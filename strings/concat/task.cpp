#include "task.h"
#include "string_view"

char* concat(const char* lhs, const char* rhs) {
     char* new_str = const_cast<char*>(lhs);
//c<char*>(new_str);
    strcat(new_str, lhs);
    strcat(new_str, rhs);
    return new_str;
}
