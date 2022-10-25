#include "task.h"
#include "string"

bool is_palindrome(const std::string& s) {
    const char *alf = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
    std::string new_str = "";
    for(int i = 0; i < s.size();i++){
        if(strchr(alf, s[i]) != nullptr)
            new_str += s[i];
    }
    bool ans = true;
    int new_str_size = new_str.size();
    for(int i = 0; i <= new_str_size / 2; i++){
        if(!(new_str[i] == new_str[new_str_size - i - 1] or new_str[i] == char(int(new_str[new_str_size - 1 - i] + 32)) or new_str[i] == char(int(new_str[new_str_size - 1 - i] - 32)))){
            ans = false;
            break;
        }
    }
    return ans;
}
