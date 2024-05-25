#include "tank.hpp"

// Constructor
template<typename T>
Tank<T>::Tank() : data(nullptr), curr_size(0) {cout<<"constructor_running!\n";}

// Destructor
template<typename T>
Tank<T>::~Tank() {
    cout<<"destructure_running!\n";
    delete[] data;
}


template <typename T>
T &Tank<T>::operator[](size_t index){
    return data[index];
}


template <typename T>
T Tank<T>::at(size_t index){
    return data[index];
}

template <typename T>
size_t Tank<T>::size(){
    return curr_size;
}

template <typename T>

void Tank<T>::pop_back(){
    
    (curr_size>0)?curr_size--:cout<<"data is empty!\n";
    
}


template<typename T>
void Tank<T>::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    T* newData = new T[newCapacity];
    for (int i = 0; i < curr_size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void Tank<T>::push_back(T &value){
    if (curr_size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            if (newCapacity > size() * 2) {
                newCapacity = size() * 2;  // Ensure the capacity does not exceed twice the size
            }
            resize(newCapacity);
        }
        data[curr_size++] = value;
}
template <typename T>
T accumulate(Tank<T> a){
    T sum = T();
    for(int i=0;i<a.size();i++){
        sum+= a.at(i);
    }
    return sum;
}



int main(){
    
    cout<<"hello!";
    
}
