#include <iostream>

#if defined(_LIBCPP_LIST) || defined(_LIBCPP_DEQUE) || defined(_LIBCPP_FORWARD_LIST)
#error "include list or deque forbidden"
#endif

#include <algorithm>
#include <cassert>
#include <chrono>
#include <memory>
#include <random>
#include <string>
#include <vector>
template<typename T>
class FlattenedVector {
public:
    //////
    class Iterator{

    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::random_access_iterator_tag;

        Iterator() = default;
        Iterator(size_t pos, std::vector<std::vector<value_type>>& vec) : IterVecOut(&vec){
            Pos = pos;
        }

        bool operator != (const Iterator& other) const {
            return Pos != other.Pos;
        }
        bool operator == (const Iterator& other) const {
            return Pos == other.Pos;
        }
        bool operator < (const Iterator& other) const{
            return Pos < other.Pos;
        }
        bool operator > (const Iterator& other) const{
            return Pos > other.Pos;
        }
        bool operator <= (const Iterator& other) const{
            return Pos <= other.Pos;
        }
        bool operator >= (const Iterator& other) const{
            return Pos >= other.Pos;
        }

        bool operator==(int x)const{
            return Pos == x;
        }
        bool operator!=(int x)const{
            return Pos != x;
        }

        Iterator& operator++() {
            ++Pos;
            return *this;
        }
        Iterator& operator--(){
            --Pos;
            return *this;
        }


        reference Bin_Poisk(size_t pos)const{
            size_t l = 0, r = IterVecOut->size();
            while(l < r - 1){
                size_t mid = PreffSum[(l + r)/2];
                if(mid < pos + 1){
                    l = (l + r)/2;
                }else{
                    r = (l + r)/2;
                }
            }
            size_t column = r;
            return *((IterVecOut->begin() + column - 1)->begin() - PreffSum[column - 1] + pos);
        }
        reference operator*()const{
            return Bin_Poisk(Pos);
        }
        reference operator[](const Iterator& other)const{
            return Bin_Poisk(other.Pos + Pos);
        }
        reference operator[](size_t diff)const{
            return Bin_Poisk(Pos + diff);
        }

        size_t operator+()const{
            return Pos;
        }
        Iterator operator+(int x)const{
            return Iterator(Pos + x, *IterVecOut);
        }
        Iterator operator-(int x)const{
            return Iterator(Pos - x, *IterVecOut);
        }
        size_t operator+(const Iterator& other)const{
            return Iterator(Pos + other.Pos, *IterVecOut);
        }
        size_t operator-(const Iterator& other)const{
            if(Pos > other.Pos)
                return Pos - other.Pos;
            else
                return other.Pos - Pos;
        }
        Iterator& operator += (const Iterator& other){
            Pos += other.Pos;
            return *this;
        }
        Iterator& operator -= (const Iterator& other){
            Pos -= other.Pos;
            return *this;
        }
        Iterator& operator +=(int x){
            Pos += x;
            return *this;
        }
        Iterator& operator -=(int x){
            Pos -= x;
            return *this;
        }

        size_t GetPos() const{
            return Pos;
        }
        std::vector<std::vector<T>>* GetVec()const{
            return IterVecOut;
        }
    private:
        std::vector<std::vector<T>>* IterVecOut;
        size_t Pos;
    };
    //////
    Iterator begin() const{
        return Iterator(0, IterVecOut);
    }
    Iterator end() const{
        return Iterator(All, IterVecOut);
    }

    FlattenedVector(std::vector<std::vector<T>>& vec) : IterVecOut(vec){
        PreffSum.clear();
        PreffSum.resize(vec.size() + 1);
        PreffSum[0] = 0;
        for(size_t i = 1; i <= vec.size(); ++i){
            PreffSum[i] += PreffSum[i - 1] + vec[i - 1].size();
            All += vec[i - 1].size();
        }
    }

    inline static std::vector<size_t> PreffSum;
private:
    std::vector<std::vector<T>>& IterVecOut;
    size_t All = 0;
};

template<typename T>
size_t operator+(const size_t& x, const T& iter){
    return iter.GetPos() + x;
}