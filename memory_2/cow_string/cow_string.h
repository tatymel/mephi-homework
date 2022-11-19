#include <cstddef>
struct State{
    int ref_count; // сколько строк используют этот State.
    char* Elements_;
    size_t Size_;
    size_t Capacity_;

    State(){
        Elements_ = new char[2];
        Size_ = 0;
        Capacity_ = 2;
        ref_count = 1;
    }

    State(const State& other) {
        ref_count = other.ref_count;
        Size_ = other.Size_;
        Capacity_ = other.Capacity_;
        Elements_ = other.Elements_;
    }
    void Copy(const State& other){
        ref_count = 1;
        Size_ = other.Size_;
        Capacity_ = other.Capacity_;
        char* New_ = new char[Capacity_];
        for(size_t i = 0; i < Size_; ++i) {
            New_[i] = other.Elements_[i];
        }
        delete[] Elements_;
        Elements_ = New_;
        New_ = nullptr;
    }
    ~State(){
        delete[] Elements_;
    }

    void Reserve(size_t capacity){
        if(capacity < Size_) {
            Size_ = capacity;
        }
        char* NewElements_ = new char[capacity];
        for (size_t i = 0; i < Size_; ++i)
            NewElements_[i] = Elements_[i];
        delete[] Elements_;
        Elements_ = NewElements_;
        Capacity_ = capacity;
    }

    void Resize(size_t size){
        if(size > Capacity_){
            Reserve(size * 2);
        }
        Size_ = size;
    }

    void PushBack(char c){
        if(Size_ == Capacity_)
            Reserve(Size_ * 2);
        Elements_[Size_] = c;
        ++Size_;
    }

};
class CowString {
private:
    State* StatePtr;
public:
    // constrcutors
    // copy operator=
    CowString() {
        StatePtr = new State();
    }

    CowString(const CowString& other) : StatePtr(other.StatePtr) {
        ++StatePtr->ref_count;
    };

    ~CowString(){
        if(StatePtr->ref_count == 1){
            delete StatePtr;
            StatePtr = nullptr;
        }else{
            --StatePtr->ref_count;
        }

    }

    void operator=(const CowString& other){
        if(StatePtr->ref_count > 1)
            --StatePtr->ref_count;
        StatePtr = other.StatePtr;
        ++StatePtr->ref_count;
    }
    const char& At(size_t index) const{
        return StatePtr->Elements_[index];
    }
    char& operator[](size_t index){
        if(StatePtr->ref_count > 1){
            --StatePtr->ref_count;
            State* NewStatePtr = new State();
            NewStatePtr->Copy(*StatePtr);
            StatePtr = NewStatePtr;
        }
        return StatePtr->Elements_[index];

    }

    const char& Back() const{
        return StatePtr->Elements_[StatePtr->Size_ - 1];
    }

    void PushBack(char c){
        if(StatePtr->ref_count > 1){
            --StatePtr->ref_count;
            State* NewStatePtr = new State;
            NewStatePtr->Copy(*StatePtr);
            StatePtr = NewStatePtr;
        }
        StatePtr->PushBack(c);
    }

    size_t Size() const{
        return StatePtr->Size_;
    }
    size_t Capacity() const{
        return StatePtr->Capacity_;
    }

    void Reserve(size_t capacity){
        StatePtr->Reserve(capacity);
    }
    void Resize(size_t size){
        StatePtr->Resize(size);
    }
};

