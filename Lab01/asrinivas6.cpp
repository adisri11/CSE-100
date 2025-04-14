#include <iostream>

using namespace std;


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

//insertion sort code
for (int i = 1; i < size; i++){
    key = array[i];
    int j = i -1;
    while (j>=0 && array[j] > key){
        array[j + 1] = array[j];
        j--;
    }
    array[j + 1] = key;
    
     for(int k = 0; k <= i; k++){
            std::cout << array[k] << ";";
        }
        std::cout << std::endl;

}

}