#include <iostream>
#include <pthread.h>
#include<unistd.h>
#include <chrono>
using namespace std::chrono;
using namespace std;
//struct of thread data->
struct thread_data{
    int row_num ;
};

//global declaration of N
int N;
int** matrix_1 = new int*[N];
int** matrix_2 = new int*[N];
int** resultant_matrix = new int*[N];
int lb;
int ub ;

//Matrix initiallization->
void make_matrix(  ){
    for(size_t i = 0; i<N;i++){
        matrix_1[i] =  new int[N];
        matrix_2[i] = new int[N];
        resultant_matrix[i] = new int[N];
    }
    
    for(size_t i=0;i<N;i++){
        for(size_t j=0;j<N;j++){
            matrix_1[i][j] = (rand() % (ub - lb + 1)) + lb ;
            matrix_2[i][j] = (rand() % (ub - lb + 1)) + lb ;
        }
    }
    
}

//matrix row multiplication->>
void* matrix_row_multiplication(void* arg){
    
    thread_data* data = static_cast<thread_data*>(arg);
    int s = data->row_num;
    
    for(int j=0;j<N;j++){
        resultant_matrix[s][j] = 0;
        for(int k = 0;k<N;++k){
            resultant_matrix[s][j] +=matrix_1[s][k]*matrix_2[k][j];
        }
    }
    
    return NULL;
}

//print matrix->
void print_matrix(int** matrix){
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<matrix[i][j]<<",";
        }
        cout<<endl;
    }
}

int main(){
    //user input->
    cout<<"Write N: ";
    cin>>N;
    //bounds for random values->
    lb = 1;   // for lower bound
    ub = 20;   // for upper bound
    
    
    //initiallizing and declaing matrices->
    make_matrix();
    
    //printing initial matrices->
    cout<<"\nmatrix 1\n";
    print_matrix(matrix_1);
    cout<<"\nmatrix 2\n";
    print_matrix(matrix_2);
    
    
    
    pthread_t newThread[N];   // So here i created a new array of threads locations
    thread_data data[N]; // create an array of thread_data struct
     auto start = high_resolution_clock::now();
    // in the code for each iteration the ith row num will be given to the ith
    // index value of data[] and its pointer will be passed to the ith thread created.
    for(int i=0;i<N;i++){
        data[i].row_num = i;
        pthread_create(&newThread[i], NULL, matrix_row_multiplication, &data[i]);
    }
    
    // here we are joining threads by waiting for each thread to complete
    // if the threads is not joined then the main function could end before completing the parallel thread.
    for(int j=0;j<N;j++){
        pthread_join(newThread[j], NULL);
    }
            auto stop = high_resolution_clock::now();

            auto time_span = duration_cast<microseconds>(stop - start);

    // resultant matrix printing->
    print_matrix(resultant_matrix);
    cout << "Time taken by function: " << time_span.count() << " microseconds" << endl;    

    return 0;
    
}
