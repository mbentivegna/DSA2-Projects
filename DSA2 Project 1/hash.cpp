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
}

//Inserts strings into hashtable (linear probing for collisions)
int hashTable::insert(const std::string &key, void *pv) 
{
    int hashIndex = hash(key); //Send to hash function


    while (data[hashIndex].isOccupied == true) 
    {
        if (hashIndex != (capacity - 1)) 
        {
            hashIndex++; //linear probe
        } 
        else 
        {
            hashIndex = 0; //If end is reached start back from 0
        }
    }

    //Insert key once open spot is available
    data[hashIndex].key = key;
    data[hashIndex].isOccupied = true;
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

    while (data[hashIndex].isOccupied)
    {
        if (data[hashIndex].key == key) 
        {
            return hashIndex; //Return index only when key is found
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
        if (temp[i].isOccupied == true) 
        {
            insert(temp[i].key, temp[i].pv);
        }
    }

    return true;
}
