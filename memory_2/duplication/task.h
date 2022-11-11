#include <iostream>
#include <vector>
#include <memory>
std::vector<std::unique_ptr<std::string>> Duplicate(const std::vector<std::shared_ptr<std::string>>& in){
    std::vector<std::unique_ptr<std::string>> out;
    for(size_t i = 0; i < in.size(); ++i){
        out.push_back(std::make_unique<std::string>(*in[i]));
    }
    return out;
}
std::vector<std::shared_ptr<std::string>> DeDuplicate(std::vector<std::unique_ptr<std::string>>& in){
    std::vector<std::shared_ptr<std::string>> out(in.size());

    for(size_t i = 0; i < in.size(); ++i){
        bool fl = true;
        for(size_t j = 0; j < std::min(i, out.size()); ++j){
            if(*in[i] == *out[j]){
                std::shared_ptr<std::string> sp_new(out[j]);
                out[i] = sp_new;
                fl = false;
                break;
            }
        }
        if(fl){
            out[i] = (std::make_shared<std::string>(*in[i]));
        }
    }
    return out;
}