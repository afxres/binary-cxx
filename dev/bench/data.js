window.BENCHMARK_DATA = {
  "lastUpdate": 1744287984257,
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
          "id": "8942f7f4aeb878b256d323c3d45265c52ff57c8f",
          "message": "Fix vector bool usages",
          "timestamp": "2025-02-16T23:32:53+08:00",
          "tree_id": "8f788cb339626234340fcc776c003a49a94476cc",
          "url": "https://github.com/afxres/binary-cxx/commit/8942f7f4aeb878b256d323c3d45265c52ff57c8f"
        },
        "date": 1739720305973,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 112.15171461528136,
            "unit": "ns/iter",
            "extra": "iterations: 6308733\ncpu: 112.14568361032241 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 98.22645720299934,
            "unit": "ns/iter",
            "extra": "iterations: 7214489\ncpu: 98.20768913778926 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 64.73780626398879,
            "unit": "ns/iter",
            "extra": "iterations: 10739387\ncpu: 64.72402475113337 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.50550719001642,
            "unit": "ns/iter",
            "extra": "iterations: 14193990\ncpu: 49.499949133400825 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.297351864714855,
            "unit": "ns/iter",
            "extra": "iterations: 13398749\ncpu: 52.29582142332844 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.55033405108214,
            "unit": "ns/iter",
            "extra": "iterations: 18583086\ncpu: 37.54955613938393 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 268.12730587513784,
            "unit": "ns/iter",
            "extra": "iterations: 2619667\ncpu: 268.1205805928769 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 168.9079281827813,
            "unit": "ns/iter",
            "extra": "iterations: 4147306\ncpu: 168.90423783535635 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 136.169799113122,
            "unit": "ns/iter",
            "extra": "iterations: 5135975\ncpu: 136.1658158382782 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2452.9354187050517,
            "unit": "ns/iter",
            "extra": "iterations: 284138\ncpu: 2452.8822684751744 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2279.4431553158497,
            "unit": "ns/iter",
            "extra": "iterations: 305719\ncpu: 2279.363147203806 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1187.8244062333065,
            "unit": "ns/iter",
            "extra": "iterations: 590636\ncpu: 1187.7624713021207 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 1008.8865804310702,
            "unit": "ns/iter",
            "extra": "iterations: 693681\ncpu: 1008.8370000043248 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2924.857812794614,
            "unit": "ns/iter",
            "extra": "iterations: 238615\ncpu: 2924.656790226937 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1182.8696422479993,
            "unit": "ns/iter",
            "extra": "iterations: 589263\ncpu: 1182.8207557576145 ns\nthreads: 1"
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
          "id": "f64e64ab71951b249d1f52c89587f9f3e8b29756",
          "message": "Fix lambda function usages",
          "timestamp": "2025-02-17T22:47:21+08:00",
          "tree_id": "8d0729edd4805c03cfe401ea611353adad676c2b",
          "url": "https://github.com/afxres/binary-cxx/commit/f64e64ab71951b249d1f52c89587f9f3e8b29756"
        },
        "date": 1739803749178,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 114.87584530910907,
            "unit": "ns/iter",
            "extra": "iterations: 6300358\ncpu: 114.85988637471077 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.45984605417262,
            "unit": "ns/iter",
            "extra": "iterations: 6735876\ncpu: 97.45536898244562 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 62.883484870013575,
            "unit": "ns/iter",
            "extra": "iterations: 11105562\ncpu: 62.87376460551931 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.55614872786221,
            "unit": "ns/iter",
            "extra": "iterations: 14167890\ncpu: 49.55296300295951 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.44680632434438,
            "unit": "ns/iter",
            "extra": "iterations: 13371505\ncpu: 52.43945801164494 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.486453962587674,
            "unit": "ns/iter",
            "extra": "iterations: 18645748\ncpu: 37.482344982888335 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 270.73147262483445,
            "unit": "ns/iter",
            "extra": "iterations: 2639783\ncpu: 270.6941888784041 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 170.60788406673103,
            "unit": "ns/iter",
            "extra": "iterations: 4169295\ncpu: 170.5908377795288 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 136.798152799017,
            "unit": "ns/iter",
            "extra": "iterations: 4984731\ncpu: 136.7945493949421 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2469.3206414018855,
            "unit": "ns/iter",
            "extra": "iterations: 285562\ncpu: 2469.271909427723 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2262.240850017341,
            "unit": "ns/iter",
            "extra": "iterations: 311476\ncpu: 2262.160644800884 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1178.5204002703977,
            "unit": "ns/iter",
            "extra": "iterations: 594698\ncpu: 1178.5015436406393 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 1000.4814084040106,
            "unit": "ns/iter",
            "extra": "iterations: 693835\ncpu: 1000.4500061253763 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2974.6063818059974,
            "unit": "ns/iter",
            "extra": "iterations: 235858\ncpu: 2974.4102765223142 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1095.3694400813015,
            "unit": "ns/iter",
            "extra": "iterations: 641736\ncpu: 1095.334087537555 ns\nthreads: 1"
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
          "id": "bd986db0e6fbdb9c4f0b694302a9cc23b8e6ec05",
          "message": "Fix static initialization flags",
          "timestamp": "2025-02-22T23:55:39+08:00",
          "tree_id": "7c7670827621c443b0e212409dc0abb9a10d3b57",
          "url": "https://github.com/afxres/binary-cxx/commit/bd986db0e6fbdb9c4f0b694302a9cc23b8e6ec05"
        },
        "date": 1740239847726,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 112.74831459077973,
            "unit": "ns/iter",
            "extra": "iterations: 6335405\ncpu: 112.72376998786976 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 98.62932343381749,
            "unit": "ns/iter",
            "extra": "iterations: 7210588\ncpu: 98.62689644728003 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.301170125372835,
            "unit": "ns/iter",
            "extra": "iterations: 11089410\ncpu: 63.29792405547276 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.33440720407571,
            "unit": "ns/iter",
            "extra": "iterations: 14113120\ncpu: 49.3312922302085 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.88008716917344,
            "unit": "ns/iter",
            "extra": "iterations: 13310669\ncpu: 52.877818913534725 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.19984658347445,
            "unit": "ns/iter",
            "extra": "iterations: 18901484\ncpu: 37.198207717446934 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 267.108836403557,
            "unit": "ns/iter",
            "extra": "iterations: 2613767\ncpu: 267.0867961834396 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 167.9809361456295,
            "unit": "ns/iter",
            "extra": "iterations: 4146748\ncpu: 167.9689052722761 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 137.14397928085694,
            "unit": "ns/iter",
            "extra": "iterations: 5088628\ncpu: 137.1222307859801 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2442.2909229334596,
            "unit": "ns/iter",
            "extra": "iterations: 286337\ncpu: 2442.2038472149984 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2258.209413621318,
            "unit": "ns/iter",
            "extra": "iterations: 311761\ncpu: 2258.131953643976 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1179.9547182849312,
            "unit": "ns/iter",
            "extra": "iterations: 590437\ncpu: 1179.9346534854699 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 1013.8773075404553,
            "unit": "ns/iter",
            "extra": "iterations: 686391\ncpu: 1013.8501728606576 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2938.4052663273173,
            "unit": "ns/iter",
            "extra": "iterations: 237471\ncpu: 2938.298432229615 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1090.9865538467259,
            "unit": "ns/iter",
            "extra": "iterations: 643976\ncpu: 1090.9541240667377 ns\nthreads: 1"
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
          "id": "fdca22657436f4e23b86160c0d4379b689c90c61",
          "message": "Update cmake lists",
          "timestamp": "2025-02-23T21:17:43+08:00",
          "tree_id": "3f9bc92861e9f32c3f57e35f6e51060c0b0f32d7",
          "url": "https://github.com/afxres/binary-cxx/commit/fdca22657436f4e23b86160c0d4379b689c90c61"
        },
        "date": 1740316728890,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 110.32527779049391,
            "unit": "ns/iter",
            "extra": "iterations: 6291072\ncpu: 110.31691292040531 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.06752408634974,
            "unit": "ns/iter",
            "extra": "iterations: 7216225\ncpu: 97.04822396751764 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 62.845129762137226,
            "unit": "ns/iter",
            "extra": "iterations: 11144969\ncpu: 62.84100556941879 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.412237978516785,
            "unit": "ns/iter",
            "extra": "iterations: 14200744\ncpu: 49.409690928869615 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.14749202111123,
            "unit": "ns/iter",
            "extra": "iterations: 13463969\ncpu: 52.143245502124934 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.17689246926312,
            "unit": "ns/iter",
            "extra": "iterations: 18742669\ncpu: 37.17615340696675 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 264.6898016154407,
            "unit": "ns/iter",
            "extra": "iterations: 2638663\ncpu: 264.6701393849839 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 167.49307339650278,
            "unit": "ns/iter",
            "extra": "iterations: 4138031\ncpu: 167.48960000541325 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 136.9485047123164,
            "unit": "ns/iter",
            "extra": "iterations: 5104603\ncpu: 136.94396077422658 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2532.7117447273918,
            "unit": "ns/iter",
            "extra": "iterations: 279419\ncpu: 2532.6834503022355 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2324.424343357827,
            "unit": "ns/iter",
            "extra": "iterations: 302029\ncpu: 2324.334246049223 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1180.4556207701091,
            "unit": "ns/iter",
            "extra": "iterations: 589848\ncpu: 1180.4211661309369 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 1014.5406468694757,
            "unit": "ns/iter",
            "extra": "iterations: 696462\ncpu: 1014.5205266044672 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2952.1691583890924,
            "unit": "ns/iter",
            "extra": "iterations: 236784\ncpu: 2952.075596324074 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1098.026202370546,
            "unit": "ns/iter",
            "extra": "iterations: 638759\ncpu: 1098.015758682068 ns\nthreads: 1"
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
          "id": "92fe2cde6b43c0e99842f51477ba96be672f6ac4",
          "message": "Fix decode auto method",
          "timestamp": "2025-03-10T23:26:24+08:00",
          "tree_id": "9bff5bf5730a1d5e87a39d352214d16f5d759112",
          "url": "https://github.com/afxres/binary-cxx/commit/92fe2cde6b43c0e99842f51477ba96be672f6ac4"
        },
        "date": 1741620446717,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 115.37835138141313,
            "unit": "ns/iter",
            "extra": "iterations: 5971642\ncpu: 115.37741478809346 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 101.78425773437692,
            "unit": "ns/iter",
            "extra": "iterations: 6910060\ncpu: 101.78484658599201 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 64.89344452609382,
            "unit": "ns/iter",
            "extra": "iterations: 10969779\ncpu: 64.89167229348924 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.73083995399689,
            "unit": "ns/iter",
            "extra": "iterations: 14101558\ncpu: 49.73111666101009 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 53.39421199730585,
            "unit": "ns/iter",
            "extra": "iterations: 13175875\ncpu: 53.39335528000983 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.587087841186616,
            "unit": "ns/iter",
            "extra": "iterations: 16866769\ncpu: 37.58729529052071 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 281.23262434886794,
            "unit": "ns/iter",
            "extra": "iterations: 2470670\ncpu: 281.2305823926303 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 182.14731910355513,
            "unit": "ns/iter",
            "extra": "iterations: 3855576\ncpu: 182.14833607222374 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 150.81440094339172,
            "unit": "ns/iter",
            "extra": "iterations: 4787853\ncpu: 150.80812067538403 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2455.169566457514,
            "unit": "ns/iter",
            "extra": "iterations: 287492\ncpu: 2455.119349407981 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2300.465199427232,
            "unit": "ns/iter",
            "extra": "iterations: 303745\ncpu: 2300.386264794483 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1150.3535970433772,
            "unit": "ns/iter",
            "extra": "iterations: 610418\ncpu: 1150.3496620348672 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 1032.8805939610293,
            "unit": "ns/iter",
            "extra": "iterations: 684220\ncpu: 1032.873581596563 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2930.504478409237,
            "unit": "ns/iter",
            "extra": "iterations: 239594\ncpu: 2930.435081846789 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1093.1059429426327,
            "unit": "ns/iter",
            "extra": "iterations: 640373\ncpu: 1093.1141178656824 ns\nthreads: 1"
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
          "id": "98e67661e68cb7978b57c98cad0edf34b64577cc",
          "message": "Fix lcov errors for range",
          "timestamp": "2025-03-10T23:43:14+08:00",
          "tree_id": "df04c2bc7111245702a794735497a59e2f131d79",
          "url": "https://github.com/afxres/binary-cxx/commit/98e67661e68cb7978b57c98cad0edf34b64577cc"
        },
        "date": 1741621462413,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 111.10802621992605,
            "unit": "ns/iter",
            "extra": "iterations: 6309857\ncpu: 111.10696803429936 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 99.24730261137557,
            "unit": "ns/iter",
            "extra": "iterations: 7147005\ncpu: 99.24295449632399 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.89691012654831,
            "unit": "ns/iter",
            "extra": "iterations: 10968022\ncpu: 63.89622085003112 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.67851512414153,
            "unit": "ns/iter",
            "extra": "iterations: 13964265\ncpu: 49.676062005411644 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 53.40641119747034,
            "unit": "ns/iter",
            "extra": "iterations: 13116676\ncpu: 53.404674629456416 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 39.2435555735346,
            "unit": "ns/iter",
            "extra": "iterations: 17797860\ncpu: 39.24200313970332 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 284.64989752030556,
            "unit": "ns/iter",
            "extra": "iterations: 2457072\ncpu: 284.6381481698544 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 180.96443151668458,
            "unit": "ns/iter",
            "extra": "iterations: 3853552\ncpu: 180.95484321996946 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.13818083075083,
            "unit": "ns/iter",
            "extra": "iterations: 4680642\ncpu: 148.13860641339386 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2421.3992824087027,
            "unit": "ns/iter",
            "extra": "iterations: 290416\ncpu: 2421.3725552311153 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2227.5482919126043,
            "unit": "ns/iter",
            "extra": "iterations: 312806\ncpu: 2227.2885366648993 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1136.0232709411703,
            "unit": "ns/iter",
            "extra": "iterations: 616477\ncpu: 1136.0269904635525 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 984.3964465517794,
            "unit": "ns/iter",
            "extra": "iterations: 713279\ncpu: 984.3561495571859 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2956.961714992682,
            "unit": "ns/iter",
            "extra": "iterations: 236829\ncpu: 2956.8535441183285 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1074.145625516237,
            "unit": "ns/iter",
            "extra": "iterations: 645299\ncpu: 1074.0820162436337 ns\nthreads: 1"
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
          "id": "7dfff12e1db8a4eeacd4801b55f9f29061e3c7f3",
          "message": "Fix allocator resize method",
          "timestamp": "2025-03-15T23:08:32+08:00",
          "tree_id": "d181b8cbbe55eb240545b041ee836c315cd2becc",
          "url": "https://github.com/afxres/binary-cxx/commit/7dfff12e1db8a4eeacd4801b55f9f29061e3c7f3"
        },
        "date": 1742051444109,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 112.45586873240593,
            "unit": "ns/iter",
            "extra": "iterations: 6287005\ncpu: 112.45344961551645 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 98.71242127427705,
            "unit": "ns/iter",
            "extra": "iterations: 7068687\ncpu: 98.70202401096556 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 65.01013372334891,
            "unit": "ns/iter",
            "extra": "iterations: 10756461\ncpu: 64.99967656648407 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 51.47453288054097,
            "unit": "ns/iter",
            "extra": "iterations: 13602088\ncpu: 51.474162349192255 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.53541130507093,
            "unit": "ns/iter",
            "extra": "iterations: 13382986\ncpu: 52.53331244611632 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 40.03858174253764,
            "unit": "ns/iter",
            "extra": "iterations: 17280868\ncpu: 40.038284882449204 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 283.8655705505037,
            "unit": "ns/iter",
            "extra": "iterations: 2462087\ncpu: 283.85992980751683 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 203.63917557552773,
            "unit": "ns/iter",
            "extra": "iterations: 3438617\ncpu: 203.63770608939583 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 153.11709524134423,
            "unit": "ns/iter",
            "extra": "iterations: 4560971\ncpu: 153.11145938003105 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2472.857933351432,
            "unit": "ns/iter",
            "extra": "iterations: 283367\ncpu: 2472.665698546408 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2285.7898107915094,
            "unit": "ns/iter",
            "extra": "iterations: 305853\ncpu: 2285.6732678770486 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1179.9411800150729,
            "unit": "ns/iter",
            "extra": "iterations: 597450\ncpu: 1179.8803347560458 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 989.8892717840583,
            "unit": "ns/iter",
            "extra": "iterations: 697609\ncpu: 989.8274133504582 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2943.3604159950455,
            "unit": "ns/iter",
            "extra": "iterations: 238849\ncpu: 2943.1770825919352 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1102.580760915384,
            "unit": "ns/iter",
            "extra": "iterations: 647089\ncpu: 1102.5598565266905 ns\nthreads: 1"
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
          "id": "ffd6dce9476b116cf1f384a9b6a315cfe4f1a7cf",
          "message": "Remove unused header",
          "timestamp": "2025-03-16T14:49:43+08:00",
          "tree_id": "446a3ae8c2209f2ba0865855216a1886dfd0f2e3",
          "url": "https://github.com/afxres/binary-cxx/commit/ffd6dce9476b116cf1f384a9b6a315cfe4f1a7cf"
        },
        "date": 1742107865730,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 111.11598932109936,
            "unit": "ns/iter",
            "extra": "iterations: 6317504\ncpu: 111.1155685853147 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.89354552473017,
            "unit": "ns/iter",
            "extra": "iterations: 7164161\ncpu: 97.88367137477789 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 64.21049316941655,
            "unit": "ns/iter",
            "extra": "iterations: 11019702\ncpu: 64.20938052589807 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 51.570043108350504,
            "unit": "ns/iter",
            "extra": "iterations: 13631234\ncpu: 51.56774537066857 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.55858253952108,
            "unit": "ns/iter",
            "extra": "iterations: 13312738\ncpu: 52.55779412169006 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 40.8931520100927,
            "unit": "ns/iter",
            "extra": "iterations: 17558992\ncpu: 40.8915360858983 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 285.252795986148,
            "unit": "ns/iter",
            "extra": "iterations: 2466661\ncpu: 285.2470667838024 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 187.69412244920022,
            "unit": "ns/iter",
            "extra": "iterations: 3723830\ncpu: 187.68988702491805 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 151.88153305484585,
            "unit": "ns/iter",
            "extra": "iterations: 4600279\ncpu: 151.87751308127184 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2417.3654587270366,
            "unit": "ns/iter",
            "extra": "iterations: 289584\ncpu: 2417.304678435272 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2243.208289132759,
            "unit": "ns/iter",
            "extra": "iterations: 311082\ncpu: 2243.0470519027135 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1186.6194016261243,
            "unit": "ns/iter",
            "extra": "iterations: 593074\ncpu: 1186.5687384710852 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 998.4200065061015,
            "unit": "ns/iter",
            "extra": "iterations: 700882\ncpu: 998.3469385716851 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2929.790060326608,
            "unit": "ns/iter",
            "extra": "iterations: 239364\ncpu: 2929.6558797480006 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1089.3624440267783,
            "unit": "ns/iter",
            "extra": "iterations: 651204\ncpu: 1089.341238690182 ns\nthreads: 1"
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
          "id": "7db11a9eb06972585aaa62311d3209f11c6956cd",
          "message": "Use const modifier for shared_ptr parameters",
          "timestamp": "2025-03-19T23:00:13+08:00",
          "tree_id": "c329e0878180cf2bb5992c7dcc0064a2221037a5",
          "url": "https://github.com/afxres/binary-cxx/commit/7db11a9eb06972585aaa62311d3209f11c6956cd"
        },
        "date": 1742396594139,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 110.44520400359873,
            "unit": "ns/iter",
            "extra": "iterations: 5392748\ncpu: 110.43718898046042 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.39038413422712,
            "unit": "ns/iter",
            "extra": "iterations: 7186186\ncpu: 97.38665976639066 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.896176593349274,
            "unit": "ns/iter",
            "extra": "iterations: 10872346\ncpu: 63.89204068744686 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.575185691422426,
            "unit": "ns/iter",
            "extra": "iterations: 14009667\ncpu: 49.57167411616565 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 52.882169458317215,
            "unit": "ns/iter",
            "extra": "iterations: 13131536\ncpu: 52.87905641807633 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.8756127389149,
            "unit": "ns/iter",
            "extra": "iterations: 18432402\ncpu: 37.872900015961 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 283.7087538074969,
            "unit": "ns/iter",
            "extra": "iterations: 2437625\ncpu: 283.68773539818494 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 187.06365399640285,
            "unit": "ns/iter",
            "extra": "iterations: 3739938\ncpu: 187.05282119650127 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 151.2129994634217,
            "unit": "ns/iter",
            "extra": "iterations: 4580866\ncpu: 151.20593355055578 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2446.2625583415934,
            "unit": "ns/iter",
            "extra": "iterations: 285388\ncpu: 2446.0034689615522 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2271.8906588939017,
            "unit": "ns/iter",
            "extra": "iterations: 311173\ncpu: 2271.7948858030763 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1203.7133203093997,
            "unit": "ns/iter",
            "extra": "iterations: 601968\ncpu: 1203.623649429872 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 985.3511338070693,
            "unit": "ns/iter",
            "extra": "iterations: 711629\ncpu: 985.2874194278198 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2926.192205962393,
            "unit": "ns/iter",
            "extra": "iterations: 237053\ncpu: 2926.0455045917997 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1082.2110204137928,
            "unit": "ns/iter",
            "extra": "iterations: 651373\ncpu: 1082.1405876510062 ns\nthreads: 1"
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
          "id": "1b5652cfe50939078bb2298f720fca4c6453a5ed",
          "message": "Fix support for template object types",
          "timestamp": "2025-03-23T15:59:27+08:00",
          "tree_id": "ef404723e478b741b45f2b6f3719775f68465731",
          "url": "https://github.com/afxres/binary-cxx/commit/1b5652cfe50939078bb2298f720fca4c6453a5ed"
        },
        "date": 1742716908319,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 111.02529516939195,
            "unit": "ns/iter",
            "extra": "iterations: 6347457\ncpu: 111.00089264094267 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 102.7007004760696,
            "unit": "ns/iter",
            "extra": "iterations: 7178832\ncpu: 102.68415391250278 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.335801449755984,
            "unit": "ns/iter",
            "extra": "iterations: 11030679\ncpu: 63.330085935779636 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.31038809486914,
            "unit": "ns/iter",
            "extra": "iterations: 14168546\ncpu: 49.30977645836066 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.174345919874995,
            "unit": "ns/iter",
            "extra": "iterations: 13886181\ncpu: 50.17301402019747 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.37512632506335,
            "unit": "ns/iter",
            "extra": "iterations: 18771018\ncpu: 37.37424768331693 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 284.76126048133034,
            "unit": "ns/iter",
            "extra": "iterations: 2489303\ncpu: 284.7527781873077 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 183.49876477392795,
            "unit": "ns/iter",
            "extra": "iterations: 3822782\ncpu: 183.49366116090323 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 149.39524818079087,
            "unit": "ns/iter",
            "extra": "iterations: 4778170\ncpu: 149.39225603107442 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2476.954065619614,
            "unit": "ns/iter",
            "extra": "iterations: 285799\ncpu: 2476.8522143184578 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2266.248756620718,
            "unit": "ns/iter",
            "extra": "iterations: 309439\ncpu: 2266.172295670555 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1134.876976431504,
            "unit": "ns/iter",
            "extra": "iterations: 618792\ncpu: 1134.835590957866 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 990.1908374141503,
            "unit": "ns/iter",
            "extra": "iterations: 709625\ncpu: 990.1801190769772 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2940.258678667739,
            "unit": "ns/iter",
            "extra": "iterations: 238199\ncpu: 2940.160622000932 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1082.188080833151,
            "unit": "ns/iter",
            "extra": "iterations: 627762\ncpu: 1082.17518900475 ns\nthreads: 1"
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
          "id": "53cb727ecd5cfbc6f2ecafa203de764bf5266d7d",
          "message": "Fix lambda captures",
          "timestamp": "2025-03-23T16:20:38+08:00",
          "tree_id": "936076894b63dece82d1577cfc472934cb6b19de",
          "url": "https://github.com/afxres/binary-cxx/commit/53cb727ecd5cfbc6f2ecafa203de764bf5266d7d"
        },
        "date": 1742718167986,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 112.90139429002654,
            "unit": "ns/iter",
            "extra": "iterations: 6392429\ncpu: 112.9000378416405 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 96.76028523395264,
            "unit": "ns/iter",
            "extra": "iterations: 7184839\ncpu: 96.75983776393599 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 92.38902317218108,
            "unit": "ns/iter",
            "extra": "iterations: 7588021\ncpu: 92.37012351441832 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 51.67497859999912,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 51.66986970000002 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 84.1087131123972,
            "unit": "ns/iter",
            "extra": "iterations: 7354605\ncpu: 84.10808180724862 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.329093087213856,
            "unit": "ns/iter",
            "extra": "iterations: 18721712\ncpu: 37.32902065793981 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 277.99349958992127,
            "unit": "ns/iter",
            "extra": "iterations: 2510457\ncpu: 277.9862379638447 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 181.01212237956992,
            "unit": "ns/iter",
            "extra": "iterations: 3929839\ncpu: 181.01164958666254 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 147.71153370980278,
            "unit": "ns/iter",
            "extra": "iterations: 4771535\ncpu: 147.71217417455807 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2468.9008367262522,
            "unit": "ns/iter",
            "extra": "iterations: 285398\ncpu: 2468.878355839915 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2244.069740756137,
            "unit": "ns/iter",
            "extra": "iterations: 297172\ncpu: 2243.988444402568 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1130.5172638384051,
            "unit": "ns/iter",
            "extra": "iterations: 621820\ncpu: 1130.4655270013827 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 974.9886333693529,
            "unit": "ns/iter",
            "extra": "iterations: 717275\ncpu: 974.956957931059 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2931.7470959163143,
            "unit": "ns/iter",
            "extra": "iterations: 233120\ncpu: 2931.6117064172972 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1081.7573008248544,
            "unit": "ns/iter",
            "extra": "iterations: 647872\ncpu: 1081.752625518621 ns\nthreads: 1"
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
          "id": "5d41affa56979103a13f1488567176cfeada5d54",
          "message": "Fix code style for tuple converter",
          "timestamp": "2025-04-02T23:55:17+08:00",
          "tree_id": "f3001aab93843c1c0709320c9f097574aaf7da22",
          "url": "https://github.com/afxres/binary-cxx/commit/5d41affa56979103a13f1488567176cfeada5d54"
        },
        "date": 1743609379816,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 111.53273726333252,
            "unit": "ns/iter",
            "extra": "iterations: 6360886\ncpu: 111.52587312522186 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.76088716922919,
            "unit": "ns/iter",
            "extra": "iterations: 7173513\ncpu: 97.75713126887759 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.810192223818845,
            "unit": "ns/iter",
            "extra": "iterations: 10975799\ncpu: 63.809277301816486 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.82849444034672,
            "unit": "ns/iter",
            "extra": "iterations: 14089724\ncpu: 49.82800010844785 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.79281164531605,
            "unit": "ns/iter",
            "extra": "iterations: 13839523\ncpu: 50.791471425713205 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 38.93674021565389,
            "unit": "ns/iter",
            "extra": "iterations: 18028800\ncpu: 38.93517843672349 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 284.5938637649139,
            "unit": "ns/iter",
            "extra": "iterations: 2459293\ncpu: 284.56227297845345 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 182.8735415943345,
            "unit": "ns/iter",
            "extra": "iterations: 3776127\ncpu: 182.8644314664204 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.24624892090694,
            "unit": "ns/iter",
            "extra": "iterations: 4709978\ncpu: 148.23950876203676 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2446.88331942614,
            "unit": "ns/iter",
            "extra": "iterations: 286423\ncpu: 2446.7815433816445 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2267.7307498970004,
            "unit": "ns/iter",
            "extra": "iterations: 308349\ncpu: 2267.6420322426875 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1130.703587750511,
            "unit": "ns/iter",
            "extra": "iterations: 623176\ncpu: 1130.6382177747553 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 988.1783849655853,
            "unit": "ns/iter",
            "extra": "iterations: 718833\ncpu: 988.1089502012297 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2926.4684227905364,
            "unit": "ns/iter",
            "extra": "iterations: 239239\ncpu: 2926.1993320487045 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1075.6037487014473,
            "unit": "ns/iter",
            "extra": "iterations: 653613\ncpu: 1075.5281764591577 ns\nthreads: 1"
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
          "id": "2e55e3aff2f7a4a09c5057c974a46bae67d7f836",
          "message": "Add variant converter",
          "timestamp": "2025-04-03T21:53:59+08:00",
          "tree_id": "daa28b11dd67045019d69625bbe93a038fc29a57",
          "url": "https://github.com/afxres/binary-cxx/commit/2e55e3aff2f7a4a09c5057c974a46bae67d7f836"
        },
        "date": 1743688509863,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 112.05676543825004,
            "unit": "ns/iter",
            "extra": "iterations: 6298269\ncpu: 112.02560354281472 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 98.07387105730412,
            "unit": "ns/iter",
            "extra": "iterations: 7063091\ncpu: 98.05953300049512 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.644961821281576,
            "unit": "ns/iter",
            "extra": "iterations: 11069387\ncpu: 63.63896185037168 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 50.43260160000216,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.4321585 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.0239855000018,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.01259570000003 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 36.91396323637425,
            "unit": "ns/iter",
            "extra": "iterations: 18880673\ncpu: 36.90946858726911 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 280.33329192501327,
            "unit": "ns/iter",
            "extra": "iterations: 2511573\ncpu: 280.3066508518763 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 183.12043008273164,
            "unit": "ns/iter",
            "extra": "iterations: 3816289\ncpu: 183.10150069871543 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.46422562922157,
            "unit": "ns/iter",
            "extra": "iterations: 4724849\ncpu: 148.46121558593728 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2421.525523275545,
            "unit": "ns/iter",
            "extra": "iterations: 289618\ncpu: 2421.3902865153414 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2230.1539732166034,
            "unit": "ns/iter",
            "extra": "iterations: 316016\ncpu: 2230.1354140296694 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1154.6504779267018,
            "unit": "ns/iter",
            "extra": "iterations: 608880\ncpu: 1154.559942845881 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 987.1183511874286,
            "unit": "ns/iter",
            "extra": "iterations: 710014\ncpu: 987.0626367930781 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2948.479701339607,
            "unit": "ns/iter",
            "extra": "iterations: 237996\ncpu: 2948.3395393199894 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1080.405364979014,
            "unit": "ns/iter",
            "extra": "iterations: 645818\ncpu: 1080.3137106739061 ns\nthreads: 1"
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
          "id": "689706055c7a04392b99e03cf405db233011c843",
          "message": "Add unit tests for tuple converter and variant converter",
          "timestamp": "2025-04-05T22:21:57+08:00",
          "tree_id": "fd2c6f9e57ce19a9d7427f397a4d154f939cad54",
          "url": "https://github.com/afxres/binary-cxx/commit/689706055c7a04392b99e03cf405db233011c843"
        },
        "date": 1743863160501,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 110.25821498888565,
            "unit": "ns/iter",
            "extra": "iterations: 6326941\ncpu: 110.25007250739337 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.5435387370304,
            "unit": "ns/iter",
            "extra": "iterations: 7189322\ncpu: 97.52646661256789 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 65.01854923967724,
            "unit": "ns/iter",
            "extra": "iterations: 10835215\ncpu: 65.01344514160539 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 50.123729000000594,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.123375200000005 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.217541485701354,
            "unit": "ns/iter",
            "extra": "iterations: 13970356\ncpu: 50.214876700350395 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.475134021128895,
            "unit": "ns/iter",
            "extra": "iterations: 18754319\ncpu: 37.47486501642633 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 280.5385283179966,
            "unit": "ns/iter",
            "extra": "iterations: 2513437\ncpu: 280.5365318486201 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 185.24996143505993,
            "unit": "ns/iter",
            "extra": "iterations: 3811752\ncpu: 185.24979405795565 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 150.218116554149,
            "unit": "ns/iter",
            "extra": "iterations: 4657166\ncpu: 150.22177757889682 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2437.6138207317344,
            "unit": "ns/iter",
            "extra": "iterations: 290057\ncpu: 2437.451380245953 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2220.1406661722517,
            "unit": "ns/iter",
            "extra": "iterations: 316885\ncpu: 2220.0758918850715 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1163.6118510631711,
            "unit": "ns/iter",
            "extra": "iterations: 602967\ncpu: 1163.590591193216 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 982.6313755926323,
            "unit": "ns/iter",
            "extra": "iterations: 711228\ncpu: 982.5980177945752 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2940.9052204849577,
            "unit": "ns/iter",
            "extra": "iterations: 237794\ncpu: 2940.754013978487 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1077.792549726899,
            "unit": "ns/iter",
            "extra": "iterations: 650956\ncpu: 1077.7591342579221 ns\nthreads: 1"
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
          "id": "5021f91f45dc62d2bfafe0ce6c4fe449edea35c6",
          "message": "Fix compiler errors for MSVC",
          "timestamp": "2025-04-05T22:41:09+08:00",
          "tree_id": "b68248f2fe76b18eb737bf24ecec1a2d95832a97",
          "url": "https://github.com/afxres/binary-cxx/commit/5021f91f45dc62d2bfafe0ce6c4fe449edea35c6"
        },
        "date": 1743864144184,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 114.25076777025338,
            "unit": "ns/iter",
            "extra": "iterations: 6347602\ncpu: 114.2505491050006 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.42777040875423,
            "unit": "ns/iter",
            "extra": "iterations: 7152311\ncpu: 97.42540501944055 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 64.63313659400902,
            "unit": "ns/iter",
            "extra": "iterations: 10866494\ncpu: 64.62349944701576 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 50.109730899998794,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.09855399999998 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.35767070000077,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.35547040000004 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.08919934773203,
            "unit": "ns/iter",
            "extra": "iterations: 18742581\ncpu: 37.08939270423853 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 285.2684590118176,
            "unit": "ns/iter",
            "extra": "iterations: 2462063\ncpu: 285.25814367869555 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 185.06803661903132,
            "unit": "ns/iter",
            "extra": "iterations: 3766457\ncpu: 185.06708161011807 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.7185304723269,
            "unit": "ns/iter",
            "extra": "iterations: 4711963\ncpu: 148.70953316059584 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2441.1759986697684,
            "unit": "ns/iter",
            "extra": "iterations: 288684\ncpu: 2441.1428828753956 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2253.387825037854,
            "unit": "ns/iter",
            "extra": "iterations: 311656\ncpu: 2253.2527434093977 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1126.3704516049834,
            "unit": "ns/iter",
            "extra": "iterations: 621428\ncpu: 1126.3604890671174 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 990.6835162292697,
            "unit": "ns/iter",
            "extra": "iterations: 708782\ncpu: 990.65628782898 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2929.5743876314064,
            "unit": "ns/iter",
            "extra": "iterations: 238541\ncpu: 2929.527884095396 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1064.7681211799204,
            "unit": "ns/iter",
            "extra": "iterations: 658525\ncpu: 1064.7593637295454 ns\nthreads: 1"
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
          "id": "d51f9c6c7a830492ea2fffb706dfcb2654eef4f1",
          "message": "Fix variant converter encode method for invalid value",
          "timestamp": "2025-04-07T23:18:32+08:00",
          "tree_id": "af74b1962f46386dbdecaf881cab5d989f77421b",
          "url": "https://github.com/afxres/binary-cxx/commit/d51f9c6c7a830492ea2fffb706dfcb2654eef4f1"
        },
        "date": 1744039222199,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 109.9869040515629,
            "unit": "ns/iter",
            "extra": "iterations: 6329973\ncpu: 109.98072456233227 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.34068844843345,
            "unit": "ns/iter",
            "extra": "iterations: 7038639\ncpu: 97.33525401714734 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 64.002198297976,
            "unit": "ns/iter",
            "extra": "iterations: 10905255\ncpu: 63.99961082982472 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.63255486503614,
            "unit": "ns/iter",
            "extra": "iterations: 14059318\ncpu: 49.63227241890394 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.82805679644894,
            "unit": "ns/iter",
            "extra": "iterations: 13876431\ncpu: 50.82658293043796 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.000974702285696,
            "unit": "ns/iter",
            "extra": "iterations: 18879611\ncpu: 37.000868344162384 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 279.4518783206018,
            "unit": "ns/iter",
            "extra": "iterations: 2384923\ncpu: 279.446515883322 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 182.88657116692278,
            "unit": "ns/iter",
            "extra": "iterations: 3833937\ncpu: 182.88002437181413 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 148.36403464659386,
            "unit": "ns/iter",
            "extra": "iterations: 4722773\ncpu: 148.36129917741133 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2440.7946037910733,
            "unit": "ns/iter",
            "extra": "iterations: 286831\ncpu: 2440.7691044552357 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2245.6604971625643,
            "unit": "ns/iter",
            "extra": "iterations: 312775\ncpu: 2245.5869107185667 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1128.919355847959,
            "unit": "ns/iter",
            "extra": "iterations: 623269\ncpu: 1128.8965679345495 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 987.6983153871063,
            "unit": "ns/iter",
            "extra": "iterations: 708412\ncpu: 987.6797626240094 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2904.1595465855144,
            "unit": "ns/iter",
            "extra": "iterations: 240751\ncpu: 2904.150013914786 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1059.5804297342158,
            "unit": "ns/iter",
            "extra": "iterations: 654963\ncpu: 1059.5590071500242 ns\nthreads: 1"
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
          "id": "58f8a0ec5c8e54c9280a15668fd8cffd135f1575",
          "message": "Fix initialization methods for object converters",
          "timestamp": "2025-04-09T22:59:31+08:00",
          "tree_id": "86293b559a0823fc57436ed7d96b706e16d50d67",
          "url": "https://github.com/afxres/binary-cxx/commit/58f8a0ec5c8e54c9280a15668fd8cffd135f1575"
        },
        "date": 1744210843412,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 110.75398312765752,
            "unit": "ns/iter",
            "extra": "iterations: 5917021\ncpu: 110.75157194811375 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.85797395676386,
            "unit": "ns/iter",
            "extra": "iterations: 7210241\ncpu: 97.85599843333948 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.63491419441222,
            "unit": "ns/iter",
            "extra": "iterations: 10900747\ncpu: 63.628381981528435 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.81924348084564,
            "unit": "ns/iter",
            "extra": "iterations: 13651657\ncpu: 49.81534812953477 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.53259952938929,
            "unit": "ns/iter",
            "extra": "iterations: 13957134\ncpu: 50.53096545465567 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 37.784733954638156,
            "unit": "ns/iter",
            "extra": "iterations: 18325296\ncpu: 37.78286920986159 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 278.6877814676542,
            "unit": "ns/iter",
            "extra": "iterations: 2516497\ncpu: 278.68175483618717 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 179.86895290720176,
            "unit": "ns/iter",
            "extra": "iterations: 3898919\ncpu: 179.8603700153812 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 146.41887536504058,
            "unit": "ns/iter",
            "extra": "iterations: 4764835\ncpu: 146.41264094139663 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2453.802407714645,
            "unit": "ns/iter",
            "extra": "iterations: 286828\ncpu: 2453.8063299259493 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2272.4329965895013,
            "unit": "ns/iter",
            "extra": "iterations: 309335\ncpu: 2272.29549517513 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1140.9532129997115,
            "unit": "ns/iter",
            "extra": "iterations: 613461\ncpu: 1140.9093878828476 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 964.2425974229046,
            "unit": "ns/iter",
            "extra": "iterations: 716541\ncpu: 964.1915884785369 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2944.3004953702944,
            "unit": "ns/iter",
            "extra": "iterations: 239215\ncpu: 2944.14010409046 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1088.346566329303,
            "unit": "ns/iter",
            "extra": "iterations: 646087\ncpu: 1088.3279790492606 ns\nthreads: 1"
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
          "id": "834444a816ec1e0c5fdf83ffed0c7db224c248a0",
          "message": "Use functions for variant converter",
          "timestamp": "2025-04-10T20:25:13+08:00",
          "tree_id": "d52ae27e617730256da883b05057b224440b7f5f",
          "url": "https://github.com/afxres/binary-cxx/commit/834444a816ec1e0c5fdf83ffed0c7db224c248a0"
        },
        "date": 1744287983367,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Encode Custom Named Object, pre-allocate memory/0",
            "value": 111.26627584504804,
            "unit": "ns/iter",
            "extra": "iterations: 6304496\ncpu: 111.24641969794257 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Named Object, pre-allocate memory/1024",
            "value": 97.62791503820138,
            "unit": "ns/iter",
            "extra": "iterations: 7160112\ncpu: 97.60966211143067 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/0",
            "value": 63.75690120036946,
            "unit": "ns/iter",
            "extra": "iterations: 11018047\ncpu: 63.748560157712184 ns\nthreads: 1"
          },
          {
            "name": "Encode Custom Tuple Object, pre-allocate memory/1024",
            "value": 49.98651183815668,
            "unit": "ns/iter",
            "extra": "iterations: 14056326\ncpu: 49.980665004496885 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/0",
            "value": 50.56129691552647,
            "unit": "ns/iter",
            "extra": "iterations: 13915170\ncpu: 50.555317038886315 ns\nthreads: 1"
          },
          {
            "name": "Encode System Tuple, pre-allocate memory/1024",
            "value": 39.13847014720136,
            "unit": "ns/iter",
            "extra": "iterations: 18521429\ncpu: 39.05339188461107 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Named Object",
            "value": 283.61250978720534,
            "unit": "ns/iter",
            "extra": "iterations: 2498156\ncpu: 283.6016281609315 ns\nthreads: 1"
          },
          {
            "name": "Decode Custom Tuple Object",
            "value": 180.56271251571675,
            "unit": "ns/iter",
            "extra": "iterations: 3846186\ncpu: 180.5570328632051 ns\nthreads: 1"
          },
          {
            "name": "Decode System Tuple",
            "value": 145.8251702413302,
            "unit": "ns/iter",
            "extra": "iterations: 4816251\ncpu: 145.82379925797068 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text)",
            "value": 2487.0512862726864,
            "unit": "ns/iter",
            "extra": "iterations: 285476\ncpu: 2486.8922221132393 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (text, reuse stream)",
            "value": 2235.3676493128646,
            "unit": "ns/iter",
            "extra": "iterations: 313168\ncpu: 2235.2050337199216 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary)",
            "value": 1154.8367547314476,
            "unit": "ns/iter",
            "extra": "iterations: 609059\ncpu: 1154.7768081581605 ns\nthreads: 1"
          },
          {
            "name": "Boost Encode Custom Tuple Object (binary, reuse stream)",
            "value": 977.1417112600291,
            "unit": "ns/iter",
            "extra": "iterations: 711990\ncpu: 977.069763620275 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (text)",
            "value": 2929.926037352615,
            "unit": "ns/iter",
            "extra": "iterations: 238323\ncpu: 2929.6749747191825 ns\nthreads: 1"
          },
          {
            "name": "Boost Decode Custom Tuple Object (binary)",
            "value": 1082.6542279793414,
            "unit": "ns/iter",
            "extra": "iterations: 650015\ncpu: 1082.6014415051961 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}