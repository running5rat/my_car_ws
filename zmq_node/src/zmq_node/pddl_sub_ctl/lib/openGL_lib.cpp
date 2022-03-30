//ROS1 draw_behavior_tree程序的bug：
//1.他是根据前一个父节点的最右子节点的位置，加上一个skip来决定下一个父节点的位置，但是加上一个skip应该是下一个父节点的最右子节点的位置。
//2.节点内名字长的时候，在draw_node的过程中断行有错误，一行内显示不全，而且行数多时下面的行数显示不全
#define NODE_WIDTH_ 0.04//无名字的节点宽度
#define NODE_HEIGHT_ 0.02//无名字的节点高度
#define FONT_WIDTH 0.015//节点中每一个字体的宽度，设置不合理会显示不全 0.017
#define FONT_HEIGHT 0.025//节点中每一个字体的高度
#define ROW_SPACING 0.005//两行之间的留白大小
#define LEAVE_BLANK_IN_X_DIRECTION 0.01//绘制node的时候字体和边框在x方向的间距
#define LEAVE_BLANK_IN_Y_DIRECTION 0.02 //绘制node的时候字体和边框在y方向的间距
#define ORIGIN_X 0//绘制的起始点x轴坐标
#define ORIGIN_Y 0.4//绘制的起始点y轴坐标


#include<draw.h>
#include<string>
#include<vector>

#include <X11/Xlib.h>
#include "ros/ros.h"

const float DEG2RAD = 3.14159/180.0;


BT::ControlNode* tree;
bool init = false;

float x_center=ORIGIN_X;
float y_center=ORIGIN_Y;

void * font_array[3] = {GLUT_BITMAP_8_BY_13, GLUT_BITMAP_8_BY_13, GLUT_BITMAP_8_BY_13};
void * font = font_array[0];
float additional_spacing_array[10]={0,0.4,0,0.15,0};//每一层节点间距额外加这个数值
bool is_number_pressed_array[10];
unsigned char number_char[4] = {'0', '1', '2', '3'};


// float x = 0.0;
// float y = 0.4;
// float x_offset = 0.01;
float y_offset = 0.2;//行为树每一层间距0.15
float r_color = 1;
float g_color = 1;
float b_color = 1;
GLfloat x_space = 0.05;//子节点间距   0.15改成0.05

int depth;

double zoom = 1.0f;

float fraction = 0.1f;
float zoom_fraction = 0.1f;


void drawString(void * font, const char *string, float x, float y, float z)
{
    renderBitmapString(x, y, font, string);
}

int compute_node_lines(const char *string)//need rec
{
    const char *c;
    int i = 0;
    int new_line_num = 1;

    for (c=string; *c != '\0'; c++)
    {
        // if ((*c == '\n') || ((*c == ' ' && i > 6) || i > 9))//如果有 换行符 或者 一行已经有9个字母 或者 6个字母的行收到空格，则换行
        if ((*c == '\n') )//改成手动换行
        {
            new_line_num++;
            i = 0;
            continue;
        }
        i++;
    }
    return new_line_num;
}

int compute_max_width(const char *string)//need rec
{
    const char *current_char;
    int current_line_width = 0;
    int max_width = 0;

    for (current_char = string; *current_char != '\0'; current_char++)
    {
        // if ((*current_char == '\n') || ((*current_char == ' ' && current_line_width > 6) || current_line_width > 9))//如果有 换行符 或者 一行已经有9个字母 或者 6个字母的行收到空格，则换行
        if ((*current_char == '\n') )//手动换行
        {
            if (current_line_width > max_width)
            {
                max_width = current_line_width;
            }
            current_line_width = 0;
            continue;
        }
        current_line_width++;
    }

    if (current_line_width > max_width)
    {
        max_width = current_line_width;
    }

    if (max_width == 0)  // if the lable fits in a single line
    {
        max_width = current_line_width;
    }
    return max_width;
}

void renderBitmapString(float x, float y, void *font, const char *string)
{
    const char *c;
    int new_line_num = 0;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++)
    {
        // if ((*c == '\n') || ((*c == ' ' && i > 6) || i > 9))// if ((*current_char == '\n') || ((*current_char == ' ' && current_line_width > 6) || current_line_width > 9))//如果有 换行符 或者 一行已经有9个字母 或者 6个字母的行收到空格，则换行
        if (*c == '\n' )//手动换行
        {
            new_line_num++;
            glRasterPos2f(x, y - (ROW_SPACING+FONT_HEIGHT)*(new_line_num));
            continue;
        }
        glutBitmapCharacter(font, *c);//函数内部会在绘制字符后自动向后加x，所以不需要改x；换行时需要手动改y
    }
}


