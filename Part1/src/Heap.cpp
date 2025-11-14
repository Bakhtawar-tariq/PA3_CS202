#include "Heap.h"
#include <iostream>
#include <climits> 

using namespace std;

MinHeap::MinHeap(int cap)
{
   capacity=cap;
   heap_size = 0;
   harr = new int[cap];
}

MinHeap::~MinHeap()
{
    delete[] harr;
}

MinHeap::MinHeap(const MinHeap& other)
{
    capacity = other.capacity;
    heap_size = other.heap_size;
    harr = new int[capacity];
    for (int i = 0; i < heap_size; i++){
        harr[i] = other.harr[i];
    }
}

MinHeap& MinHeap::operator=(const MinHeap& other)
{
    if (this == &other){
        return *this;
    }
    capacity = other.capacity;
    heap_size = other.heap_size;
    delete[] harr;
    harr = new int[capacity];
    for (int i = 0; i < heap_size; i++){
        harr[i] = other.harr[i];
    }
    return *this;
}

int MinHeap::extractMin()
{
    if (heap_size <= 0){
        return INT_MAX;
    }
    if (heap_size == 1){
        heap_size--;
        return harr[0];
    }
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    minHeapify(0);

    return root;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && (harr[parent(i)] > harr[i])){
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::increaseKey(int i, int new_val)
{
    harr[i] = new_val;
    minHeapify(i);
}

int MinHeap::getMin() const
{
    if (heap_size <= 0){
        return INT_MAX;
    }
    return harr[0];
}

void MinHeap::deleteKey(int i)
{
    harr[i] = INT_MIN;
    while (i != 0 && (harr[parent(i)] > harr[i])){
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
    extractMin();
}

void MinHeap::insertKey(int k)
{
    if (heap_size == capacity){
        capacity = capacity*2;
        int* arr = new int[capacity];
        for (int i = 0; i < heap_size; i++){
            arr[i] = harr[i];
        }
        delete[] harr;
        harr = arr;
    }

    harr[heap_size] = k;
    int i = heap_size;
    while (i != 0 && (harr[parent(i)] > harr[i])){
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
    heap_size++;
}

void MinHeap::minHeapify(int i)
{
    int r_indx= right(i);
    int l_indx= left(i);
    int small = i;

    if (r_indx < heap_size && harr[r_indx] < harr[i]){ 
        small = r_indx;
    }
    if(l_indx < heap_size && harr[l_indx]< harr[i]){
        small = l_indx;
    }
    if (small != i){
        swap(&harr[i],&harr[small]);
        minHeapify(small);
    }
}