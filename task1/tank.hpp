#ifndef tank_hpp
#define tank_hpp

#include <iostream>
using namespace std;

template <typename T>
class Tank{
private:
    T* data;
    size_t curr_size;
    size_t capacity;
    void resize( size_t newCapacity );
    
public:
    Tank();
    ~Tank();
    T& operator[](std::size_t index);
    size_t size();
    
    T at(size_t index);
    
    void pop_back();
    
    void push_back(T &value);
};

#endif /* tank_hpp */
