#include "UniquePtr.h"
#include <iostream>

int main() {    
    // UniquePtr<int> ptr(new int(5));
    // they test all methods here...
    // constructor + operator*
    UniquePtr<int> ptr(new int(1));
    std::cout << "printing ptr object:" << std::endl;
    std::cout << *ptr << std::endl; // Output: 1
    assert(*ptr == 1);
 
    // get()
    UniquePtr<int> ptr2(new int(2));
    assert(ptr2.get() != nullptr);
 
    // operator bool on an empty pointer
    UniquePtr<int> empty;
    std::cout << "is empty pointer nonempty? (0 = no)" << std::endl;
    std::cout << (bool)empty << std::endl; // Output: 0
    assert(!empty);

    // test that copying is blocked
    //UniquePtr<int> ptr2 = ptr;   
    //UniquePtr<int> ptr3;
    //ptr3 = ptr;   
 
    // operator->
    UniquePtr<std::string> ptrStr(new std::string("hi"));
    std::cout << "printing size via operator-> :" << std::endl;
    std::cout << ptrStr->size() << std::endl; // Output: 2
    assert(ptrStr->size() == 2);
 
    // move constructor
    UniquePtr<int> ptr3 = std::move(ptr);
    std::cout << "printing ptr3 object after move:" << std::endl;
    std::cout << *ptr3 << std::endl; // Output: 1
    assert(!ptr && *ptr3 == 1);
 
    // move assignment
    UniquePtr<int> ptr4(new int(4));
    ptr4 = std::move(ptr2);
    std::cout << "printing ptr4 object after move assignment:" << std::endl;
    std::cout << *ptr4 << std::endl; // Output: 2
    assert(!ptr2 && *ptr4 == 2);
 
    // makeUnique
    UniquePtr<int> a = makeUnique<int>(10);
    std::cout << "printing makeUnique object:" << std::endl;
    std::cout << *a << std::endl; // Output: 10
    assert(*a == 10);
 
    // converting constructor
    UniquePtr<int> ptr7(new int(7));
    UniquePtr<const int> ptr8 = std::move(ptr7);
    std::cout << "Is ptr7 empty after converting constructor? (0 = empty)" << std::endl;
    std::cout << (bool)ptr7 << std::endl; // Output: 0
    assert(!ptr7 && *ptr8 == 7);
 
    // operator== and operator!=
    assert(ptr4 == ptr4);
    assert(ptr4 != empty);
 
    // release
    UniquePtr<int> ptr9(new int(9));
    int* raw = ptr9.release();
    std::cout << "released value:" << std::endl;
    std::cout << *raw << std::endl; // Output: 9
    assert(!ptr9 && *raw == 9);
    delete raw;
 
    // reset
    UniquePtr<int> ptr10(new int(10));
    ptr10.reset(new int(11));
    std::cout << "printing ptr10 after reset:" << std::endl;
    std::cout << *ptr10 << std::endl; // Output: 11
    assert(*ptr10 == 11);
 
    // swap
    UniquePtr<int> ptr11(new int(1));
    UniquePtr<int> ptr12(new int(2));
    ptr11.swap(ptr12);
    std::cout << "printing ptr11 and ptr12 after swap:" << std::endl;
    std::cout << *ptr11 << " " << *ptr12 << std::endl; // Output: 2 1
    assert(*ptr11 == 2 && *ptr12 == 1);
 
    return 0;
}