void draw_node(float x, float y, int node_type, const char *leafName, int status) //绘制节点：核心函数
{
    float NODE_WIDTH = NODE_WIDTH_;//默认节点长度，action\condition_node后来会覆盖
    float NODE_HEIGHT =NODE_HEIGHT_;//默认节点高度，action\condition_node后来会覆盖
    switch (node_type)//1.写node的内容
    {
    case BT::SELECTORSTAR:
        drawString(font, "?*", (x + NODE_WIDTH/2 -0.005), (y - NODE_HEIGHT/2), 0);
        break;
    case BT::SEQUENCESTAR:
        drawString(font, ">*", (x + NODE_WIDTH/2 -0.005), (y - NODE_HEIGHT/2), 0);
        break;
    case BT::SELECTOR:
        drawString(font, "?", (x + NODE_WIDTH/2 -0.005), (y - NODE_HEIGHT/2), 0);
        break;
    case BT::SEQUENCE:
        drawString(font, ">", (x + NODE_WIDTH/2 -0.005), (y - NODE_HEIGHT/2), 0);
        break;
    case BT::PARALLEL:
        drawString(font, "=", (x + NODE_WIDTH/2 -0.005), (y - NODE_HEIGHT/2), 0);
        break;
    case BT::DECORATOR:
        drawString(font, "D", (x + NODE_WIDTH/2 -0.005), (y - NODE_HEIGHT/2), 0);
        break;
    case BT::ACTION:
    {
        NODE_HEIGHT = FONT_HEIGHT*(compute_node_lines(leafName));
        // std::string st(leafName, 0, 15);
        NODE_WIDTH = FONT_WIDTH*compute_max_width(leafName);
    }
    renderBitmapString(x, y-0.5*FONT_HEIGHT, font, leafName);//字区左上角和字符的绘制起始点差一个子高   1个改成0.5个
    break;
    case BT::CONDITION:
    {
        NODE_HEIGHT = FONT_HEIGHT*compute_node_lines(leafName);
        // std::string st(leafName, 0, 15);
        NODE_WIDTH = FONT_WIDTH*compute_max_width(leafName);
    }
    renderBitmapString(x, y-0.5*FONT_HEIGHT, font, leafName);//字区左上角和字符的绘制起始点差一个子高  1个改成0.5个
    break;
    default:
        break;
    }

    switch (status)//2.根据状态选择颜色
    {
    case BT::RUNNING:
        glColor3f(0.8, 0.8, 0.8);
        break;
    case BT::SUCCESS:
        glColor3f(0.0, 1.0, 0.0);
        break;
    case BT::FAILURE:
        glColor3f(1.0, 0.0, 0.0);
        break;
    case BT::IDLE:
        glColor3f(0.0, 0.0, 0.0);
        break;
    case BT::HALTED:
        glColor3f(0.0, 0.0, 0.0);
        break;
    default:
        break;
    }

    switch (node_type)//3.画node的边框
    {
    case BT::CONDITION:
        glBegin(GL_LINE_LOOP);//绘制从第一个顶点到最后一个顶点依次相连的一组线段
        glVertex2f((GLfloat) (x + NODE_WIDTH+LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y - NODE_HEIGHT -LEAVE_BLANK_IN_Y_DIRECTION));//字体区与绘制的边框有留白
        glVertex2f((GLfloat) (x + NODE_WIDTH+LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y + LEAVE_BLANK_IN_Y_DIRECTION));
        glVertex2f((GLfloat) (x-LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y + LEAVE_BLANK_IN_Y_DIRECTION));
        glVertex2f((GLfloat) (x-LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y - NODE_HEIGHT - LEAVE_BLANK_IN_Y_DIRECTION));
        glColor3f(0.0, 0.0, 0.0);//线段颜色
        glEnd();//绘制结束
        break;

    case BT::ACTION:
        glBegin(GL_LINE_LOOP);
        glVertex2f((GLfloat) (x + NODE_WIDTH+LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y - NODE_HEIGHT -LEAVE_BLANK_IN_Y_DIRECTION));//字体区与绘制的边框有留白
        glVertex2f((GLfloat) (x + NODE_WIDTH+LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y + LEAVE_BLANK_IN_Y_DIRECTION));
        glVertex2f((GLfloat) (x-LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y + LEAVE_BLANK_IN_Y_DIRECTION));
        glVertex2f((GLfloat) (x-LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y - NODE_HEIGHT - LEAVE_BLANK_IN_Y_DIRECTION));
        glColor3f(0.0, 0.0, 0.0);
        glEnd();
        break;

    default:
        glBegin(GL_LINE_LOOP);
        glVertex2f((GLfloat) (x + NODE_WIDTH+LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y - NODE_HEIGHT -LEAVE_BLANK_IN_Y_DIRECTION));//字体区与绘制的边框有留白
        glVertex2f((GLfloat) (x + NODE_WIDTH+LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y + LEAVE_BLANK_IN_Y_DIRECTION));
        glVertex2f((GLfloat) (x-LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y + LEAVE_BLANK_IN_Y_DIRECTION));
        glVertex2f((GLfloat) (x-LEAVE_BLANK_IN_X_DIRECTION), (GLfloat) (y - NODE_HEIGHT - LEAVE_BLANK_IN_Y_DIRECTION));
        glColor3f(0.0, 0.0, 0.0);
        glEnd();
        break;
    }
}

