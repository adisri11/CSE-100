#include <iostream>
#include <limits>

using namespace std;

int max_left;
int max_right;

int maxsub(int* A, int low, int mid, int high){
    int left_sum = -(std::numeric_limits<int>::max());
    int sum = 0;
    for (int i = mid; i >= low; i--){
        sum += A[i];
        if(sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = -(std::numeric_limits<int>::max());
    sum = 0;
    for(int j = mid + 1; j <= high; j++){
        sum += A[j];
        if(sum>right_sum){
            right_sum = sum;
            max_right = j;
        }
    }

    return (max_left, max_right, left_sum + right_sum);

}

int findmaxsub(int* A, int low, int high){
    if( high == low){
        return (low, high, A[low]);
    } else {
        int mid = (low + high)/2;
        int left_low = findmaxsub(A, low, mid);
        int left_sum =  findmaxsub(A, low, mid);
        int left_high = findmaxsub(A, low, mid);

        int right_low = findmaxsub(A, mid + 1, high);
        int right_sum =  findmaxsub(A, mid + 1, high);
        int right_high = findmaxsub(A, mid + 1, high);

        int cross_low = maxsub(A, low, mid, high);
        int cross_sum =  maxsub(A, low, mid, high);
        int cross_high = maxsub(A, low, mid, high);

        if(left_sum >= right_sum && left_sum >= cross_sum){
            return (left_low, left_high, left_sum);
        } else if(right_sum >= left_sum && right_sum >= cross_sum){
            return (right_low, right_high, right_sum);
        } else{
            return (cross_low, cross_high, cross_sum);
        }

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
    
    cout << findmaxsub(array, 0, size-1);

}