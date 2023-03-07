#include "utils_str.h"
#include <codecvt>

void NumberToChinese(unsigned long num, std::string& chnStr){
    // ref： http://data.biancheng.net/view/146.html
    // unsigned long 最大支持 18446744073709551615 ： 
        // 一千八百四十四万兆六千七百四十四万亿零七百三十七亿零九百五十五万一千六百一十五
    // 超过概述，会被转换成 ：18446744073709551615 。
    const int CHN_NUM_CHAR_COUNT = 10;
    const char *chnNumChar[CHN_NUM_CHAR_COUNT] = {"零","一","二","三","四","五","六","七","八","九"};
    const char *chnUnitSection[] = {"","万","亿","万亿","万兆","垓"};
    const char *chnUnitChar[] = {"","十","百","千"};
    //num == 0需要特殊处理，直接返回"零"
    if (num==0){
        chnStr = chnNumChar[num];
        return;
    }
    int unitPos = 0;
    std::string strIns;
    bool needZero = false;
    int id = 0;
    while(num > 0)
    {
        id += 1;
        std::string strIns;
        unsigned long section = num % 10000;
        if(needZero)
        {
            chnStr.insert(0, chnNumChar[0]);
        }
        SectionToChinese(section, strIns);
        /*是否需要节权位？ */
        if (section){
            // strIns += (section != 0) ? chnUnitSection[unitPos] : chnUnitSection[0];
            strIns += chnUnitSection[unitPos];
            chnStr.insert(0, strIns);
        }
        /*千位是0需要在下一个section补零*/
        needZero = (section < 1000) && (section > 0);
        num = num / 10000;
        unitPos++;
    }
    // 一十几 -> 十几
    if ((chnStr.substr(0,3)=="一") && (chnStr.substr(3,3)=="十")){
        chnStr = chnStr.substr(3,chnStr.size());
    }
    // xxx零 -> xxx
    if (chnStr.substr(chnStr.size()-3,chnStr.size())=="零"){
        chnStr = chnStr.substr(0,chnStr.size()-3);
    }
}

void SectionToChinese(unsigned long section, std::string& chnStr){
    const int CHN_NUM_CHAR_COUNT = 10;
    const char *chnNumChar[CHN_NUM_CHAR_COUNT] = {"零","一","二","三","四","五","六","七","八","九"};
    const char *chnUnitSection[] = {"","万","亿","万亿"};
    const char *chnUnitChar[] = {"","十","百","千"};
    std::string strIns;
    int unitPos = 0;
    bool zero = true;
    while(section > 0)
    {
        int v = section % 10;
        if(v == 0){
            if( (section==0) || !zero ){
                zero = true; /*需要补，zero的作用是确保对连续的多个，只补一个中文零*/
                chnStr.insert(0, chnNumChar[v]);
            }
        } else {
            zero = false;              //至少有一个数字不是
            strIns = chnNumChar[v];    //此位对应的中文数字
            strIns += chnUnitChar[unitPos]; //此位对应的中文权位
            chnStr.insert(0, strIns);
        }
        unitPos++; //移位
        section = section / 10;
    }
}

std::string digit_to_chinese(const std::string& str_in,int is_tele_num){
    // 将输入字符串 str_in 中的 阿拉伯数字 0~9 逐个转换成 零~九。 2：二
    // 如果 is_tele_num 为 true, 1： 一 ——> 幺，
    // 备注： 
        // 数字 0-9 的 wchar: [48,57]
        // 零 : 38646
        // 一 : 19968
        // 幺 : 24186
        // 二 : 20108
        // 三 : 19977
        // 四 : 22235
        // 五 : 20116
        // 六 : 20845
        // 七 : 19971
        // 八 : 20843
        // 九 : 20061
    // 
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring ws = conv.from_bytes(str_in);
    std::wstring nws;
    for (wchar_t ch:ws){
        if (ch==48){
            nws.push_back(38646);
        } else if (ch==49){
            if (is_tele_num){
                nws.push_back(24186);
            } else {
                nws.push_back(19968);
            }
        } else if (ch==50){ // 2
            nws.push_back(20108);
        } else if (ch==51){
            nws.push_back(19977);
        } else if (ch==52){ //4
            nws.push_back(22235);
        } else if (ch==53){
            nws.push_back(20116);
        } else if (ch==54){
            nws.push_back(20845);
        } else if (ch==55){
            nws.push_back(19971);
        } else if (ch==56){
            nws.push_back(20843);
        } else if (ch==57){
            nws.push_back(20061);
        } else {
            nws.push_back(ch);
        } 
    }
    std::string chn_str = conv.to_bytes(nws);
    return chn_str;
}

