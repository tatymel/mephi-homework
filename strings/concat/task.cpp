#include "task.h"
#include "string_view"

char* concat(const char* lhs, const char* rhs) {
    char* new_str = new char;

    int i = 0;
    while (lhs[i] != '\0'){
        new_str[i] = lhs[i];
        i++;
    }
    int n = i;
    while(rhs[i - n] != '\0'){
        new_str[i] = rhs[i - n];
        i++;
    }
    cout << lhs;
    return new_str;
}
