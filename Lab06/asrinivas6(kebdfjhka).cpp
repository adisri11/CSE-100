#include <iostream>
#include <vector>
using namespace std;

void countingSort(int** A, int n, int k) {
    int** sortedA = new int*[n]; 
    
    // Count array: counts of each key value (first element of each array)
    int* C = new int[k + 1](); // Initialize with zeros
    
    // Step 1: Count occurrences of each key
    for(int j = 0; j < n; j++) {
        C[A[j][0]]++;
    }
    
    // Step 2: Calculate starting position of each key
    for(int i = 1; i <= k; i++) {
        C[i] += C[i - 1];
    }
    
    // Step 3: Place elements in their sorted positions
    for(int j = n - 1; j >= 0; j--) {
        sortedA[--C[A[j][0]]] = A[j];
    }
    
    // Step 4: Copy sorted array back to original
    for(int i = 0; i < n; i++) {
        A[i] = sortedA[i];
    }
    
    // Cleanup
    delete[] C;
    delete[] sortedA;
}

// We don't need a radix sort if we're only sorting by the first element,
// so we'll simplify it to just call countingSort once
void radixSort(int **A, int n, int d) {
    countingSort(A, n, d + 1); // +1 to handle keys from 0 to d inclusive
}

int main(int argc, char **argv) {
    int key = 0;
    int size;
    int** array;
    
    cin >> size;
    array = new int*[size];
    
    for(int i = 0; i < size; i++) {
        array[i] = new int[10];
    }
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> array[i][j];
            if(key < array[i][j]) {
                key = array[i][j];
            }
        }
    }
    
    radixSort(array, size, key);
    
    for(int k = 0; k < size; k++) {
        for(int x = 0; x < 10; x++) {
            cout << array[k][x] << ";";
        }
        cout << "\n";
    }
    
    // Cleanup
    for(int i = 0; i < size; i++) {
        delete[] array[i];
    }
    delete[] array;
    
    return 0;
}