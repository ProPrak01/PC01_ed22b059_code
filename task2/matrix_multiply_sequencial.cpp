#include <iostream>
using namespace std;
//globally initiallizing the variables:
int N;
int** matrix1 = new int*[N];
int** matrix2 = new int*[N];
int** resultant_matrix = new int*[N];
int lb;
int ub;

void declare_matrices(){
    
    for(size_t i = 0; i<N;i++){
        matrix1[i] =  new int[N];
        matrix2[i] = new int[N];
        resultant_matrix[i] = new int[N];
    }
    //give value to matrix_1 and matrix_2->
    for(size_t j=0;j<N;j++){
        for(size_t k=0;k<N;k++){
            matrix1[j][k] = (rand() % (ub - lb + 1)) + lb ;
            matrix2[j][k] = (rand() % (ub - lb + 1)) + lb ;
        }
    }
    
}


void print_matrix(int** matrix){
    for(size_t i=0;i<N;i++){
        for(size_t j=0;j<N;j++){
            cout<<matrix[i][j]<<",";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void matrix_multiplication(){
    //matrix multiply->
    for(int i=0;i<N;++i){
       
        for(int j=0;j<N;++j){
            resultant_matrix[i][j] = 0;
            for(int k = 0;k<N;++k){
                resultant_matrix[i][j] +=matrix1[i][k]*matrix2[k][j];
            }
        }
        }
  
    
}


int main(){
    
    //taking value of N->
    cout<<"Write the value of N->";
    cin>>N;
    
    //seting a lower bound and upper bound of random value generation
    lb = 1;
    ub = 10;
    
    declare_matrices();

    //print matrix-1:
    cout<<"matrix-1"<<endl;
    print_matrix(matrix1);
    
    //print matrix-2:
    cout<<"matrix-2"<<endl;
    print_matrix(matrix2);

    
    matrix_multiplication();
    
    //print resultant matrix:
    cout<<"resultant"<<endl;
    print_matrix(resultant_matrix);
    
    
    
}

