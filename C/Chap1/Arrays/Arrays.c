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

int main(){
    int arr[6] = {1, 2, 3, 4, 5,6};
    return 0;
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
    for(int i = 0; i < size; i++){
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