#include "task.h"
#include "string_view"

char* concat(const char* lhs, const char* rhs) {
     char* new_str = const_cast<char*>(lhs);
int i = 0;
while (lhs[i] != '\0'){
    new_str += lhs[i];
    i++;
}
i = 0;
while(rhs[i] != '\0'){
    new_str += rhs[i];
    i++;
}
    return new_str;
}
