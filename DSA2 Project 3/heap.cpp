/*
Michael Bentivegna
Dijkstra Assignment

*/

#include <iostream>
#include "heap.h"

using namespace std;

//Constructor
heap::heap(int capacity)
{ 
    data.resize(capacity+1);
    this->capacity = capacity + 1;
    hash = new hashTable(this->capacity*2);
    filled = 0;
}

//Insert a new element into the priority queue
int heap::insert(const std::string &id, int key, void *pv)
{
    //Check to make sure we don't go out of bounds of the allotted heap size
    if (filled < capacity - 1)
    {
        //Check if the hashtable already contains the id
        if(hash->contains(id) == true)
        {
            return 2;
        }
        else
        {
            filled++;

            //Enter the data into the heap
            data[filled].id = id;
            data[filled].key = key;
            data[filled].pData = pv;

            hash->insert(id, &data[filled]);
            percolateUp(filled);

            return 0;
        }
    }
    else 
    {
        return 1;
    }
}

//Change the value of an id's corresponding key
int heap::setKey(const std::string &id, int key)
{
    //Check if the element exists in the queue
    if (hash->contains(id) == true)
    {
        //Change the key
        node *p = static_cast<node *>(hash->getPointer(id));
        int index = getPosition(p);

        int tmp = data[index].key;
        data[index].key = key;

        //Put the node in it's correct location
        if(data[index].key > tmp)
        {
            percolateDown(index);
        }
        else
        {
            percolateUp(index);
        }

        return 0;
    }
    else
    {
        return 1;
    }
}

//Delete the node with the smallest key value
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    //Make sure the heap isn't empty
    if (filled > 0)
    {
        if (pId != nullptr) 
        {
            *pId = data[1].id;
        }
        if (pKey != nullptr)
        {
            *pKey = data[1].key;
        } 
        if (ppData != nullptr)
        {
            *(static_cast <void**> (ppData)) = data[1].pData;
        } 

        //Delete the node and update the queue
        hash->remove(data[1].id);
        data[1] = data[filled];
        filled--;
        percolateDown(1);
        
        return 0;
    }
    else
    {
        return 1;
    }
}

//Remove an element given it's id
int heap::remove(const std::string &id, int *pKey, void *ppData) 
{
    //Make sure the element exists in the queue
    if(hash->contains(id) == true)
    {
        node* p= static_cast<node *>(hash->getPointer(id));

        if (pKey != nullptr)
        {
            *pKey = p->key;
        } 
        if (ppData != nullptr)
        {
            *(static_cast <void**> (ppData)) = p->pData;
        } 
        
        //Set the key to the smallest int, then delete min
        setKey(id, INT_MIN);
        deleteMin();

        return 0;
    }
    else
    {
        return 1;
    }  
}

//Update the heap by percolating up
void heap::percolateUp(int pos)
{
    //Loop if percolating up is required each time
    while(pos > 1 && (data[pos].key < data[pos/2].key))
    {
        node tmp = data[pos];

        data[pos] = data[pos/2];
        hash->setPointer(data[pos].id, &data[pos]);

        data[pos/2] = tmp;
        hash->setPointer(data[pos/2].id, &data[pos/2]);

        //Increment the location of the node to it's parent before looping
        pos = pos/2;
    }
}

//Update the heap by percolating down
void heap::percolateDown(int pos) 
{ 
    node tmp = data[pos];

    int selectedChild;
    int leftChild;
    int rightChild;

    //Decide whether the left or right child should used to percolate down
    //Check if either of them is smaller than the parent's key
    while ((2 * pos) <= filled) 
    {
        int leftChild = 2*pos;
        int rightChild = leftChild + 1;

        if (leftChild < filled && data[rightChild].key < data[leftChild].key) 
        {
            selectedChild = rightChild;
        } 
        else 
        {
            selectedChild = leftChild;
        }

        if (data[selectedChild].key < tmp.key) 
        {
            data[pos] = data[selectedChild];
            hash->setPointer(data[pos].id, &data[pos]);
        } 
        else 
        {
            break;
        }

        pos = selectedChild;
    }

    //Use tmp to fill in the last value
    data[pos] = tmp;
    hash->setPointer(data[pos].id, &data[pos]);
}

//Get index of the node given a pointer
int heap::getPosition(node *p) 
{
    return (p - &data[0]);
}

