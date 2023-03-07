#include "utils_str.h"


void regex_seg(const std::string str_in,std::regex reg,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_mark_vec,int debug){
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

void str_to_vec(const std::string str_in,std::vector<std::string>& rec_str_vec,std::vector<int>& rec_len_vec,int debug){
    // 将输入 str_in 分解成 单个 元素的 vec。
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