// draw the edge connecting one node to the other
void draw_edge(GLfloat parent_x, GLfloat parent_y,
               GLfloat parent_size, GLfloat child_x, GLfloat child_y, GLfloat child_size)
{
    glLineWidth(1.5);
    glColor3f(0.0, 0.0, 0.0);
    GLfloat above_spacing = 0.04;

    glBegin(GL_LINES);
    glVertex3f(parent_x, parent_y - parent_size, 0);
    glVertex3f(parent_x, child_y + child_size + above_spacing, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(parent_x, child_y + child_size + above_spacing, 0);
    glVertex3f(child_x, child_y + child_size + above_spacing, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(child_x, child_y + child_size + above_spacing, 0);
    glVertex3f(child_x, child_y+child_size, 0);
    glEnd();
}


void updateTree(BT::TreeNode* tree, GLfloat x_pos, GLfloat y_pos, GLfloat y_offset, int depth )//显示函数！
{
    BT::ControlNode* d = dynamic_cast<BT::ControlNode*> (tree);//将tree这个树节点转换成control_node，如果是动作节点则因为不是control_node的继承类而无法转换，返回NULL
    if (d == NULL)
    {
        // if it is a leaf node, draw it
        draw_node(x_pos , (GLfloat) y_pos, tree->DrawType(), tree->get_name().c_str(), tree->get_color_status());//draw_node根据node的type不同，DrawType不同
    }
    else
    {
        // if it is a control flow node, draw it and its children
        draw_node((GLfloat) x_pos, (GLfloat) y_pos, tree->DrawType(),
                  tree->get_name().c_str(), tree->get_color_status());//绘制父节点
        std::vector<BT::TreeNode*> children = d->GetChildren();//子节点集合
        int M = d->GetChildrenNumber();//子节点数量
        std::vector<GLfloat> children_x_end;
        std::vector<GLfloat> children_x_middle_relative;

        GLfloat max_x_end = 0;
        GLfloat current_x_end = 0;

        for (int i = 0; i < M; i++)//遍历定位子节点位置
        {
            if (children[i]->DrawType() != BT::ACTION && children[i]->DrawType() != BT::CONDITION)//当子节点不是动作或者条件节点，比如序列和选择节点等
            {
                current_x_end = 0.04;//固定x的长度
                children_x_middle_relative.push_back(0.02);
            }
            else
            {
                current_x_end = FONT_WIDTH*compute_max_width(children[i]->get_name().c_str());//由节点名字来计算节点显示上的最大长度  default:0.02
                children_x_middle_relative.push_back(current_x_end/2);
            }

            if (i < M-1)//如果不是最后一个子节点，需要额外加x_space和additional_spacing_array（估计这个额外的space是区分不同父节点的子节点的距离）
            {
                max_x_end = max_x_end + current_x_end + x_space + additional_spacing_array[depth];//additional_spacing_array是什么东西
            }
            else//是最后一个子节点，只加节点长度
            {
                max_x_end = max_x_end + current_x_end;
            }
            children_x_end.push_back(max_x_end);//记录遍历过程中，当前子节点x轴上的最大位置
        }

        GLfloat x_shift = x_pos - max_x_end/2;

        for (int i = 0; i < M; i++)
        {
            if (i > 0)
            {
                updateTree(children[i], x_shift + children_x_end.at(i - 1) , y_pos - y_offset  , y_offset, depth + 1);//递归调用updatetree函数来绘制子节点，每一次updatetree只绘制一个父节点or叶子节点
                draw_edge(x_pos + 0.015, y_pos, LEAVE_BLANK_IN_Y_DIRECTION+NODE_HEIGHT_,
                          x_shift + children_x_end.at(i-1) + children_x_middle_relative.at(i),
                          y_pos - y_offset, 0.02);                                                                                              //绘制父节点到子节点的连接线
            }
            else
            {
                updateTree(children[i], x_shift , y_pos - y_offset  , y_offset, depth + 1);
                draw_edge(x_pos + 0.015, y_pos, LEAVE_BLANK_IN_Y_DIRECTION+NODE_HEIGHT_,
                          x_shift + children_x_middle_relative.at(i), y_pos - y_offset, 0.02);
            }
        }
    }
}





void display()
{
    glClearColor(r_color, g_color, b_color, 0.1);    // clear the draw buffer ，设置清除（变成的）颜色（白色）。
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything，清除为白色。
    updateTree(tree, x_center , y_center, y_offset, 1);   //行为树的绘制函数！！！！
    glutSwapBuffers();//双缓冲，防止屏幕闪烁
    glutPostRedisplay();//防止反复调用显示函数
}


void processSpecialKeys(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_UP :
        y_center +=  fraction;
        break;
    case GLUT_KEY_DOWN :
        y_center -=  fraction;
        break;
    case GLUT_KEY_LEFT:
        x_center -=  fraction;
        break;
    case GLUT_KEY_RIGHT:
        x_center +=  fraction;
        break;
    case  GLUT_KEY_PAGE_UP:
        for (int i = 1; i < 10; i++)
        {
            if (is_number_pressed_array[i])
            {
                additional_spacing_array[i] += fraction;
            }
        }
        break;
    case  GLUT_KEY_PAGE_DOWN:
        for (int i = 1; i < 10; i++)
        {
            if (is_number_pressed_array[i] && additional_spacing_array[i] >= 0 )
            {
                additional_spacing_array[i] -= fraction;
            }
        }
        break;
    case  GLUT_KEY_F1:
        if (r_color < 1)  r_color +=  fraction;
        break;
    case  GLUT_KEY_F2:
        if (r_color > 0) r_color -=  fraction;
        break;
    case  GLUT_KEY_F3:
        if (g_color < 1) g_color +=  fraction;
        break;
    case  GLUT_KEY_F4:
        if (g_color > 0) g_color -=  fraction;
        break;
    case  GLUT_KEY_F5:
        if (b_color < 1) b_color +=  fraction;
        break;
    case  GLUT_KEY_F6:
        if (b_color > 0) b_color -=  fraction;
        break;
    case GLUT_KEY_HOME:
        if (zoom < 1.0f)
        {
            glScalef(1.0f + zoom_fraction, 1.0f + zoom_fraction, 1.0f);
            zoom += zoom_fraction;
        }
        else
        {
            glScalef(1.0f, 1.0f, 1.0f);
        }
        break;
    case GLUT_KEY_END:
        glScalef(1.0f  - zoom_fraction, 1.0f  - zoom_fraction, 1.0f);
        zoom -= zoom_fraction;
        break;
    }
}

void drawTree(BT::ControlNode* tree_)
{
    /***************************BT VISUALIZATION****************************/
    int argc = 1;
    char *argv[1] = {const_cast<char*>("")};

    if (!init)
    {
        XInitThreads();
        glutInit(&argc, argv);
        init = true;
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);  //  Antialiasing,显示模式的初始化
        glEnable(GL_MULTISAMPLE);//开启多重采样
    }
    tree = tree_;//传入参数(tree_)是根结点,所以要绘制的节点（tree）就是根结点。
    depth = tree->Depth();

    glutInitWindowSize(1024, 860);

    glutCreateWindow("Behavior Tree");  // Create a window

    glClearColor(0, 0.71, 0.00, 0.1);//red，green，blue，不透明度,值域都是：0~1
    glutDisplayFunc(display);  // Register display callback（显示的回调函数）


    glutSpecialFunc(processSpecialKeys);  // Register keyboard arrow callback，键盘箭头（上下左右键）回调，以及特殊键位的回调处理（F1、F2等，end，home等）

    glutMainLoop();             // Enter main event loop

    /***************************ENDOF BT VISUALIZATION ****************************/
}

