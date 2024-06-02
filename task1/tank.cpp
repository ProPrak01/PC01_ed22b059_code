#include "tank.hpp"
/*
changes done: post interview

the newCapacity defined in 
the push back function will be send as a parameter to the resize function
which will resize the capacity accordingly

and for the question asked in the interview: 
the pop back function here checks if the array needs to be shrunk. If the current size falls below a 
quarter of the capacity, and the capacity is more than 1, 
then it reduces the capacity to half its current value to free up unused space.
*/




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
   if (curr_size > 0) {
        curr_size--;
        // Check if we need to shrink the array
        if (curr_size <= capacity / 4 && capacity > 1) {
            size_t newCapacity = capacity / 2;
            resize(newCapacity);
        }
    } else {
        cout << "data is empty!\n";
    }
}
template<typename T>
void Tank<T>::resize(size_t newCapacity) {
   
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
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
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
