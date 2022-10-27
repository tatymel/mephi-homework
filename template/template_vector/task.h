#include <iostream>

template<typename T>
class Array {
public:
    Array(std::ostream& ostream) : Ostream_(ostream) {
        Elements_ = new T[2];
        Size_ = 0;
        Capacity_ = 2;

    }

    Array(const Array<T>& array) : Ostream_(array.Ostream_){
        Size_ = array.Size();
        Capacity_ = array.Capacity();
        Elements_ = new T[Capacity_];
        for(size_t i = 0; i < Size_; i++)
            Elements_[i] = array.Elements_[i];
    }

    Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = T())
    : Ostream_(ostream)
    {
        Size_ = size;
        Capacity_ = 2 * Size_;
        Elements_ = new T[Capacity_];
        for(size_t i = 0; i < size;i++){
            Elements_[i] = defaultValue;
        }
    }

    ~Array() {
        delete[] Elements_;
    }

    void Clear(){
        Size_ = 0;
    }



    size_t Size() const {
        return Size_;
    }

    size_t Capacity() const {
        return Capacity_;
    }

    void Reserve(size_t newCapacity) {
        if(newCapacity > Capacity_){
            T* NewElements_ = new T[newCapacity];
            for(size_t i = 0; i < Size_; i++)
                NewElements_[i] = Elements_[i];
            delete[] Elements_;
            Elements_ = NewElements_;
            Capacity_ = newCapacity;

        }
    }

    void Resize(size_t newSize) {
        if(newSize > Capacity_){
            Reserve(newSize);
        }
        Size_ = newSize;
    }

    void PushBack(T value = 0) {
        if(Size_ == Capacity_){
            Reserve(Size_ * 2);
        }
        Elements_[Size_] = value;
        Size_++;
    }

    void PopBack() {
        Size_--;
    }

    const T& operator [](const size_t i) const {
        return Elements_[i];
    }

    T& operator [](const size_t i) {
        return Elements_[i];
    }

    explicit operator bool() const {
        return Elements_ != NULL;
    }

    bool operator <(const Array<T>& it) const {
        size_t m;
        if(Size_ < it.Size())
            m = Size_;
        else
            m = it.Size();
        for(size_t i = 0; i < m; i++) {
            if (Elements_[i] > it[i]) {
                return false;
            }else if(Elements_[i] < it[i])
                return true;
        }
        if(Size_ < it.Size())
            return true;
        return false;

    }

    bool operator >(const Array<T>& it) const {
        return !(*this < it || *this == it);
    }

    bool operator !=(const Array<T>& it) const {
        return !(*this == it);
    }

    bool operator ==(const Array<T>& it) const {
        if(Size_ == it.Size()){
            for(size_t i = 0; i < Size_; i++){
                if(Elements_[i] != it.Elements_[i])
                    return false;
            }
            return true;
        }
        return false;
    }

    bool operator <=(const Array<T>& it) const {
        return (*this == it || *this < it);
    }

    bool operator >=(const Array<T>& it) const {
        return !(*this < it);
    }

    Array<T>& operator <<(const T& value) {
        PushBack(value);
        return *this;
    }

    Array<T>& operator <<(const Array<T>& it) {
        for(size_t i = 0; i < it.Size_; i++){
            *this << it.Elements_[i];
        }
        return *this;
    }

    bool Insert(size_t pos, const T& value) {
        if(pos > Size_)
            return false;
        if(Size_ == Capacity_)
            Reserve(Size_ * 2);
        T temp = Elements_[pos];
        Elements_[pos] = value;
        T next = Elements_[pos + 1];
        for(size_t i = pos + 1; i <= Size_; i++){
            Elements_[i] = temp;
            temp = next;
            next = Elements_[i + 1];
        }
        Size_++;
        return true;

    } ////

    bool Erase(size_t pos) {
        if(pos >= Size_)
            return false;
        for(size_t i = pos; i < Size_ - 1;i++)
            Elements_[i] = Elements_[i + 1];
        Size_--;
        return true;
    }

private:
    // ToDo
    T* Elements_;
    size_t Size_;
    size_t Capacity_;
    std::ostream& Ostream_;
};

template<typename T>
std::ostream& operator <<(std::ostream& ostream, const Array<T>& array) {
    if(array.Size() == 0){
        ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << 0;
    }else if(array.Size() > 0){
        ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size()
                << ", elements are: ";
        for (size_t i = 0; i < array.Size() - 1; ++i){
            ostream << *(array.Elements_ + i) << ", ";
        }
        ostream << *(array.Elements_ + array.Size() - 1);
    }
    return ostream;
}


