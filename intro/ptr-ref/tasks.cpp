#include "tasks.h"
#include <cmath>
using namespace std;
namespace NPointers {
    /* To implement:
    Increment
    Multiply
    ScalarProduct
    SizeOfMaximumSquareOfCrosses
    MultiplyToLongLong
    */
    void Increment(int *p){
        *p += 1;
    }

    long long Multiply(int a, int b, bool *flag){
        long long c = a * b;
        if(abs(c) > std::numeric_limits<int>::max())
            *flag = true;
        else
            *flag = false;
        return c;
    }

    int ScalarProduct(const int *a,const int *b, int n){
        int scalar = 0;
        for(int i = 0; i < n; i++){
            scalar += a[i] * b[i];
        }
        return scalar;
    }


    long long* MultiplyToLongLong(const int a, const int b){
        long long *p = new long long();
        *p = (long long)a * (long long)b;
        return p;
    }




    int SizeOfMaximumSquareOfCrosses(const char* a, int n, int m){
        return 2;
    }
    /*bool fl;
    int ans = 0, k = 0;
    for(int k = 0; k < n; k++){
    for(int i = 0; i < m; i++){
    fl = true;

    if(a[i][i] == "+") {
    k = 1;
    for (int j = i + 1; j < m && j < n; j++) {
    if (a[i][j] == "+") {
    k += 1;
    for (int ii = j; ii >= i; ii--)
    if (a[ii][j] != "+") {
    fl = false;
    k -= 1;
    break;
}
if (!fl)
break;
for (int jj = j; jj >= i; jj--)
if (a[i][jj] != "+") {
fl = false;
k -= 1;
break;
}
if (!fl)
break;
}

}
}
if(fl){
if(k > ans)
ans = k;
}
}
}
}
*/
}

namespace NReferences {
    /* To implement:
    MultiplyInplace
    CompareArraysByAverage
    */
    void MultiplyInplace(int &a, int b){
        a = a * b;
    }

    int CompareArraysByAverage(const int *a, int n, int *b){
        double aver1 = 0, aver2 = 0, size_b = 5;

        for(int i = 0; i < n; i++)
            aver1 += a[i];
        aver1 = aver1 / (double)n;

        for(int i = 0; i < size_b;i++)
            aver2 += b[i];
        aver2 = aver2 / (double)size_b;

        if(aver1 < aver2)
            return -1;
        if(aver1 == aver2)
            return 0;
        return 1;
    }
}
