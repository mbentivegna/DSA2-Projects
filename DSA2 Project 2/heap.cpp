#include <iostream>

#include "heap.h"

using namespace std;

heap::heap(int capacity)
{
    
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
    this->capacity = capacity + 1;
    size = 0;
}


