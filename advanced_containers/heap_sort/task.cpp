#include "task.h"

using namespace std;

vector<int> HeapSort(const vector<int>& v) {
    priority_queue<int> pr;
    vector<int> nv(v.size(), 0);
    for(int t : v)
        pr.push(t);

    for(int i = v.size() - 1; i > -1; i--){
        nv[i] = pr.top();
        pr.pop();
    }
    return nv;
}
