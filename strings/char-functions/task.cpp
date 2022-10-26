#include <cstring>
bool isalpha(unsigned char c) {
    const char *alf = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
    if(std::strchr(alf, c) != nullptr)
        return true;
    return false;
}

unsigned char tolower(unsigned char c) {
}
