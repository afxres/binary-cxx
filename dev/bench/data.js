window.BENCHMARK_DATA = {
  "lastUpdate": 1765106470467,
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
          "id": "fe147e6717d9d7b6ef5418d57c5b3598ca2c63e7",
          "message": "Fix code style",
          "timestamp": "2025-09-18T23:55:56+08:00",
          "tree_id": "8567bcd9328d3dbabbbcc6fbb0fa9ef4836a6025",
          "url": "https://github.com/afxres/binary-cxx/commit/fe147e6717d9d7b6ef5418d57c5b3598ca2c63e7"
        },
        "date": 1758211054082,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 98.18760240970222,
            "unit": "ns/iter",
            "extra": "iterations: 7194753\ncpu: 98.17885297799663 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 50.045666599999095,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.04414739999999 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 37.06681517950861,
            "unit": "ns/iter",
            "extra": "iterations: 18910149\ncpu: 37.0636622693983 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 269.9016359322183,
            "unit": "ns/iter",
            "extra": "iterations: 2618507\ncpu: 269.887804004343 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 171.92822031990838,
            "unit": "ns/iter",
            "extra": "iterations: 4070372\ncpu: 171.92051144219744 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 156.94246513069686,
            "unit": "ns/iter",
            "extra": "iterations: 4452413\ncpu: 156.93176890823023 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.855346025405634,
            "unit": "ns/iter",
            "extra": "iterations: 27051901\ncpu: 25.85329921915656 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.4539057278798,
            "unit": "ns/iter",
            "extra": "iterations: 26426201\ncpu: 26.452835577841846 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 116.11206896982165,
            "unit": "ns/iter",
            "extra": "iterations: 6007149\ncpu: 116.100290170928 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 118.74660762066055,
            "unit": "ns/iter",
            "extra": "iterations: 5905000\ncpu: 118.74521388653683 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2268.2516359039005,
            "unit": "ns/iter",
            "extra": "iterations: 306864\ncpu: 2267.949290239328 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1021.4452136258917,
            "unit": "ns/iter",
            "extra": "iterations: 692800\ncpu: 1021.387181004617 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2934.1833145822047,
            "unit": "ns/iter",
            "extra": "iterations: 238208\ncpu: 2933.9333145822206 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1109.791595797595,
            "unit": "ns/iter",
            "extra": "iterations: 631446\ncpu: 1109.774102615267 ns\nthreads: 1"
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
          "id": "6e04498a2c69396d406b08326ae7572c20a6bb56",
          "message": "Remove allocator memory shrink logic",
          "timestamp": "2025-09-19T21:15:32+08:00",
          "tree_id": "925636cdc711e5d8f61c9c55e51ef4afe681389d",
          "url": "https://github.com/afxres/binary-cxx/commit/6e04498a2c69396d406b08326ae7572c20a6bb56"
        },
        "date": 1758287959454,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.15584027674181,
            "unit": "ns/iter",
            "extra": "iterations: 7646701\ncpu: 93.1377435838017 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 47.579112461764566,
            "unit": "ns/iter",
            "extra": "iterations: 14703006\ncpu: 47.57143015516691 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 35.204436976243144,
            "unit": "ns/iter",
            "extra": "iterations: 19888770\ncpu: 35.20023354888212 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 271.97377892129805,
            "unit": "ns/iter",
            "extra": "iterations: 2584600\ncpu: 271.9248533622225 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 174.96002098730065,
            "unit": "ns/iter",
            "extra": "iterations: 3994796\ncpu: 174.93034437803578 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 140.85582042037316,
            "unit": "ns/iter",
            "extra": "iterations: 4966265\ncpu: 140.83474522604013 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 26.442322132311457,
            "unit": "ns/iter",
            "extra": "iterations: 26471601\ncpu: 26.438068441723633 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.74254531013753,
            "unit": "ns/iter",
            "extra": "iterations: 26153033\ncpu: 26.739636546170384 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 110.08638114801649,
            "unit": "ns/iter",
            "extra": "iterations: 6352393\ncpu: 110.07889310374843 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 117.85755606742424,
            "unit": "ns/iter",
            "extra": "iterations: 5939902\ncpu: 117.8467661587685 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2248.5140752511643,
            "unit": "ns/iter",
            "extra": "iterations: 302055\ncpu: 2248.3017331280735 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 987.9762215273304,
            "unit": "ns/iter",
            "extra": "iterations: 707741\ncpu: 987.9308207380947 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2929.8642523707044,
            "unit": "ns/iter",
            "extra": "iterations: 238855\ncpu: 2929.6908877771025 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1076.3607245331984,
            "unit": "ns/iter",
            "extra": "iterations: 651730\ncpu: 1076.3055130191954 ns\nthreads: 1"
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
          "id": "ed6ffe42a6c59787b31bbeb399b5c478fdb6bde4",
          "message": "Add unit tests for uncovered lines",
          "timestamp": "2025-09-19T23:12:34+08:00",
          "tree_id": "5835e92d5a7a1608ed34c495b89464e7c8e91c82",
          "url": "https://github.com/afxres/binary-cxx/commit/ed6ffe42a6c59787b31bbeb399b5c478fdb6bde4"
        },
        "date": 1758294915903,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.40828861258245,
            "unit": "ns/iter",
            "extra": "iterations: 7637394\ncpu: 93.40035920629471 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 47.66852131595359,
            "unit": "ns/iter",
            "extra": "iterations: 14691367\ncpu: 47.656361181365895 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 35.231467079186736,
            "unit": "ns/iter",
            "extra": "iterations: 19884305\ncpu: 35.222250211913355 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 269.7571475106641,
            "unit": "ns/iter",
            "extra": "iterations: 2590972\ncpu: 269.6853999194124 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 177.04630321153803,
            "unit": "ns/iter",
            "extra": "iterations: 3996807\ncpu: 177.02659372844374 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 140.92859417588303,
            "unit": "ns/iter",
            "extra": "iterations: 4967620\ncpu: 140.90933384598662 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 26.43290867501562,
            "unit": "ns/iter",
            "extra": "iterations: 26465277\ncpu: 26.43073582793032 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.749003391252618,
            "unit": "ns/iter",
            "extra": "iterations: 26123090\ncpu: 26.746084517566633 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 116.80899576137905,
            "unit": "ns/iter",
            "extra": "iterations: 6154832\ncpu: 116.7978173896543 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 118.2639783586539,
            "unit": "ns/iter",
            "extra": "iterations: 5939002\ncpu: 118.24444628912404 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2275.604037262039,
            "unit": "ns/iter",
            "extra": "iterations: 307337\ncpu: 2275.4646365390454 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 998.1813950013208,
            "unit": "ns/iter",
            "extra": "iterations: 709347\ncpu: 998.14711558659 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2950.0615012492044,
            "unit": "ns/iter",
            "extra": "iterations: 238548\ncpu: 2949.7793190469 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1050.7733236917063,
            "unit": "ns/iter",
            "extra": "iterations: 666554\ncpu: 1050.6833699895285 ns\nthreads: 1"
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
          "id": "9a326b4a1a39e627d838ddad39bf4197311af488",
          "message": "Add underlying allocator interface and implementation",
          "timestamp": "2025-09-20T11:14:25+08:00",
          "tree_id": "c3a469b9e9ec2ce14b1402269763b1fd6570c7dd",
          "url": "https://github.com/afxres/binary-cxx/commit/9a326b4a1a39e627d838ddad39bf4197311af488"
        },
        "date": 1758338222390,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 91.73956509644903,
            "unit": "ns/iter",
            "extra": "iterations: 6762281\ncpu: 91.732714893096 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 48.14206734041521,
            "unit": "ns/iter",
            "extra": "iterations: 14802255\ncpu: 48.139057731406474 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 35.50442182605899,
            "unit": "ns/iter",
            "extra": "iterations: 19837845\ncpu: 35.50165131343652 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 265.8713242720063,
            "unit": "ns/iter",
            "extra": "iterations: 2618971\ncpu: 265.8485848067809 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 169.37224026397172,
            "unit": "ns/iter",
            "extra": "iterations: 4142244\ncpu: 169.3592784490725 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 136.59187434543253,
            "unit": "ns/iter",
            "extra": "iterations: 5136940\ncpu: 136.57948759378166 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.826741387056433,
            "unit": "ns/iter",
            "extra": "iterations: 27040901\ncpu: 25.82562962676427 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 25.916413830069388,
            "unit": "ns/iter",
            "extra": "iterations: 27066559\ncpu: 25.914831545450607 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 112.99645512926331,
            "unit": "ns/iter",
            "extra": "iterations: 6185557\ncpu: 112.98920792420157 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 115.8054357466867,
            "unit": "ns/iter",
            "extra": "iterations: 6049914\ncpu: 115.79793448303538 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2282.7284572913304,
            "unit": "ns/iter",
            "extra": "iterations: 307900\ncpu: 2282.6243520623593 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 968.6854890461058,
            "unit": "ns/iter",
            "extra": "iterations: 716824\ncpu: 968.5996116201482 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2979.967001825404,
            "unit": "ns/iter",
            "extra": "iterations: 235013\ncpu: 2979.768004323166 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1098.36275691119,
            "unit": "ns/iter",
            "extra": "iterations: 638207\ncpu: 1098.2629303658548 ns\nthreads: 1"
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
          "id": "0fd9fea2adf1bc3c912178d34e38633cd9aff9d4",
          "message": "Add unit tests for uncovered lines",
          "timestamp": "2025-09-20T18:07:40+08:00",
          "tree_id": "c3563714daf9d566ee03ba0f44248633f8cf8e6b",
          "url": "https://github.com/afxres/binary-cxx/commit/0fd9fea2adf1bc3c912178d34e38633cd9aff9d4"
        },
        "date": 1758363090195,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 92.57593326496061,
            "unit": "ns/iter",
            "extra": "iterations: 7649355\ncpu: 92.56073211401485 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.32357427090966,
            "unit": "ns/iter",
            "extra": "iterations: 14806477\ncpu: 46.3207028923896 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 35.03085445272304,
            "unit": "ns/iter",
            "extra": "iterations: 19863065\ncpu: 35.02883104898462 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 269.89970232822776,
            "unit": "ns/iter",
            "extra": "iterations: 2613281\ncpu: 269.8798296088328 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 168.74103459448347,
            "unit": "ns/iter",
            "extra": "iterations: 4147944\ncpu: 168.72004443647256 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 137.64427760551075,
            "unit": "ns/iter",
            "extra": "iterations: 5084611\ncpu: 137.60887863397997 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.130842993645366,
            "unit": "ns/iter",
            "extra": "iterations: 27076681\ncpu: 25.102915013845305 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 25.935456357925695,
            "unit": "ns/iter",
            "extra": "iterations: 27063998\ncpu: 25.932925135451168 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 112.98290872145341,
            "unit": "ns/iter",
            "extra": "iterations: 6204568\ncpu: 112.97414034305064 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 118.93789460942419,
            "unit": "ns/iter",
            "extra": "iterations: 5898554\ncpu: 118.93374935619806 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2278.9483046045584,
            "unit": "ns/iter",
            "extra": "iterations: 307126\ncpu: 2278.701471057484 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 981.3366400201535,
            "unit": "ns/iter",
            "extra": "iterations: 714915\ncpu: 981.2556317883945 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2922.8567425685947,
            "unit": "ns/iter",
            "extra": "iterations: 239827\ncpu: 2922.377872383007 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1101.5688979256881,
            "unit": "ns/iter",
            "extra": "iterations: 635919\ncpu: 1101.4651079775879 ns\nthreads: 1"
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
          "distinct": false,
          "id": "869ef422d3bda9b5ca12c1710c2b719163e2081c",
          "message": "New decoder for named object converter",
          "timestamp": "2025-09-21T16:04:38+08:00",
          "tree_id": "5de2a3e0cdc432b0696d0bd1fa67a8b01cda2f90",
          "url": "https://github.com/afxres/binary-cxx/commit/869ef422d3bda9b5ca12c1710c2b719163e2081c"
        },
        "date": 1758442075505,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.21192680011012,
            "unit": "ns/iter",
            "extra": "iterations: 7057333\ncpu: 93.20530744404437 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 49.33279573529333,
            "unit": "ns/iter",
            "extra": "iterations: 14117735\ncpu: 49.326808655921084 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.81424606759896,
            "unit": "ns/iter",
            "extra": "iterations: 20113733\ncpu: 34.81054993620527 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 257.6484653161514,
            "unit": "ns/iter",
            "extra": "iterations: 2671560\ncpu: 257.61974464357894 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 170.39720819948496,
            "unit": "ns/iter",
            "extra": "iterations: 4101869\ncpu: 170.38684609381733 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 141.13286149325367,
            "unit": "ns/iter",
            "extra": "iterations: 4956199\ncpu: 141.11938745800958 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 26.772430842314183,
            "unit": "ns/iter",
            "extra": "iterations: 26180604\ncpu: 26.771347979595916 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.480263696006652,
            "unit": "ns/iter",
            "extra": "iterations: 26469267\ncpu: 26.47767261556584 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 110.11841795647105,
            "unit": "ns/iter",
            "extra": "iterations: 6374616\ncpu: 110.10318786260999 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 116.41359227407881,
            "unit": "ns/iter",
            "extra": "iterations: 6004411\ncpu: 116.40092558620653 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2196.3028859307656,
            "unit": "ns/iter",
            "extra": "iterations: 317991\ncpu: 2195.992421169148 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1023.8306974960175,
            "unit": "ns/iter",
            "extra": "iterations: 693581\ncpu: 1023.7021674469179 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2951.4450584394667,
            "unit": "ns/iter",
            "extra": "iterations: 237425\ncpu: 2951.0739728335243 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1075.3543387970187,
            "unit": "ns/iter",
            "extra": "iterations: 652243\ncpu: 1075.2577674271706 ns\nthreads: 1"
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
          "id": "4c0cb20c25a3d0f6de4d4a78dfde1204a5a87ee5",
          "message": "Fix compiler errors for clang",
          "timestamp": "2025-09-21T17:18:04+08:00",
          "tree_id": "ba7cb9c9e1e4a47eb6d5722ac51b2c4e8fd2176a",
          "url": "https://github.com/afxres/binary-cxx/commit/4c0cb20c25a3d0f6de4d4a78dfde1204a5a87ee5"
        },
        "date": 1758446438934,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 94.62927754683346,
            "unit": "ns/iter",
            "extra": "iterations: 7234725\ncpu: 94.62210132382366 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 49.2698101778581,
            "unit": "ns/iter",
            "extra": "iterations: 13051902\ncpu: 49.26667124837437 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.86552715628363,
            "unit": "ns/iter",
            "extra": "iterations: 20141048\ncpu: 34.8626521817534 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 256.25592676166434,
            "unit": "ns/iter",
            "extra": "iterations: 2741843\ncpu: 256.1959780337532 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 172.40349849664673,
            "unit": "ns/iter",
            "extra": "iterations: 4063574\ncpu: 172.3605867642622 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 141.3759193457602,
            "unit": "ns/iter",
            "extra": "iterations: 4955970\ncpu: 141.34343549295087 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 26.77448609251368,
            "unit": "ns/iter",
            "extra": "iterations: 26153540\ncpu: 26.770841308671795 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.502327021844355,
            "unit": "ns/iter",
            "extra": "iterations: 26400053\ncpu: 26.498312938992964 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 115.57370088865966,
            "unit": "ns/iter",
            "extra": "iterations: 6000294\ncpu: 115.56550112377815 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 116.46888223897845,
            "unit": "ns/iter",
            "extra": "iterations: 6018460\ncpu: 116.46410643254268 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2231.9736628087294,
            "unit": "ns/iter",
            "extra": "iterations: 313549\ncpu: 2231.7968164465537 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 981.0936846896619,
            "unit": "ns/iter",
            "extra": "iterations: 709593\ncpu: 981.0336277274441 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2928.748857628122,
            "unit": "ns/iter",
            "extra": "iterations: 239633\ncpu: 2928.540372152415 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1085.6461629599044,
            "unit": "ns/iter",
            "extra": "iterations: 654971\ncpu: 1085.5979684596725 ns\nthreads: 1"
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
          "id": "47f0867d732333e7445ca4c3f63ef6b4ff8863f4",
          "message": "Fix exception usages",
          "timestamp": "2025-09-21T20:23:45+08:00",
          "tree_id": "f37500f360c7a7e0900b7fb1878fdabda23e701c",
          "url": "https://github.com/afxres/binary-cxx/commit/47f0867d732333e7445ca4c3f63ef6b4ff8863f4"
        },
        "date": 1758457637089,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.02103331333356,
            "unit": "ns/iter",
            "extra": "iterations: 7555443\ncpu: 93.0163251843737 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.83537498854638,
            "unit": "ns/iter",
            "extra": "iterations: 14930696\ncpu: 46.83211164436005 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 35.393255458603285,
            "unit": "ns/iter",
            "extra": "iterations: 19755146\ncpu: 35.38835202736543 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 260.8934075155127,
            "unit": "ns/iter",
            "extra": "iterations: 2695706\ncpu: 260.88081860558987 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.6959618364188,
            "unit": "ns/iter",
            "extra": "iterations: 3993127\ncpu: 175.69140175105872 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 143.707387735984,
            "unit": "ns/iter",
            "extra": "iterations: 4879235\ncpu: 143.67852972853328 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 26.16282117957551,
            "unit": "ns/iter",
            "extra": "iterations: 26683009\ncpu: 26.162449145072042 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.50413195545277,
            "unit": "ns/iter",
            "extra": "iterations: 26414975\ncpu: 26.50218571094616 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 112.03826419513175,
            "unit": "ns/iter",
            "extra": "iterations: 6252477\ncpu: 112.03243722447931 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 120.32235419314114,
            "unit": "ns/iter",
            "extra": "iterations: 5890018\ncpu: 120.30585746936569 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2231.842179736901,
            "unit": "ns/iter",
            "extra": "iterations: 315194\ncpu: 2231.628124266321 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 954.6243912535143,
            "unit": "ns/iter",
            "extra": "iterations: 729573\ncpu: 954.5010889931508 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2976.8750585959756,
            "unit": "ns/iter",
            "extra": "iterations: 236791\ncpu: 2976.381505209229 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1069.5833728182101,
            "unit": "ns/iter",
            "extra": "iterations: 647927\ncpu: 1069.4454236356871 ns\nthreads: 1"
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
          "id": "8a851a5cfe9345492ab7d901ede6fb9573aa8c48",
          "message": "Add token type and unit tests",
          "timestamp": "2025-10-02T22:50:04+08:00",
          "tree_id": "7946367f3ab5b718cb6b1474c2fb0b123b77641b",
          "url": "https://github.com/afxres/binary-cxx/commit/8a851a5cfe9345492ab7d901ede6fb9573aa8c48"
        },
        "date": 1759416744024,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.08302868979213,
            "unit": "ns/iter",
            "extra": "iterations: 7604516\ncpu: 93.0732487116866 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.83515431713438,
            "unit": "ns/iter",
            "extra": "iterations: 14898540\ncpu: 46.823148040009286 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.96945179618538,
            "unit": "ns/iter",
            "extra": "iterations: 20027004\ncpu: 34.96382000023567 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 258.84803886303854,
            "unit": "ns/iter",
            "extra": "iterations: 2696650\ncpu: 258.83758960191363 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.50342216953936,
            "unit": "ns/iter",
            "extra": "iterations: 4001409\ncpu: 175.4946984924562 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 143.3158346994696,
            "unit": "ns/iter",
            "extra": "iterations: 4885429\ncpu: 143.30345748551466 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.900736859336273,
            "unit": "ns/iter",
            "extra": "iterations: 27032975\ncpu: 25.900726242672153 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.458386904451828,
            "unit": "ns/iter",
            "extra": "iterations: 26395597\ncpu: 26.456679157512525 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.446348599319,
            "unit": "ns/iter",
            "extra": "iterations: 6243248\ncpu: 111.44630134827266 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 119.0165166776858,
            "unit": "ns/iter",
            "extra": "iterations: 5878543\ncpu: 119.00720858893109 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2252.3493893080977,
            "unit": "ns/iter",
            "extra": "iterations: 312760\ncpu: 2252.236222662743 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1005.3916800467529,
            "unit": "ns/iter",
            "extra": "iterations: 698177\ncpu: 1005.3337635012313 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2981.9971348778504,
            "unit": "ns/iter",
            "extra": "iterations: 234894\ncpu: 2981.880963328137 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1074.7915041105919,
            "unit": "ns/iter",
            "extra": "iterations: 652339\ncpu: 1074.7391678253164 ns\nthreads: 1"
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
          "id": "2c4bcec60909e448c2f43a90d13b41f836225b0e",
          "message": "Remove locker for token type",
          "timestamp": "2025-10-03T14:38:23+08:00",
          "tree_id": "31eecf366cdd6e0f77fb7ab2e93445832233816c",
          "url": "https://github.com/afxres/binary-cxx/commit/2c4bcec60909e448c2f43a90d13b41f836225b0e"
        },
        "date": 1759474032052,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.84812225392211,
            "unit": "ns/iter",
            "extra": "iterations: 7588992\ncpu: 93.82443966207897 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 47.74975212314258,
            "unit": "ns/iter",
            "extra": "iterations: 14700848\ncpu: 47.75002591687226 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 35.01846578744219,
            "unit": "ns/iter",
            "extra": "iterations: 19803488\ncpu: 35.015674460983846 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 259.4127626226589,
            "unit": "ns/iter",
            "extra": "iterations: 2703927\ncpu: 259.3978217607207 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.32728752773255,
            "unit": "ns/iter",
            "extra": "iterations: 3993733\ncpu: 175.31413517127956 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 143.76650035256253,
            "unit": "ns/iter",
            "extra": "iterations: 4894153\ncpu: 143.76357379918446 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 26.089995514540025,
            "unit": "ns/iter",
            "extra": "iterations: 26940376\ncpu: 26.088700246796876 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.456152811062964,
            "unit": "ns/iter",
            "extra": "iterations: 26454786\ncpu: 26.455602551462714 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.33873207968173,
            "unit": "ns/iter",
            "extra": "iterations: 6286089\ncpu: 111.33267394082382 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 119.02702829247217,
            "unit": "ns/iter",
            "extra": "iterations: 5894749\ncpu: 119.02183740138898 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2259.706109713357,
            "unit": "ns/iter",
            "extra": "iterations: 312797\ncpu: 2259.533262787051 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1017.0335519325403,
            "unit": "ns/iter",
            "extra": "iterations: 688932\ncpu: 1016.9275240517213 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2998.0410401595122,
            "unit": "ns/iter",
            "extra": "iterations: 232772\ncpu: 2997.9951067997913 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1086.1662086199126,
            "unit": "ns/iter",
            "extra": "iterations: 649497\ncpu: 1086.0755800257748 ns\nthreads: 1"
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
          "id": "04647e9e9674fc6a6360a355b8feaef6aa254a0f",
          "message": "Fix signature of generator get converter method",
          "timestamp": "2025-10-03T15:28:20+08:00",
          "tree_id": "d778685c4972d1912fb5f962ad1c88052654b75d",
          "url": "https://github.com/afxres/binary-cxx/commit/04647e9e9674fc6a6360a355b8feaef6aa254a0f"
        },
        "date": 1759476691360,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 95.84947038127574,
            "unit": "ns/iter",
            "extra": "iterations: 7579226\ncpu: 95.84532180462755 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.96414574615152,
            "unit": "ns/iter",
            "extra": "iterations: 14699009\ncpu: 46.95423915993248 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.49967771053776,
            "unit": "ns/iter",
            "extra": "iterations: 20334205\ncpu: 34.49947863710433 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 264.30564260351053,
            "unit": "ns/iter",
            "extra": "iterations: 2637116\ncpu: 264.27246317568137 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.99938450124327,
            "unit": "ns/iter",
            "extra": "iterations: 3978887\ncpu: 175.99549723327138 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 146.5381776003659,
            "unit": "ns/iter",
            "extra": "iterations: 4765936\ncpu: 146.52688391115623 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.932496962436833,
            "unit": "ns/iter",
            "extra": "iterations: 27049642\ncpu: 25.9319139602661 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.008402195393863,
            "unit": "ns/iter",
            "extra": "iterations: 26285035\ncpu: 26.007284905650696 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 112.06560828128946,
            "unit": "ns/iter",
            "extra": "iterations: 6143005\ncpu: 112.06151337985243 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 117.93112340969303,
            "unit": "ns/iter",
            "extra": "iterations: 5913417\ncpu: 117.92558008339343 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2254.9858717596026,
            "unit": "ns/iter",
            "extra": "iterations: 312070\ncpu: 2254.839071362194 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 973.6484104466367,
            "unit": "ns/iter",
            "extra": "iterations: 719353\ncpu: 973.6289763162168 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2963.5021742186473,
            "unit": "ns/iter",
            "extra": "iterations: 234797\ncpu: 2963.3207877443074 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1070.0209372461725,
            "unit": "ns/iter",
            "extra": "iterations: 656199\ncpu: 1070.0013121019686 ns\nthreads: 1"
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
          "id": "1fc8a1ad0d3f6f78d903636e0329d8328e689781",
          "message": "New design for token type",
          "timestamp": "2025-10-04T23:50:19+08:00",
          "tree_id": "0cbea71af5735e0a094ff79d7aa9268751689cd4",
          "url": "https://github.com/afxres/binary-cxx/commit/1fc8a1ad0d3f6f78d903636e0329d8328e689781"
        },
        "date": 1759593113956,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 92.79423507351713,
            "unit": "ns/iter",
            "extra": "iterations: 7556419\ncpu: 92.7898112849486 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 47.08578904803705,
            "unit": "ns/iter",
            "extra": "iterations: 14856605\ncpu: 47.083177145788 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.503675334810644,
            "unit": "ns/iter",
            "extra": "iterations: 20256930\ncpu: 34.50078639754397 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 266.39158652037446,
            "unit": "ns/iter",
            "extra": "iterations: 2632062\ncpu: 266.33952505678036 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 174.91173960837338,
            "unit": "ns/iter",
            "extra": "iterations: 4000866\ncpu: 174.90839583230215 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.43971573502313,
            "unit": "ns/iter",
            "extra": "iterations: 4756548\ncpu: 148.4289699168389 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.986482216954396,
            "unit": "ns/iter",
            "extra": "iterations: 26979350\ncpu: 25.984711529373385 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.465068392230968,
            "unit": "ns/iter",
            "extra": "iterations: 26190621\ncpu: 26.463117884833682 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.70989398306867,
            "unit": "ns/iter",
            "extra": "iterations: 6267395\ncpu: 111.708910480351 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 119.91626515853383,
            "unit": "ns/iter",
            "extra": "iterations: 5834668\ncpu: 119.90799836426005 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2234.034737672075,
            "unit": "ns/iter",
            "extra": "iterations: 313291\ncpu: 2234.009304448581 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 987.0455127094629,
            "unit": "ns/iter",
            "extra": "iterations: 715844\ncpu: 986.943593855646 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 3006.2653930376314,
            "unit": "ns/iter",
            "extra": "iterations: 231988\ncpu: 3006.1055183888852 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1095.3760889762048,
            "unit": "ns/iter",
            "extra": "iterations: 639362\ncpu: 1095.3355125891123 ns\nthreads: 1"
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
          "id": "c8a5eb5ec87afac9427611f63028833c52a251c1",
          "message": "Fix header including",
          "timestamp": "2025-10-05T13:44:18+08:00",
          "tree_id": "345738b6f706a4ff30d653a1d9a5c3a7885c1464",
          "url": "https://github.com/afxres/binary-cxx/commit/c8a5eb5ec87afac9427611f63028833c52a251c1"
        },
        "date": 1759643156732,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 93.45685563801987,
            "unit": "ns/iter",
            "extra": "iterations: 7547846\ncpu: 93.4338477494109 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.90193003141827,
            "unit": "ns/iter",
            "extra": "iterations: 14895457\ncpu: 46.888723118733424 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.46896747155652,
            "unit": "ns/iter",
            "extra": "iterations: 20262851\ncpu: 34.45932919311305 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 267.2954277736296,
            "unit": "ns/iter",
            "extra": "iterations: 2630819\ncpu: 267.2244791450876 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.76945305364245,
            "unit": "ns/iter",
            "extra": "iterations: 3897640\ncpu: 175.7614443612032 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 147.0900753696096,
            "unit": "ns/iter",
            "extra": "iterations: 4766908\ncpu: 147.0525460109573 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.918189631071623,
            "unit": "ns/iter",
            "extra": "iterations: 26541220\ncpu: 25.913012288056073 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.47876115797573,
            "unit": "ns/iter",
            "extra": "iterations: 26457869\ncpu: 26.47620940295686 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.68180348582544,
            "unit": "ns/iter",
            "extra": "iterations: 6260210\ncpu: 111.6699542028144 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 119.85479077389314,
            "unit": "ns/iter",
            "extra": "iterations: 5844849\ncpu: 119.84675446705278 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2251.0725286458396,
            "unit": "ns/iter",
            "extra": "iterations: 310953\ncpu: 2250.623206722557 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 982.941349541694,
            "unit": "ns/iter",
            "extra": "iterations: 712390\ncpu: 982.8796473841569 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 3018.295501706254,
            "unit": "ns/iter",
            "extra": "iterations: 231799\ncpu: 3017.9191972355325 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1059.5798913035223,
            "unit": "ns/iter",
            "extra": "iterations: 658163\ncpu: 1059.517929449087 ns\nthreads: 1"
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
          "id": "9f961a089debd1425008dfd78beee1d4f604a562",
          "message": "Add unit tests for token equality operator",
          "timestamp": "2025-10-06T19:04:52+08:00",
          "tree_id": "96df4b374bec2d934297354d5d8f67e1900ad0d5",
          "url": "https://github.com/afxres/binary-cxx/commit/9f961a089debd1425008dfd78beee1d4f604a562"
        },
        "date": 1759748786450,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 92.41635464187057,
            "unit": "ns/iter",
            "extra": "iterations: 7601426\ncpu: 92.4067126352345 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.884642413930216,
            "unit": "ns/iter",
            "extra": "iterations: 14874167\ncpu: 46.87876127785845 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.45596961333252,
            "unit": "ns/iter",
            "extra": "iterations: 20274680\ncpu: 34.449919752124316 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 264.1802380573199,
            "unit": "ns/iter",
            "extra": "iterations: 2553251\ncpu: 264.14985444047596 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.31382538475214,
            "unit": "ns/iter",
            "extra": "iterations: 3988323\ncpu: 175.3028042111935 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 146.98824128966166,
            "unit": "ns/iter",
            "extra": "iterations: 4676023\ncpu: 146.97021956478815 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.915990051921355,
            "unit": "ns/iter",
            "extra": "iterations: 26898862\ncpu: 25.91380568441893 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 27.777118503123216,
            "unit": "ns/iter",
            "extra": "iterations: 25349408\ncpu: 27.774077051424626 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.86824582295178,
            "unit": "ns/iter",
            "extra": "iterations: 6263809\ncpu: 111.8607890183115 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 120.00651268409841,
            "unit": "ns/iter",
            "extra": "iterations: 5840142\ncpu: 119.99698945676332 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2287.540089580988,
            "unit": "ns/iter",
            "extra": "iterations: 308771\ncpu: 2287.4655910043357 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 991.7362442034954,
            "unit": "ns/iter",
            "extra": "iterations: 707738\ncpu: 991.6969457624151 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 3042.774200141411,
            "unit": "ns/iter",
            "extra": "iterations: 229947\ncpu: 3042.5020809143034 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1087.4815528775487,
            "unit": "ns/iter",
            "extra": "iterations: 641699\ncpu: 1087.3818519274616 ns\nthreads: 1"
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
          "id": "327dff3161d6f7d41a33b1f4a5c2a40d1b5fec89",
          "message": "Fix internal length prefix methods",
          "timestamp": "2025-11-29T19:03:49+08:00",
          "tree_id": "494570659bd0766ab9a13d2140f34c1310111fa7",
          "url": "https://github.com/afxres/binary-cxx/commit/327dff3161d6f7d41a33b1f4a5c2a40d1b5fec89"
        },
        "date": 1764414311982,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 92.2251978091462,
            "unit": "ns/iter",
            "extra": "iterations: 7028492\ncpu: 92.22118898335518 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.940780566241315,
            "unit": "ns/iter",
            "extra": "iterations: 14459375\ncpu: 46.93100282688568 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.53383474322632,
            "unit": "ns/iter",
            "extra": "iterations: 20240659\ncpu: 34.5291844005672 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 270.67772925664735,
            "unit": "ns/iter",
            "extra": "iterations: 2635278\ncpu: 270.624992885001 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 174.83850008275866,
            "unit": "ns/iter",
            "extra": "iterations: 4005581\ncpu: 174.81579775817784 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 147.1100364995721,
            "unit": "ns/iter",
            "extra": "iterations: 4758412\ncpu: 147.0867665515302 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.91674914586662,
            "unit": "ns/iter",
            "extra": "iterations: 27052275\ncpu: 25.91417283758945 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.46138861003269,
            "unit": "ns/iter",
            "extra": "iterations: 26451314\ncpu: 26.458660049931748 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 111.77033362544623,
            "unit": "ns/iter",
            "extra": "iterations: 6269246\ncpu: 111.76306752040051 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 119.93088607764325,
            "unit": "ns/iter",
            "extra": "iterations: 5827943\ncpu: 119.9223894262523 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2262.7755872997545,
            "unit": "ns/iter",
            "extra": "iterations: 309978\ncpu: 2262.5508390918058 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 979.6666652638173,
            "unit": "ns/iter",
            "extra": "iterations: 712842\ncpu: 979.6623403222588 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2940.662355699036,
            "unit": "ns/iter",
            "extra": "iterations: 237611\ncpu: 2940.4904781344285 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1069.8782402132408,
            "unit": "ns/iter",
            "extra": "iterations: 661762\ncpu: 1069.8450182996303 ns\nthreads: 1"
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
          "id": "39ec61e50c95fa2f3089befa926f26f58c43bd8d",
          "message": "Fix code style",
          "timestamp": "2025-12-07T18:05:25+08:00",
          "tree_id": "7bee1c207a9c7032959aede5f9eb41f7aa89fce7",
          "url": "https://github.com/afxres/binary-cxx/commit/39ec61e50c95fa2f3089befa926f26f58c43bd8d"
        },
        "date": 1765102035531,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 92.60439106523539,
            "unit": "ns/iter",
            "extra": "iterations: 7529107\ncpu: 92.60036469132395 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 46.88803966590987,
            "unit": "ns/iter",
            "extra": "iterations: 14733861\ncpu: 46.88381836912944 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.53541866698007,
            "unit": "ns/iter",
            "extra": "iterations: 20229121\ncpu: 34.531031822885424 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 261.4804005372593,
            "unit": "ns/iter",
            "extra": "iterations: 2674308\ncpu: 261.4585724606143 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 170.1209772794867,
            "unit": "ns/iter",
            "extra": "iterations: 4071343\ncpu: 170.1107108882745 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 142.92142096936036,
            "unit": "ns/iter",
            "extra": "iterations: 4904680\ncpu: 142.90872370878432 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.838131828723615,
            "unit": "ns/iter",
            "extra": "iterations: 26959284\ncpu: 25.837164703632315 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.77337125349017,
            "unit": "ns/iter",
            "extra": "iterations: 26142297\ncpu: 26.770758667457567 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 113.97269076135628,
            "unit": "ns/iter",
            "extra": "iterations: 6152753\ncpu: 113.96776353609528 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 116.15930353082648,
            "unit": "ns/iter",
            "extra": "iterations: 6053965\ncpu: 116.14314536010686 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2260.234777973413,
            "unit": "ns/iter",
            "extra": "iterations: 309535\ncpu: 2260.0894793803627 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 966.0892935067958,
            "unit": "ns/iter",
            "extra": "iterations: 724140\ncpu: 965.9633938188741 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2998.4343099624566,
            "unit": "ns/iter",
            "extra": "iterations: 234480\ncpu: 2998.2456286250385 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1069.6989270140493,
            "unit": "ns/iter",
            "extra": "iterations: 654715\ncpu: 1069.6263855265286 ns\nthreads: 1"
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
          "id": "c19f0a2720cb2231b955f12d8c4c0764ccb89b5f",
          "message": "Fix unit tests",
          "timestamp": "2025-12-07T19:18:26+08:00",
          "tree_id": "6b734f8e7054f846d40e82895f7512065010fc93",
          "url": "https://github.com/afxres/binary-cxx/commit/c19f0a2720cb2231b955f12d8c4c0764ccb89b5f"
        },
        "date": 1765106470188,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object",
            "value": 95.40885342048976,
            "unit": "ns/iter",
            "extra": "iterations: 7559406\ncpu: 95.40102317563047 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object",
            "value": 47.73830130044664,
            "unit": "ns/iter",
            "extra": "iterations: 14467997\ncpu: 47.73503436584898 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple",
            "value": 34.420560887356515,
            "unit": "ns/iter",
            "extra": "iterations: 20338237\ncpu: 34.41910343556327 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 263.43697875618534,
            "unit": "ns/iter",
            "extra": "iterations: 2675931\ncpu: 263.41087793369843 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 175.18595112726678,
            "unit": "ns/iter",
            "extra": "iterations: 4097254\ncpu: 175.17683770642475 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 143.4959289770436,
            "unit": "ns/iter",
            "extra": "iterations: 4918297\ncpu: 143.48420276368034 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode Custom Tuple Object",
            "value": 25.87873715359926,
            "unit": "ns/iter",
            "extra": "iterations: 27019628\ncpu: 25.876819436596232 ns\nthreads: 1"
          },
          {
            "name": "Experimental Encode System Tuple",
            "value": 26.755252853200822,
            "unit": "ns/iter",
            "extra": "iterations: 26143173\ncpu: 26.754264908854033 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode Custom Tuple Object",
            "value": 113.8404447545041,
            "unit": "ns/iter",
            "extra": "iterations: 6140826\ncpu: 113.83625329882324 ns\nthreads: 1"
          },
          {
            "name": "Experimental Decode System Tuple",
            "value": 115.67473065146395,
            "unit": "ns/iter",
            "extra": "iterations: 6050896\ncpu: 115.67535055965246 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2306.812014546439,
            "unit": "ns/iter",
            "extra": "iterations: 303582\ncpu: 2306.6037643865584 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1017.2651422382103,
            "unit": "ns/iter",
            "extra": "iterations: 699847\ncpu: 1017.2538183345795 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 3109.3646835566615,
            "unit": "ns/iter",
            "extra": "iterations: 225538\ncpu: 3109.035847617695 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1100.2021646369549,
            "unit": "ns/iter",
            "extra": "iterations: 629482\ncpu: 1100.10735017046 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}