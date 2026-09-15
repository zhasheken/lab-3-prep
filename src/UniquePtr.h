#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <cassert>
#include <utility>

// Your implementation here
template <typename T>
class UniquePtr{
    //private members
    T* ptr;
    public:
    //public members

    // constructor
    UniquePtr(T* p = nullptr) : ptr(p) {}

    // destructor
    ~UniquePtr(){
        delete ptr;
    }

    // handle copy
    // case 1: UniquePtr b = a;
    UniquePtr(const UniquePtr& other) = delete;
    // case 2: b = a
    UniquePtr& operator=(const UniquePtr& other) = delete;

    // move constructor
    UniquePtr(UniquePtr&& other){
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    // move assignment
    UniquePtr& operator=(UniquePtr&& other){
        if (this != &other){
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // converting constructor
    template <typename U> friend class UniquePtr;
    template <typename U>
    UniquePtr(UniquePtr<U>&& other){
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // dereference - returns the object
    T& operator*() const {
        assert(ptr != nullptr);
        return *ptr;
    }

    // returns the pointer address
    T* operator->() const {
        assert(ptr != nullptr);
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    bool operator==(const UniquePtr<T>& other) const {
        return ptr == other.ptr;
    }

    bool operator!=(const UniquePtr<T>& other) const { 
        return ptr != other.ptr;
    }

    T* release(){
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* newPtr = nullptr){
        T* temp = ptr;
        ptr = newPtr;
        delete temp;
    }

    void swap(UniquePtr<T>& other){
        T* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    /*
    Consider the following question while implementing your UniquePtr<T>: 
    suppose I take a const (lvalue) reference to a UniquePtr<T> like so:
    void f(const UniquePtr<T>& x)
    {
        // Can I modify the member fields of x's owned object here?
        *********yes, i can modify the member fields of x's owned object
    }
    Should or shouldn't I be able to modify the member fields of the owned object inside f? 
    ** We should for now, because there is no restrictions saying that the pointer can
    only point to an constant and unchanging object

    If you want a UniquePtr which disallows modification to the stored object, how can you do this?
    **make the uniqueptr const when calling it, eg. UniquePtr<const int> p(new int(3));

    */
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    T* rawPtr = new T(std::forward<Args>(args)...);
    UniquePtr<T> smartPtr(rawPtr);
    return smartPtr;
}
#endif
