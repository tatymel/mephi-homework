#include "task.h"
// 1 2 3 4 5
// 5 4 3 2 1
void ReverseList(std::list<int>& l) {
    auto start_list = l;
    for(int t : start_list){
        l.push_front(t);
        l.pop_back();
    }
}
