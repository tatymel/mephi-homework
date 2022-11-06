#include <chrono>
#include <string>
#include <sstream>
class Timer {
private:
    std::chrono::seconds sec;
    std::chrono::steady_clock::time_point  begin;
public:
    Timer(std::chrono::seconds sec) : sec(sec) {
        begin = std::chrono::steady_clock::now();
    }

    bool Expired() const{
        while(std::chrono::steady_clock::now() - begin <= sec){
            return false;
        }
        return true;
    }
};


class TimeMeasurer {
private:
    std::stringstream& Ostream_;
    std::chrono::steady_clock::time_point begin;
public:
    TimeMeasurer(std::stringstream& out) : Ostream_(out){
        begin = std::chrono::steady_clock::now();
    }
    ~TimeMeasurer(){
        Ostream_ << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() << std::endl;
    }
};
