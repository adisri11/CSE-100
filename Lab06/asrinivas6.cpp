#include <iostream>
#include <vector>
using namespace std;

void countingSort(vector<int>* A, int n, int k, int col){
    vector<int>* B = new vector<int>[n];
    vector<int> C(k + 1, 0);

    for(int j = 0; j < n; j++){
        C[A[j][col]] = C[A[j][col]] + 1;
    }

    for(int i = 1; i <= k; i++){
        C[i] += C[i -1];
    }

    for(int j = n - 1; j >= 0; j--){
        int first = C[A[j][col]] - 1;
        B[first] = A[j];
        C[A[j][col]]--;
    }


    for(int i = 0; i < n; i++){
        A[i] = B[i];
    }

    delete[] B;
}

void radixSort(vector<int>* A, int n, int d){
    for(int col = d - 1; col >= 0; col--) {
        countingSort(A, n, 3, col);
    }
}


int main(int argc, char **argv) {
    int size;
    
    cin >> size;
    vector<int>* array = new vector<int>[size];
    
    for(int i = 0; i < size; i++) {
        array[i] = vector<int>(10);
    }
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> array[i][j];
        }
    }

    
    radixSort(array, size, 10);
    
    for(int k = 0; k < size; k++) {
        for(int x = 0; x < 10; x++) {
            cout << array[k][x] << ";";
        }
        cout << "\n";
    }
    
    delete[] array;
    
    return 0;
}