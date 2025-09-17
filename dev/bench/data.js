window.BENCHMARK_DATA = {
  "lastUpdate": 1758114577005,
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
          "distinct": false,
          "id": "975917057118dc9b0a2a462b8b14e593cf53d9d5",
          "message": "New benchmarks for experimental converters",
          "timestamp": "2025-09-17T21:05:11+08:00",
          "tree_id": "f6cc0584977793681687fa254b5ea3eb8819a740",
          "url": "https://github.com/afxres/binary-cxx/commit/975917057118dc9b0a2a462b8b14e593cf53d9d5"
        },
        "date": 1758114576119,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 106.14407023554723,
            "unit": "ns/iter",
            "extra": "iterations: 6716599\ncpu: 106.12580489024282 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 55.82691315802856,
            "unit": "ns/iter",
            "extra": "iterations: 12555680\ncpu: 55.82649701171103 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 43.194676319528746,
            "unit": "ns/iter",
            "extra": "iterations: 16253004\ncpu: 43.18765011071184 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 300.9542903253344,
            "unit": "ns/iter",
            "extra": "iterations: 2353353\ncpu: 300.93055567949216 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 189.54882164077617,
            "unit": "ns/iter",
            "extra": "iterations: 3698278\ncpu: 189.53239372486343 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 150.20112661744355,
            "unit": "ns/iter",
            "extra": "iterations: 4648783\ncpu: 150.19382513660034 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 33.27112926931753,
            "unit": "ns/iter",
            "extra": "iterations: 21027774\ncpu: 33.2697578925853 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 34.55161160371691,
            "unit": "ns/iter",
            "extra": "iterations: 20265714\ncpu: 34.55012090864406 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 116.31591281310364,
            "unit": "ns/iter",
            "extra": "iterations: 6002691\ncpu: 116.31179332735928 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 121.91830991557912,
            "unit": "ns/iter",
            "extra": "iterations: 5741370\ncpu: 121.91598938929216 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2275.958517348157,
            "unit": "ns/iter",
            "extra": "iterations: 308852\ncpu: 2275.8635430562213 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1013.74311032598,
            "unit": "ns/iter",
            "extra": "iterations: 690635\ncpu: 1013.6485133246952 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 3003.2242612419122,
            "unit": "ns/iter",
            "extra": "iterations: 233500\ncpu: 3003.184077087797 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1104.3022827089792,
            "unit": "ns/iter",
            "extra": "iterations: 634115\ncpu: 1104.2102410446053 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}