#include <iostream>

using namespace std;


void merge(int* arr, int l, int mid, int r){
    int left = mid - l + 1;
    int right = r - mid;

    int* larr = new int[left];
    int* rarr= new int[right];

    for(int i = 0; i < left; i++){
        larr[i] = arr[l+i];
    }

    for(int j = 0; j < right; j++){
        rarr[j] = arr[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while(i < left && j < right){
        if(larr[i] <= rarr[j]){
            arr[k] = larr[i];
            i++;
        } else{
            arr[k] = rarr[j];
            j++;
        }
        k++;
    }

    while(i < left){
        arr[k] = larr[i];
        i++;
        k++;
    }
    while(j < right){
        arr[k] = rarr[j];
        j++;
        k++;
    }

}

void sort(int* arr, int l, int r){
    if(l >= r){
        return;
    }
    int mid = (l + r)/2;
    sort(arr, l, mid);
    sort(arr, mid+1, r);
    merge(arr, l, mid, r);
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

    //calling sort and inputting the array, beginning at index 0 and ending at index size -1
    sort(array, 0, size - 1);

    //printing sorted array (no endl cause only one line)
    for(int k = 0; k < size; k++){
        std::cout << array[k] << ";";
    }

}