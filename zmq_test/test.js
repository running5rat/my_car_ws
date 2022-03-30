//0.initialize sub ip
var zmq_rec = require('zeromq')
  , sock_rec = zmq_rec.socket('sub');
 
sock_rec.connect('tcp://127.0.0.1:2000');
sock_rec.subscribe("");
console.log('Sub IP bound to port 2000');

//0.initialize pub ip
var zmq_pub = require('zeromq')
,sock_pub = zmq_pub.socket('pub');

sock_pub.bindSync('tcp://127.0.0.1:3000');
console.log('Pub IP bound to port 3000');

//1.receive the initialize msg from zmq
sock_rec.on('message', function(data) {//if received
  // console.log('Data::', data.toString("utf-8"));


  var jsonObj=JSON.parse(data);
  var domain_add=jsonObj["domain_address"];
  var problem_add=jsonObj["problem_address"];
  // console.log("type of domain_add:"+typeof domain_add);
  // console.log(domain_add);
  // console.log(problem_add);



  //2.export Strips problem solutions.
  var strips = require('strips');
  var util = require('util');
  strips.load(domain_add,problem_add, function(domain, problem) {
    var solutions = strips.solve(domain, problem,false);
        //only take the first solution into consideration
        var solution = solutions[0];
        console.log(util.inspect(solution, true, 100, true));
        console.log("1:" + typeof solution.path[0]);
        console.log('- Solution found in ' + solution.steps + ' steps!');
        for (var i = 0; i < solution.path.length; i++) {
            console.log((i + 1) + '. ' + solution.path[i]);
        }

        var temp_state=problem.states[0];
        var error_flag=false;

        var output=new Array;


        for(var i=0;i<solution.path.length;i++)//遍历所有解
        {
          error_flag=true;
          var actions = strips.applicableActions(domain, temp_state);
          for(var j=0;j<actions.length;j++)
          {
            if(strips.actionToString(actions[j])==solution.path[i])
            {
              temp_state=strips.applyAction(actions[j],temp_state);
              error_flag=false;

              for(var k=0;k<actions[j]["parameters"]["length"];k++ )//把param=map[param],把实参赋给形参
                  actions[j]["parameters"][k]["parameter"]=actions[j]["map"][ actions[j]["parameters"][k]["parameter"]];
              output.push(actions[j]);
              // console.log("actions:",actions[j]["map"][ actions[j]["parameters"][0]["parameter"] ]);
              break;
            }
          }
          if(error_flag==true)
            console.log("ERROR in solution tracking!")
        }

        console.log(util.inspect(output, true, 100, true));




  //3.Pub solutions via ZeroMQ
  var jsonObj=output;
  jsonStr=JSON.stringify(jsonObj);
  // setInterval(function(){
  //   sock_pub.send(jsonStr);
  // }, 50);//0.05s执行一次
  sock_pub.send(jsonStr);//单次发送
});
});

// Load the domain and problem.

// var strips = require('strips');
// var util = require('util');
 
// // Load the domain and problem.
// strips.load('./examples/Narrow-channel-Search/domain.txt', './examples/Narrow-channel-Search/problem.txt', function(domain, problem) {
//     // Get all applicable actions for the initial state.
// var actions = strips.applicableActions(domain, problem.states[0]);

//     // Display the JSON result.
//     console.log(util.inspect(actions[0].precondition[0], false, 100, true));
// });

