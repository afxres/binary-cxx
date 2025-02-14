window.BENCHMARK_DATA = {
  "lastUpdate": 1739535728250,
  "repoUrl": "https://github.com/afxres/binary-cxx",
  "entries": {
    "Benchmark": [
      {
        "commit": {
          "author": {
            "email": "stdarg@outlook.com",
            "name": "miko",
            "username": "afxres"
          },
          "committer": {
            "email": "stdarg@outlook.com",
            "name": "miko",
            "username": "afxres"
          },
          "distinct": true,
          "id": "060dc74ed05f5e340fa43217992c69a13ae693cc",
          "message": "Add workflow for benchmark",
          "timestamp": "2025-02-13T21:16:27+08:00",
          "tree_id": "527f353ae70a4e107b9406971c53442fa08970b3",
          "url": "https://github.com/afxres/binary-cxx/commit/060dc74ed05f5e340fa43217992c69a13ae693cc"
        },
        "date": 1739452646446,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 110.45635725856523,
            "unit": "ns/iter",
            "extra": "iterations: 6250375\ncpu: 110.45419098854069 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 98.92778151620492,
            "unit": "ns/iter",
            "extra": "iterations: 7079628\ncpu: 98.91843554491844 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 62.174407693500314,
            "unit": "ns/iter",
            "extra": "iterations: 11290987\ncpu: 62.166123563865575 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 48.701019309467874,
            "unit": "ns/iter",
            "extra": "iterations: 14385327\ncpu: 48.695385026701175 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.89967860289779,
            "unit": "ns/iter",
            "extra": "iterations: 13854512\ncpu: 50.89566178873713 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 36.278504786980484,
            "unit": "ns/iter",
            "extra": "iterations: 18268300\ncpu: 36.27657800671108 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 274.2565671492213,
            "unit": "ns/iter",
            "extra": "iterations: 2553924\ncpu: 274.2515971501111 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 170.17116116928676,
            "unit": "ns/iter",
            "extra": "iterations: 4111838\ncpu: 170.17160452332982 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 135.4994141671891,
            "unit": "ns/iter",
            "extra": "iterations: 5178952\ncpu: 135.49456839916655 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2405.4837329560787,
            "unit": "ns/iter",
            "extra": "iterations: 291233\ncpu: 2405.4902020032036 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2236.6392481560947,
            "unit": "ns/iter",
            "extra": "iterations: 315225\ncpu: 2236.582206360538 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1136.201584571373,
            "unit": "ns/iter",
            "extra": "iterations: 615687\ncpu: 1136.1394556000057 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 971.5909985626307,
            "unit": "ns/iter",
            "extra": "iterations: 719374\ncpu: 971.5025494388173 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2977.546414548785,
            "unit": "ns/iter",
            "extra": "iterations: 233806\ncpu: 2977.32371282174 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1061.1902491209216,
            "unit": "ns/iter",
            "extra": "iterations: 658074\ncpu: 1061.0994508216388 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "stdarg@outlook.com",
            "name": "miko",
            "username": "afxres"
          },
          "committer": {
            "email": "stdarg@outlook.com",
            "name": "miko",
            "username": "afxres"
          },
          "distinct": true,
          "id": "84dd4207726ee2427ea5ac76df9c2fc4eda12e51",
          "message": "Fix unsafe method names",
          "timestamp": "2025-02-13T23:04:45+08:00",
          "tree_id": "7ab8e980a526cd14823d8b5a2faad536c66494f7",
          "url": "https://github.com/afxres/binary-cxx/commit/84dd4207726ee2427ea5ac76df9c2fc4eda12e51"
        },
        "date": 1739459143484,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 110.37688780942389,
            "unit": "ns/iter",
            "extra": "iterations: 6377630\ncpu: 110.36977450871248 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 98.64812159072672,
            "unit": "ns/iter",
            "extra": "iterations: 7074816\ncpu: 98.64388741700138 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.30161753311395,
            "unit": "ns/iter",
            "extra": "iterations: 11097949\ncpu: 63.2946916587921 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.14907290970926,
            "unit": "ns/iter",
            "extra": "iterations: 14060281\ncpu: 49.14669614355503 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.660938053566504,
            "unit": "ns/iter",
            "extra": "iterations: 13850531\ncpu: 50.65981419773724 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 38.863739216817464,
            "unit": "ns/iter",
            "extra": "iterations: 17230651\ncpu: 38.86318955679621 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 272.98109360202227,
            "unit": "ns/iter",
            "extra": "iterations: 2573203\ncpu: 272.97767607141753 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 172.18874353561898,
            "unit": "ns/iter",
            "extra": "iterations: 4071154\ncpu: 172.18161828316988 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 136.91611093833376,
            "unit": "ns/iter",
            "extra": "iterations: 5148049\ncpu: 136.91346702410962 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2463.9993331345036,
            "unit": "ns/iter",
            "extra": "iterations: 284915\ncpu: 2463.9030588070123 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2273.0889335150237,
            "unit": "ns/iter",
            "extra": "iterations: 306746\ncpu: 2273.0189668324933 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1166.2147615901129,
            "unit": "ns/iter",
            "extra": "iterations: 609853\ncpu: 1166.1267223412874 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 987.117103507665,
            "unit": "ns/iter",
            "extra": "iterations: 708305\ncpu: 987.0426934724428 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2943.0244751285272,
            "unit": "ns/iter",
            "extra": "iterations: 238487\ncpu: 2942.867401577439 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1060.3589036265166,
            "unit": "ns/iter",
            "extra": "iterations: 669188\ncpu: 1060.2946018159341 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "stdarg@outlook.com",
            "name": "miko",
            "username": "afxres"
          },
          "committer": {
            "email": "stdarg@outlook.com",
            "name": "miko",
            "username": "afxres"
          },
          "distinct": true,
          "id": "019fdf473e6441538538cab1b779a74ffde45de0",
          "message": "Set branches for workflows",
          "timestamp": "2025-02-14T20:15:15+08:00",
          "tree_id": "6b76e46905fdc040261302602ef9c2d6e1e9e403",
          "url": "https://github.com/afxres/binary-cxx/commit/019fdf473e6441538538cab1b779a74ffde45de0"
        },
        "date": 1739535727405,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 112.21474443296654,
            "unit": "ns/iter",
            "extra": "iterations: 6397167\ncpu: 112.21171762437967 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 101.07332455655754,
            "unit": "ns/iter",
            "extra": "iterations: 6581765\ncpu: 101.0633805673706 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 62.54774479281305,
            "unit": "ns/iter",
            "extra": "iterations: 11219590\ncpu: 62.54558535561462 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.18001219396816,
            "unit": "ns/iter",
            "extra": "iterations: 14249668\ncpu: 49.17715205715669 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.714966895664425,
            "unit": "ns/iter",
            "extra": "iterations: 13807105\ncpu: 50.71239365529558 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 38.558801911284824,
            "unit": "ns/iter",
            "extra": "iterations: 18141094\ncpu: 38.55565166025822 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 279.92985717628926,
            "unit": "ns/iter",
            "extra": "iterations: 2516879\ncpu: 279.9319744810936 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 172.52680853570632,
            "unit": "ns/iter",
            "extra": "iterations: 4073945\ncpu: 172.50945827692817 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 136.83694653592357,
            "unit": "ns/iter",
            "extra": "iterations: 5101799\ncpu: 136.8248390420712 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2458.413658981613,
            "unit": "ns/iter",
            "extra": "iterations: 287181\ncpu: 2458.266737702006 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2248.5329516330366,
            "unit": "ns/iter",
            "extra": "iterations: 308619\ncpu: 2248.4444217627547 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1152.8808164207542,
            "unit": "ns/iter",
            "extra": "iterations: 615026\ncpu: 1152.8799254015257 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 988.9424597160106,
            "unit": "ns/iter",
            "extra": "iterations: 709277\ncpu: 988.917370787436 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2932.3786495045556,
            "unit": "ns/iter",
            "extra": "iterations: 238046\ncpu: 2932.352247044686 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1083.1191288318387,
            "unit": "ns/iter",
            "extra": "iterations: 641759\ncpu: 1083.0997181184816 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}