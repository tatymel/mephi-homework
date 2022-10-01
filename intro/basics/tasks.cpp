#include <iostream>
#include <cmath>
#include <limits>
using namespace std;
namespace NOuter{
    namespace NInner{
        int DoSomething(int a, int b){
            return(a + b);
        }
    }
    int DoSomething(int a, int b){
        return abs(a - b);
    }
}

namespace NOverload{
    int ProcessTwoArgs(int a, int b){
        return a + b;
    }
    char ProcessTwoArgs(char a, char b){
        return a > b ? a : b;
    }
    int ProcessTwoArgs(int a, char b){
        return a - int(b);
    }
}

namespace NLoop{
    int SumInRange(const int a, const int b){
        int sum = 0;
        for(int i = a; i < b; i++){
            sum += i;
        }
        return sum;
    }
    int CountFixedBitsInRange(const int a, const int b, const int k){
        int ans = 0;
        for(int i = a; i < b + 1; i++){
            int s = 0;
            int ii = i;
            while (ii > 0){
                s += (ii%2);
                ii /= 2;
            }
            if (s == k){
                ans += 1;
            }

        }
        return ans;
    }
}

namespace NMath{
    bool IsPositive(int a){
        if(a > 0)
            return true;
        return false;
    }
    double ComputeMathFormula(const double a){
        return abs((sin(a) / 2 + cos(a)) * (sin(a) / 2 + cos(a)) + tan(a) * atan(a));
    }
}

namespace NRecursion{
    int CalculateFibonacci(const int a){
        int fib1 = 1;
        int fib2 = 1;
        int t;
        for(int i = 0; i < a - 2;i++){
            t = fib1;
            fib1 = fib2;
            fib2 += t;
        }
        return fib2;
    }
}

namespace NOverflow{
    unsigned int WithOverflow(int a, int b){
        return a + b;
    }
    uint64_t WithOverflow(int64_t a, int64_t b){
        return a - b;
    }

}
