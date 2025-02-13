window.BENCHMARK_DATA = {
  "lastUpdate": 1739452646771,
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
      }
    ]
  }
}