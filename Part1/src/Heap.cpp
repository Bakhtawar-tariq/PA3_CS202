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
    return 0;
}

void MinHeap::decreaseKey(int i, int new_val)
{
}

void MinHeap::increaseKey(int i, int new_val)
{
}

int MinHeap::getMin() const
{
    return 0;
}

void MinHeap::deleteKey(int i)
{
}

void MinHeap::insertKey(int k)
{
}

void MinHeap::minHeapify(int i)
{
}