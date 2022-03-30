### 本npm工程的开发流程（非移植）：

1.初始化npm项目:

```
mkdir zmq_java
cd zmq_java

npm init  #In process,you need type in project name、version etc.
#install strips package
npm install strips

#install zeromq package
#if you haven't libzmq ever, type this command to download.
npm install --unsafe-perm zeromq@5
#if you have libzmq downloaded locally,use your local zmq instead of downloading.
npm install zeromq@5 --zmq-external
```

2.vscode 下各个依赖node的智能提示（补全）

```
#工程目录下（package.json同级目录）
npm install --save-dev @types/node 
npm i @types/zmq --save-dev
```

你的package.json文件里的dependence 会多一个叫types的插件，他用来给大部分node包提供vscode下的补全，不影响其他功能。
如果你的node包不在types插件的解决范围内，
你需要在https://microsoft.github.io/TypeSearch/下，搜索你的包，执行***类似***

`npm i @types/your_package_name --save-dev`

的语句来为你的包添加补全插件。(如果没有搜索结果，那就是包太冷门了，vscode没法补全)

