#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void reverseArray(int *arr, int size);

void shiftRight(int *arr, int size);

bool isSorted(int arr[], int size);

int sumArray(int arr[], int size);

int countEvens(int arr[], int size);

int findMax(int arr[], int size);

void replaceValue(int arr[], int size, int target, int replacement);

bool isPalindrome(int arr[], int size);

void reverseArray(int arr[], int size);

void shiftLeft(int arr[], int size);

void printArray(int arr[], int size);

void shiftRightByK(int arr[], int size, int k);

int removeDuplicates(int arr[], int size);

void mergeSorted(int arr1[], int size1, int arr2[], int size2, int result[]);

double maxAvg(int arr[], int size, int k);

int minSubArrayLen(int target, int* nums, int numsSize);

int main(){
    int arr[5] = {2, 3, 1, 1, 4, 3};
    printf("%d", minSubArrayLen(7, arr, 6));
}

void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int sumArray(int arr[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += arr[i];
    }
    return sum;
}

int countEvens(int arr[], int size){
    int counter = 0;
    for(int i = 0; i < size; i++){
        if(arr[i] % 2 == 0){
            counter++;
        }
    }
    return counter;
}

int findMax(int arr[], int size){
    int max = arr[0];
    for(int i = 0; i < size; i ++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

void replaceValue(int arr[], int size, int target, int replacement){
    for(int i = 0; i < size; i++){
        if(arr[i] == target){
            arr[i] = replacement;
        }
    }
}

bool isSorted(int arr[], int size){
    for(int i = 0; i < size - 1; i++){
        if(arr[i] < arr[i+1]){
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool isPalindrome(int arr[], int size){
    for(int i = 0; i < size/2; i++){
        int j = size - i - 1;
        if (arr[i] == arr[j]){
            continue;
        } else {
            return false;
        }
    }
    return true;
}

void reverseArray(int arr[], int size){
    for(int i = 0; i < size/2; i++){
        int j = size - i - 1;
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

void shiftLeft(int arr[], int size){
    int temp = arr[0];
    for(int i = 0; i < size - 1; i++){
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
}

void reverseSubArray(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[end];
        arr[end] = arr[start];
        arr[start] = temp;
        start++;
        end--;
    }
}

void shiftRightByK(int arr[], int size, int k) {
    if (size == 0) return; 
    k = k % size;          
    if (k == 0) return;    

    reverseSubArray(arr, 0, size - 1);
    
    reverseSubArray(arr, 0, k - 1);
    
    reverseSubArray(arr, k, size - 1);
}

int removeDuplicates(int arr[], int size) {
    if (size == 0 || size == 1) {
        return size;
    }
    
    int i = 1; // i is the Writer
    
    for (int j = 1; j < size; j++) { // j is the Reader
        // Compare the current Reader number to the number right behind it
        if (arr[j] != arr[j - 1]) {
            arr[i] = arr[j];
            i++;
        }
    }
    
    return i; // Return the final count
}

void mergeSorted(int arr1[], int size1, int arr2[], int size2, int result[]){
    int arrResult[size1 + size2];
    int i = 0;
    int j = 0;
    int k = 0;   
    while(k < size1 + size2){
        if (arr1[i] == arr2[j]){
            arrResult[k] = arr1[i];
            arrResult[k + 1] = arr1[i];
            i++;
            j++;
            k+=2;
        }
        if (arr1[i] > arr2[j]){
            arrResult[k] = arr2[j];
            j++;
            k++;
        }
        if (arr1[i] < arr2[j]){
            arrResult[k] = arr1[i];
            i++;
            k++;
        }
    }
}

void mergeSortedFixed(int arr1[], int size1, int arr2[], int size2, int result[]){
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k] = arr1[i];
            i++;
        } else {
            result[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < size1) {
        result[k] = arr1[i];
        i++;
        k++;
    }

    while (j < size2) {
        result[k] = arr2[j];
        j++;
        k++;
    }
}


// Implimented a static sliding window algorithm to solve a maxAvg array problem
double maxAvg(int arr[], int size, int k){
    int current_sum = 0;
    int max_sum = 0;
    for (int i = 0; i < k; i++){
        current_sum += arr[i];
    }
    max_sum = current_sum;
    for (int i = k; i < size; i++){
        current_sum += arr[k];
        current_sum -= arr[k - i];
        if (current_sum > max_sum){
            max_sum = current_sum;
        }
    }
    return (double)max_sum / k;
}

int minSubArrayLen(int target, int* nums, int numsSize){
    int total = 0;
    for(int i = 0; total < )
}
