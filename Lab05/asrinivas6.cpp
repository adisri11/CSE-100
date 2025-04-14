#include <iostream>
#include <climits>

using namespace std;

int generatePivot(int p, int r) {
    srand(time(NULL));
    return p + rand() % (r - p + 1);
}

int partition(int* A, int p, int r){
    int pivot = generatePivot(p,r);
    swap(A[pivot], A[r]);
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++){
        if (A[j] <= x){
            i++;
            int temp1 = A[i];
            A[i] = A[j];
            A[j] = temp1;
        }
    }
    int temp2 = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp2;
    return (i+1);
}

void quicksort(int* A, int p, int r){
    if (p < r){
        int q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
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

    quicksort(array, 0, size -1);

    for(int k = 0; k < size; k++){
        cout << array[k] << ";";
    }

    delete[] array;

    return 0;
}