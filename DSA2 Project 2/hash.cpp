/*
Michael Bentivegna
Hashtable Spellcheck Assignment

    A summary of this project can be found at the top of spellcheck.cpp.  This file implements the hashtable that is used to load the dictionary.
    It has the ability to rehash based on the number of words the dictionary contains and uses linear probing for collisions.
*/

#include "hash.h"
#include <iostream>

using namespace std;

vector<int>primes = {49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};

//Returns the first prime number bigger than size in the above sequence
unsigned int hashTable::getPrime(int size) {

    for (int i = 0; i < primes.size(); i++) 
    {
            if(primes[i] >= size)
            {
                return primes[i];
            }
    }

    return 0;
}

//Implements the size of the hashtable
hashTable::hashTable(int size) 
{
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;
}

//Inserts strings into hashtable (linear probing for collisions)
int hashTable::insert(const std::string &key, void *pv) 
{
    int hashIndex = hash(key); //Send to hash function
    int deletedIndex = -1;

    while (data[hashIndex].isOccupied == true) 
    {
        if (data[hashIndex].key == key)
        {
            if (data[hashIndex].isDeleted == true)
            {
                data[hashIndex].isDeleted = false;
                data[hashIndex].pv = pv;
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            if (data[hashIndex].isDeleted == true && deletedIndex == -1)
            {
                deletedIndex = hashIndex;
            }

            if (hashIndex != (capacity - 1)) 
            {
                hashIndex++; 
            } 
            else 
            {
                hashIndex = 0; 
            }
        }
    }

    if (deletedIndex != -1) 
    {
        hashIndex = deletedIndex;
    }

    //Insert key once open spot is available
    data[hashIndex].key = key;
    data[hashIndex].isOccupied = true;
    data[hashIndex].isDeleted = false;
    data[hashIndex].pv = pv;
    filled++;

    //Rehash if filled halfway
    if (capacity < 2*filled)
    {
        if(rehash() == false)
        {
            return 2;
        }
    }

    return 0;
}

//Hash function
int hashTable::hash(const string &key) 
{ 
    unsigned int value = 0;

    for (char ch : key)
    {
        value = 37 * value + ch;
    }

    return value % capacity;
}

//Returns position of a key within the hashtable or -1 if it doesn't exist
int hashTable::findPos(const string &key)
{
    int hashIndex = hash(key); //Send to hash function

    while (data[hashIndex].isOccupied == true)
    {
        if (data[hashIndex].key == key) 
        {
            if(data[hashIndex].isDeleted == false)
            {
                return hashIndex;
            }
            else
            {
                return -1;
            }
        }
        else 
        {
            if (hashIndex != (capacity - 1)) 
            {
                hashIndex++; 
            }
            else 
            {
                hashIndex = 0; 
            }
        }
    }

    return -1;
}

bool hashTable::remove(const std::string &key)
{
    int pos = findPos(key);
    if (pos == -1)
    {
        return false;
    }
    else 
    {
        data[pos].isDeleted = true;
        return true;
    }
}

//Return if findPos found the key or not
bool hashTable::contains(const string &key) 
{
    if (findPos(key) == -1) 
    {
        return false;
    } 
    else 
    {
        return true;
    }
}

//Resizes the hashtable to fit the dictionary length
bool hashTable::rehash() 
{
    int bigPrime = getPrime(2*capacity);

    vector<hashItem>temp = data; //Load data into temp vector
    
    try //Increase hashtable size and check for error
    {
        data.resize(bigPrime);
    } 
    catch(bad_alloc&) 
    { 
        return false;
    }

    //Change capacity and reset filled
    capacity = bigPrime;
    filled = 0;

    //Clear hashtable occupied boolean
    for (int i = 0; i < bigPrime; i++)
    {
        data[i].isOccupied = false;
    }

    //Re-enter relevant data into new hashtable
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i].isOccupied == true && temp[i].isDeleted == false) 
        {
            insert(temp[i].key, temp[i].pv);
        }
    }

    return true;
}

int hashTable::setPointer(const std::string &key, void *pv)
{
    int pos = findPos(key);
    if(pos == -1)
    {
        return 1;
    }
    else
    {
        data[pos].pv = pv;
        return 0;
    }
}

void * hashTable::getPointer(const std::string &key, bool *b)
{
    int pos = findPos(key);
    if (pos == -1)
    {
        if(b != nullptr)
        {
            *b = true;
        }

        return nullptr;
    }
    else
    {
        if(b != nullptr)
        {
            *b = false;
        }

        return data[pos].pv;
    }
}
