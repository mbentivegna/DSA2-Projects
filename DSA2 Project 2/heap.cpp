/*
Michael Bentivegna
Heap Assignment
*/

#include <iostream>
#include "heap.h"

using namespace std;

heap::heap(int capacity)
{ 
    data.resize(capacity+1);
    this->capacity = capacity + 1;
    hash = new hashTable(this->capacity*2);
    filled = 0;
}

int heap::insert(const std::string &id, int key, void *pv)
{
    if (filled < capacity)
    {
        if(hash->contains(id) == true)
        {
            return 2;
        }
        else
        {
            filled++;

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

int heap::setKey(const std::string &id, int key)
{
    if (hash->contains(id) == true)
    {
        node *p = static_cast<node *>(hash->getPointer(id));
        int index = getPosition(p);

        int tmp = data[index].key;
        data[index].key = key;

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

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (filled > 0)
    {
        if (pId != NULL) 
        {
            *pId = data[1].id;
        }
        if (pKey != NULL)
        {
            *pKey = data[1].key;
        } 
        if (ppData != NULL)
        {
            *(static_cast <void**> (ppData)) = data[1].pData;
        } 

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

int heap::remove(const std::string &id, int *pKey, void *ppData) 
{
    if(hash->contains(id) == true)
    {
        node* p= static_cast<node *>(hash->getPointer(id));
        int index = getPosition(p);

        if (pKey != nullptr)
        {
            *pKey = p->key;
        } 
        if (ppData != nullptr)
        {
            *(static_cast <void**> (ppData)) = p->pData;
        } 

        setKey(id, INT_MIN);
        deleteMin();

        return 0;
    }
    else
    {
        return 1;
    }  
}

void heap::percolateUp(int pos)
{
    while(pos > 1 && (data[pos].key < data[pos/2].key))
    {
        node tmp = data[pos];

        data[pos] = data[pos/2];
        hash->setPointer(data[pos].id, &data[pos]);

        data[pos/2] = tmp;
        hash->setPointer(data[pos/2].id, &data[pos/2]);

        pos = pos/2;
    }
}

void heap::percolateDown(int pos) 
{ 
    node tmp = data[pos];

    int selectedChild;
    int leftChild;
    int rightChild;

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

    data[pos] = tmp;
    hash->setPointer(data[pos].id, &data[pos]);
}

int heap::getPosition(node *p) 
{
    return (p - &data[0]);
}

