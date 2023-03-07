## 子函数功能测试

* ./test_NumberToChinese 0
--> val_in = 0
--> val_in = 0
--> res_str = 零
* ./test_NumberToChinese 11
--> val_in = 11
--> val_in = 11
--> res_str = 十一
* ./test_NumberToChinese ：18446744073709551615
--> val_in = 0
--> val_in = 0
--> res_str = 零
* ./test_NumberToChinese 18446744073709551615  
--> val_in = 18446744073709551615
--> val_in = 18446744073709551615
--> res_str = 一千八百四十四万兆六千七百四十四万亿零七百三十七亿零九百五十五万一千六百一十五


* ./test_digit_to_chinese 你好啊123周019 0
--> str_in = 你好啊123周019
--> debug = 0
--> res = 你好啊一二三周零一九
* ./test_digit_to_chinese 你好啊123周019 1
--> str_in = 你好啊123周019
--> debug = 1
--> res = 你好啊幺二三周零幺九


* ./test_str_to_vec "你好洪湖,你abc12*" 0
--> str_in = 你好洪湖,你abc12*
--> rec_str_vec.size() = 12
0: 你 len= 3
1: 好 len= 3
2: 洪 len= 3
3: 湖 len= 3
4: , len= 1
5: 你 len= 3
6: a len= 1
7: b len= 1
8: c len= 1
9: 1 len= 1
10: 2 len= 1
11: * len= 1

* ./test_regex 你好ab的你ni 0
--> str_in = 你好ab的你ni
--> rec_str_vec.size() = 4
--> rec_mark_vec.size() = 4
0: 你好:0
1: ab:1
2: 的你:0
3: ni:1