void regex_seg(const std::string& str_in,std::regex reg,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_mark_vec,int debug){
    // 根据 reg 对 str_in 进行分段，
    // 结果存 rec_str_vec，匹配的 mark=1 存 rec_mark_vec
    
    std::regex reg_abc("[a-zA-Z ]+");
    std::regex reg_ssml("<speak>.*?</speak>");
    // 临时结果
    std::vector<std::string> tmp_res_vec;
    std::vector<int> tmp_pos_vec;
    std::vector<int> tmp_len_vec;
    // 匹配
    std::sregex_iterator iter(str_in.begin(),str_in.end(),reg);
    std::sregex_iterator end;
    int cnt = 0;
    while (iter!=end){
        for (size_t i=0;i<iter->size();i++){
            if (debug){
                std::cout << cnt << " : " << i << " : " << "cont = " << (*iter)[i] << std::endl;
                std::cout << cnt << " : " << i << " : " << "cont = " << (*iter).str() << std::endl;
                std::cout << cnt << " : " << i << " : " << "posi = " << (*iter).position() << std::endl;
                std::cout << cnt << " : " << i << " : " << "leng = " << (*iter).length() << std::endl;
            }
            tmp_res_vec.push_back((*iter).str());
            tmp_pos_vec.push_back((*iter).position());
            tmp_len_vec.push_back((*iter).length());
        }
        cnt += 1;
        ++iter;
    }
    // 分段
    std::vector<std::string> tmp_res_vec_all;
    std::vector<int> tmp_mark_vec_all;
    int last_pos_s = 0;
    int last_len = 0;
    for (size_t i=0;i<tmp_res_vec.size();i++){
        int cur_pos_s = tmp_pos_vec[i];
        int cur_len = tmp_len_vec[i];
        // 未匹配结果 保存
        if (cur_pos_s>(last_pos_s+last_len)){
            tmp_mark_vec_all.push_back(0);
            tmp_res_vec_all.push_back(str_in.substr(last_pos_s+last_len,cur_pos_s-(last_pos_s+last_len)));
        }
        // 匹配结果保存
        tmp_mark_vec_all.push_back(1);
        // tmp_res_vec_all.push_back(str_in.substr(cur_pos_s,cur_len));
        tmp_res_vec_all.push_back(tmp_res_vec[i]);
        last_pos_s = cur_pos_s;
        last_len = cur_len;
    }
    // 句尾判断
    if ((last_pos_s+last_len)<str_in.size()){
        tmp_mark_vec_all.push_back(0);
        tmp_res_vec_all.push_back(str_in.substr(last_pos_s+last_len,str_in.size()));
    }
    // 
    rec_str_vec = std::move(tmp_res_vec_all);
    rec_mark_vec = std::move(tmp_mark_vec_all);
}

void str_to_vec(const std::string& str_in,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_len_vec,int debug){
    // 将输入 str_in 分解成 单个 元素的 vec。
    // 返回 rec_str_vec 内容向量
    //      rec_len_vec 元素字节长度向量
    std::vector<std::string> tmp_str_vec;
    std::vector<int> tmp_len_vec;
    std::string seg_str;
    int char_len = 0;
    for (size_t i=0;str_in[i]!='\0';){
        char tmp_char = str_in[i];
        if ((tmp_char & 0x80) == 0){
            char_len = 1;
        } else if ((tmp_char & 0xF8) == 0xF8){
            char_len = 5;
        } else if ((tmp_char & 0xF0) == 0xF0){
            char_len = 4;
        } else if ((tmp_char & 0xE0) == 0xE0){
            char_len = 3;
        } else if ((tmp_char & 0xC0) == 0xC0){
            char_len = 2;
        }
        seg_str = str_in.substr(i,char_len);
        tmp_str_vec.push_back(seg_str);
        tmp_len_vec.push_back(char_len);
        i += char_len;
    }
    rec_str_vec = std::move(tmp_str_vec);
    rec_len_vec = std::move(tmp_len_vec);
}