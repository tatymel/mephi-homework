#include <iostream>

class Array {
public:
    Array(std::ostream& ostream);
    Array(const Array& array);
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0);
    ~Array();

    size_t Size() const;
    size_t Capacity() const;
    void Reserve(size_t newCapacity);
    void Resize(size_t newSize);
    void PushBack(int value = 0);
    void PopBack();

    int& operator [](const size_t& i);
    explicit operator bool() const;

    bool operator <(const Array& it) const;
    bool operator >(const Array& it) const;
    bool operator !=(const Array& it) const;
    bool operator ==(const Array& it) const;
    bool operator <=(const Array& it) const;
    bool operator >=(const Array& it) const;

    Array& operator <<(const int& value);
    Array& operator <<(const Array& it);

    friend std::ostream& operator <<(std::ostream& ostream, const Array& array);

private:
    int* Elements_; // указатель на участок памяти с данными
    size_t Size_; //реальный размер
    size_t Capacity_; //размер аллоцированной памяти
    std::ostream& Ostream_; //ссылку на поток вывода ostream&
};

Array::~Array(){
    delete[] Elements_;

    Ostream_ << "Destructed " << Size_ << "\n";

}

Array::Array(std::ostream& ostream) : Ostream_(ostream){
Elements_ = new int[2];
Size_ = 0;
Capacity_ = 2;
Ostream_ << "Constructed. " << *this << "\n";
}

Array::Array(const Array& array) : Ostream_(array.Ostream_){ ////WHY OSTREAM?
Size_ = array.Size();
Capacity_ = array.Capacity();
Elements_ = new int[Capacity_];
for(size_t i = 0; i < Size_; i++)
    Elements_[i] = array.Elements_[i];
Ostream_ << "Constructed from another Array. " << *this << "\n";
}

Array::Array(size_t size, std::ostream& ostream, int defaultValue) : Ostream_(ostream){
Size_ = size;
Capacity_  = 2 * Size_;
Elements_ = new int[Capacity_];
for(size_t i = 0; i < size; i++){
    Elements_[i] = defaultValue;
}

Ostream_ << "Constructed with default. " << *this << "\n"; //to make

}

size_t Array::Size() const{
    return Size_;
}

size_t Array::Capacity() const{
    return Capacity_;
}

void Array::PushBack(int value){
    if(Size_ == Capacity_){
        Array::Reserve(Size_ * 2);
    }
    Elements_[Size_] = value;
    Size_ += 1;
}

void Array::Reserve(size_t newCapacity){
    int* NewElem = new int[newCapacity];
    for(size_t i = 0; i < Size_; i++){
        NewElem[i] = Elements_[i];
    }
    delete[] Elements_; ////   !!!!
    Elements_ = NewElem; ////   !!!!
    Capacity_ = newCapacity;
}

void Array::Resize(size_t newSize){
    if(newSize > Capacity_){
        Array::Reserve((newSize * 2));
    }
    Size_ = newSize;
}

void Array::PopBack(){
  Size_--;

}

int& Array::operator [](const size_t& i){
    return *(Elements_ + i);
}

Array::operator bool() const{
    if(Size_ == 0)
        return false;
    else
        return true;
}

Array& Array::operator <<(const int& value){
    PushBack(value);
    return *this;
}

Array& Array::operator <<(const Array& it) {
    for (size_t i = 0; i < it.Size(); ++i)
        PushBack(it.Elements_[i]);
    return *this;
}


bool Array::operator <(const Array& it) const{
    size_t minim = std::min(Size_, it.Size());
    for(size_t i = 0; i < std::min(Size_, it.Size()); ++i) {
        if (Elements_[i] > it.Elements_[i]) {
            return false;
        }else if(Elements_[i] < it.Elements_[i])
            return true;
    }
    return false;
}




bool Array::operator >(const Array& it) const{
    return !Array::operator<(it);
}

bool Array::operator !=(const Array& it) const{
    for (size_t i = 0; i < std::min(Size(), it.Size()); ++i){
        if (Elements_[i] != it.Elements_ [i]){
            return true;
        }
    }
    return false;
}

bool Array::operator ==(const Array& it) const{
    /*if(Size_ != it.Size())
        return false;
    else {
        for (size_t i = 0; i < Size_; i++){
            if (Elements_[i] != it.Elements_[i])
                return false;
        }
        return true;
    }*/
    return !Array::operator!=(it);
}


bool Array::operator <=(const Array& it) const{
    for (size_t i = 0; i < std::min(Size_, it.Size()); ++i){
        if (Elements_[i] > it.Elements_[i]){
            return false;
        }else if(Elements_[i] < it.Elements_[i])
            return true;
    }
    return true;
}

bool Array::operator >=(const Array& it) const{
    return !Array::operator<=(it);
}

std::ostream& operator <<(std::ostream& ostream, const Array& array){
    ostream << "Result Array's capacity is " << array.Capacity()
            << " and size is " << array.Size() << ", elements are: ";
    for(size_t i = 0; i < array.Size() - 1; i++){
        ostream << *(array.Elements_ + i) << ", ";
    }
    ostream << *(array.Elements_ + array.Size() - 1);
    return ostream;
}


