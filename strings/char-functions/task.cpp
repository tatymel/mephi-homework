#include <cstring>
#include "task.h"
bool isalpha(unsigned char c) {
    const char *alf = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
    if(std::strchr(alf, c) != nullptr)
        return true;
    return false;
}

unsigned char tolower(unsigned char c) {
    const char *ALF = "QWERTYUIOPLKJHGFDSAZXCVBNM";
    if(std::strchr(ALF, c) != nullptr)
        c = char(int(c) + 32);
    return c;
}
