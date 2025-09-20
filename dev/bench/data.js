window.BENCHMARK_DATA = {
  "lastUpdate": 1758363091053,
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
      }
    ]
  }
}