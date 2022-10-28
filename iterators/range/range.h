#pragma once


#include <cstddef>
#include <iterator>
class Range {
private:
    const int64_t Start_;
    const int64_t End_;
    int64_t Step_ = 1;

public:
    class TIterator{
    public:
        int64_t current;
        int64_t end;
        int64_t step;

        TIterator(int64_t start, int64_t end, const int64_t step) : current(start), end(end), step(step) {};

        int64_t operator *() const{
            return this->current;
        }

        TIterator& operator++(){ //++iter
            if(step > 0 && this->current + step > end)
                this->current = end;
            else if(step < 0 && this->current + step < end)
                this->current = end;
            else
                this->current += step;
            return *this;
        }
        TIterator operator++(int){ //iter++
            TIterator old = *this;
            operator++();
            return old;
        }

        bool operator!=(const TIterator& it) const{
            return (it.current != this->current || it.step != this->step);
        }

        bool operator==(const TIterator& it) const{
            return !(*this != it);
        }
        /*friend bool operator!=(const TIterator& lhs, const TIterator& rhs){
            return (lhs.current != rhs.current || lhs.step != rhs.step);
        }

        friend bool operator==(const TIterator& lhs, const TIterator& rhs){
            return !(lhs != rhs);
        }
        friend TIterator& operator+(int64_t rhs, TIterator& lhs){
            lhs.current += rhs * lhs.step;
            return lhs;
        }*/
        friend TIterator& operator+(int64_t rhs, TIterator& lhs){
            lhs.current += rhs * lhs.step;
            return lhs;
        }
    };

    Range(int64_t n) : Start_(0), End_(n){}
    Range(int64_t start, int64_t end) : Start_(start), End_(end) {};
    Range(int64_t start, int64_t end, int64_t step) : Start_(start), End_(end), Step_(step) {};

    int64_t Size() const{
        return std::abs(std::abs(End_ - Start_) + std::abs(Step_) - 1) / std::abs(Step_);
    }

    const TIterator begin() const{
        return TIterator(Start_, End_, Step_);
    }
    const TIterator end() const{
        return TIterator(End_, End_, Step_);
    }
};
