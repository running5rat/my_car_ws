
  var domain_add='/home/tiger/lab_car_ws/src/zmq_test/examples/NCS_new/domain.txt';
  var problem_add='/home/tiger/lab_car_ws/src/zmq_test/examples/NCS_new/problem.txt';
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
        // console.log("1:" + typeof solution.path[0]);
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

