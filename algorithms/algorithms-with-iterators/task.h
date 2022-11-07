#include <cstdlib>
#include <iterator>
#include <vector>
#include <functional>

/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    OutputIt result = firstOut;
    for(InputIt it = firstIn; it != lastIn; ++it){
        *result = op(*it);
        ++result;
    }
}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */

template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {
    BidirIt i = first, j = first;
    while(i != last && j != last){
        while(i != last && !p(*i))
            ++i;
        while(j != last && p(*j))
            ++j;
        if(i!= last && j!= last && p(*i) && !p(*j)) {
            if(i > j) {
                std::swap(*i, *j);
                ++i;
                ++j;
            }else{
                ++i;
            }
        }
    }
}

/*
 * Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
 */
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {
    InputIt1 i = first1;
    InputIt2 j = first2;
    while(i != last1 && j != last2){
        if(*i < *j){
            *firstOut = *i;
            ++i;
        }else{
            *firstOut = *j;
            ++j;
        }
        ++firstOut;
    }
    while(i != last1) {
        *firstOut = *i;
        ++i;
        ++firstOut;
    }
    while(j != last2){
        *firstOut = *j;
        ++j;
        ++firstOut;
    }
}


/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */
class FibonacciRange {
private:
    size_t Amount_;
    uint64_t* Numbers_;
public:

    class Iterator {
        friend class FibonacciRange;
    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;
    private:
        pointer current;
    public:
        Iterator(pointer ptr) : current(ptr){}


        value_type operator *() const {
            // разыменование итератора -- доступ к значению
            return *current;
        }

        Iterator& operator ++() {
            // prefix increment
            ++current;
            return *this;
        }

        ////
        Iterator operator ++(int) {
            // postfix increment
            Iterator temp_current = *this;
            operator++(); // or ++(*this)
            return temp_current;
        }

        bool operator ==(const Iterator& rhs) const {
            return (current == rhs.current);
        }

        bool operator !=(const Iterator& rhs) const{
            return(current != rhs.current);
        }

        bool operator <(const Iterator& rhs) const {
            return(*current < *(rhs.current));
        }
    };


    FibonacciRange(size_t amount) : Amount_(amount)
    {
        Numbers_ = new uint64_t[Amount_];
        if(Amount_ > 0)
            Numbers_[0] = 1;
        if(Amount_ > 1)
            Numbers_[1] = 2;
        for(size_t i = 2; i < Amount_; ++i)
            Numbers_[i] = Numbers_[i - 1] + Numbers_[i - 2];
    }
    ~FibonacciRange()
    {
        delete[] Numbers_;
    }


    Iterator begin() const {
        return Iterator(Numbers_);
    }

    Iterator end() const {
        return Iterator(Numbers_ + Amount_);
    }

    size_t size() const {
        return Amount_;
    }
};

