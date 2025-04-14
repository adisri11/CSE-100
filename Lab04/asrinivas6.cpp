#include <iostream>

using namespace std;


int Left(int i){
    return 2*i + 1;
}

int Right(int i){
    return 2*i + 2;
}

void heapify(int* A, int size, int i){
    int l = Left(i);
    int r = Right(i);
    int largest = i;
    if(l < size && A[l] > A[i]){
        largest = l;
    } 

    if(r < size && A[r] > A[largest]){
        largest = r;
    } 
    
    if(largest != i){
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        heapify(A, size, largest);
    }
}

void build_max_heap(int* arr, int size){
    for(int i = size/2 - 1; i >= 0; i--){
        heapify(arr, size, i);
    }
}

void heapsort(int* A, int size){
    build_max_heap(A, size);
    for(int i = size - 1; i > 0; i--){
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        heapify(A, i, 0);
    }
}

int main(int argc,char **argv){
    int key;
    int size;

    int* array;

    //getting size from the first of the given numbers 
    cin >> size;

    //making the array the given size
    array = new int[size];

    //assigning numbers to the array
    for(int i = 0; i < size; i++){
    cin >> array[i];
    }

    heapsort(array, size);

    for(int k = 0; k < size; k++){
        cout << array[k] << ";";
    }

    delete[] array;

    return 0;
}