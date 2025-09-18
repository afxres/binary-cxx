window.BENCHMARK_DATA = {
  "lastUpdate": 1758208848919,
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
          "id": "39e4a714e17e2fcdf2b5ac73d7c6118d64892579",
          "message": "Fix decode performance for common converters",
          "timestamp": "2025-09-17T22:33:02+08:00",
          "tree_id": "a24e8d341783221b2c3fc157b6ef87ae31cd87c1",
          "url": "https://github.com/afxres/binary-cxx/commit/39e4a714e17e2fcdf2b5ac73d7c6118d64892579"
        },
        "date": 1758119668929,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 95.41129413319565,
            "unit": "ns/iter",
            "extra": "iterations: 6960605\ncpu: 95.39365285057836 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 48.799462351190634,
            "unit": "ns/iter",
            "extra": "iterations: 14633716\ncpu: 48.79045254124105 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.1382936675537,
            "unit": "ns/iter",
            "extra": "iterations: 20516131\ncpu: 34.1256030193997 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 276.65277387784164,
            "unit": "ns/iter",
            "extra": "iterations: 2535656\ncpu: 276.5916035140413 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 171.324461470233,
            "unit": "ns/iter",
            "extra": "iterations: 3889525\ncpu: 171.2975545857141 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 144.6300411501365,
            "unit": "ns/iter",
            "extra": "iterations: 4844455\ncpu: 144.62212199308294 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 28.32441758912272,
            "unit": "ns/iter",
            "extra": "iterations: 24705883\ncpu: 28.32218710822845 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 29.647331292596704,
            "unit": "ns/iter",
            "extra": "iterations: 23810366\ncpu: 29.64419711145978 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.55868879957696,
            "unit": "ns/iter",
            "extra": "iterations: 6261987\ncpu: 111.55247894957326 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 115.47950301239851,
            "unit": "ns/iter",
            "extra": "iterations: 6064940\ncpu: 115.47475770576479 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2225.5468836980695,
            "unit": "ns/iter",
            "extra": "iterations: 314363\ncpu: 2225.411696032925 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 988.124191138818,
            "unit": "ns/iter",
            "extra": "iterations: 708867\ncpu: 988.0238718969846 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2990.309475806408,
            "unit": "ns/iter",
            "extra": "iterations: 235104\ncpu: 2990.208031339317 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1117.5692419660757,
            "unit": "ns/iter",
            "extra": "iterations: 622426\ncpu: 1117.4801679235777 ns\nthreads: 1"
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
          "id": "7a6545a15fca61c1ee2d97e982b8265ee19d4998",
          "message": "New experimental definitions",
          "timestamp": "2025-09-18T21:54:20+08:00",
          "tree_id": "242374c1b82ee2714a8c1b335d7053cceadbc436",
          "url": "https://github.com/afxres/binary-cxx/commit/7a6545a15fca61c1ee2d97e982b8265ee19d4998"
        },
        "date": 1758203961773,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 95.57199673777514,
            "unit": "ns/iter",
            "extra": "iterations: 7344680\ncpu: 95.55923280524136 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 49.20775970110146,
            "unit": "ns/iter",
            "extra": "iterations: 14433391\ncpu: 49.20647559537465 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 37.35691731972611,
            "unit": "ns/iter",
            "extra": "iterations: 19330970\ncpu: 37.350457426606106 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 271.0939483764445,
            "unit": "ns/iter",
            "extra": "iterations: 2528495\ncpu: 271.0529366283106 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 168.05454818347818,
            "unit": "ns/iter",
            "extra": "iterations: 4277411\ncpu: 168.0176604492764 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.75480516039397,
            "unit": "ns/iter",
            "extra": "iterations: 4769872\ncpu: 148.74673827725348 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.45076251217231,
            "unit": "ns/iter",
            "extra": "iterations: 26849014\ncpu: 25.44980493510861 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 27.38472127366666,
            "unit": "ns/iter",
            "extra": "iterations: 25562314\ncpu: 27.383428002644816 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.3622204613156,
            "unit": "ns/iter",
            "extra": "iterations: 6172357\ncpu: 111.35097888861576 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 118.97711676992785,
            "unit": "ns/iter",
            "extra": "iterations: 6219795\ncpu: 118.95988645928063 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2212.5550307383032,
            "unit": "ns/iter",
            "extra": "iterations: 317359\ncpu: 2212.1468998830937 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 987.5245716200847,
            "unit": "ns/iter",
            "extra": "iterations: 716070\ncpu: 987.4062451994919 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2961.932734553229,
            "unit": "ns/iter",
            "extra": "iterations: 241491\ncpu: 2961.787913421208 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1089.1973678191926,
            "unit": "ns/iter",
            "extra": "iterations: 655958\ncpu: 1089.1306028739655 ns\nthreads: 1"
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
          "id": "84b1ef2f6464f5cf25aa4795bfbc2b45b64770c5",
          "message": "Fix encode with length prefix method for experimental container converter",
          "timestamp": "2025-09-18T23:04:30+08:00",
          "tree_id": "26e785a2e7aec8b28c1e4482d2946aec4b1474dc",
          "url": "https://github.com/afxres/binary-cxx/commit/84b1ef2f6464f5cf25aa4795bfbc2b45b64770c5"
        },
        "date": 1758208118933,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 98.69536040096239,
            "unit": "ns/iter",
            "extra": "iterations: 7173982\ncpu: 98.67894734054255 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 49.14364515010284,
            "unit": "ns/iter",
            "extra": "iterations: 13992801\ncpu: 49.14330976335617 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 36.885354628488145,
            "unit": "ns/iter",
            "extra": "iterations: 18833329\ncpu: 36.88339830945448 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 277.8566057029126,
            "unit": "ns/iter",
            "extra": "iterations: 2544627\ncpu: 277.84762403291325 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 169.48613148135016,
            "unit": "ns/iter",
            "extra": "iterations: 4140709\ncpu: 169.4778193782755 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 153.1472515279473,
            "unit": "ns/iter",
            "extra": "iterations: 4571158\ncpu: 153.1399157500133 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.8594797803076,
            "unit": "ns/iter",
            "extra": "iterations: 27102242\ncpu: 25.857753723843242 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.442202252379165,
            "unit": "ns/iter",
            "extra": "iterations: 26473696\ncpu: 26.442201459138925 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 113.33971904662144,
            "unit": "ns/iter",
            "extra": "iterations: 5700590\ncpu: 113.33092557086187 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 118.59522286201498,
            "unit": "ns/iter",
            "extra": "iterations: 5903451\ncpu: 118.58924889865267 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2263.6343430820634,
            "unit": "ns/iter",
            "extra": "iterations: 309681\ncpu: 2263.5298387695766 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1033.7606472904217,
            "unit": "ns/iter",
            "extra": "iterations: 678459\ncpu: 1033.70385682849 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2925.8755713113787,
            "unit": "ns/iter",
            "extra": "iterations: 238924\ncpu: 2925.789711372657 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1076.154829466673,
            "unit": "ns/iter",
            "extra": "iterations: 649140\ncpu: 1076.0697338016448 ns\nthreads: 1"
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
          "id": "e8b90ca70aec60f1373f77a1639a332162be5c3d",
          "message": "Refact internal get capacity function",
          "timestamp": "2025-09-18T23:18:29+08:00",
          "tree_id": "337ef7043a17554da7170367aa1589546c4e8052",
          "url": "https://github.com/afxres/binary-cxx/commit/e8b90ca70aec60f1373f77a1639a332162be5c3d"
        },
        "date": 1758208848317,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 100.25326658966877,
            "unit": "ns/iter",
            "extra": "iterations: 7081621\ncpu: 100.24961601305691 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 50.78506009999728,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.7737702 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 37.09524503292858,
            "unit": "ns/iter",
            "extra": "iterations: 18861771\ncpu: 37.088281688925186 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 273.6621678420876,
            "unit": "ns/iter",
            "extra": "iterations: 2607570\ncpu: 273.6247092120251 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 169.2736448189767,
            "unit": "ns/iter",
            "extra": "iterations: 4147029\ncpu: 169.25760683130014 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 152.5500958265882,
            "unit": "ns/iter",
            "extra": "iterations: 4573365\ncpu: 152.5373515999708 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.846912491469862,
            "unit": "ns/iter",
            "extra": "iterations: 27084411\ncpu: 25.844763764661547 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.460063701189824,
            "unit": "ns/iter",
            "extra": "iterations: 26475801\ncpu: 26.458496307628224 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 113.40046091202521,
            "unit": "ns/iter",
            "extra": "iterations: 6164734\ncpu: 113.39183247809243 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 118.59454256536925,
            "unit": "ns/iter",
            "extra": "iterations: 5892219\ncpu: 118.58458197158 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2251.520032927256,
            "unit": "ns/iter",
            "extra": "iterations: 310988\ncpu: 2251.3104492777893 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1018.4631271061891,
            "unit": "ns/iter",
            "extra": "iterations: 685490\ncpu: 1018.3571751593755 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2909.617222790793,
            "unit": "ns/iter",
            "extra": "iterations: 240414\ncpu: 2909.4046478158516 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1079.4700482551827,
            "unit": "ns/iter",
            "extra": "iterations: 653401\ncpu: 1079.3720441199193 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}