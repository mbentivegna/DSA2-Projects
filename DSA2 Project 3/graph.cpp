/*
Michael Bentivegna
Dijkstra Assignment

    A summary of this project can be found in the useDijstra.cpp file.  This class has member functions 
capable of implementing dijskstra's algorthim with an efficient time complexity due to it's reliance on
both a hashtable and priority queue.  
*/

#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"

graph::graph() 
{
    capacity = 0;
    hash = new hashTable(100000);
}

void graph::initialInsert(string &from, string &to, string &weight)
{
    node *fromN, *toN; //Potential new node / Potential seen node
    edge *e = new edge; //New edge will always be made
    int weightINT; 

    //Initialize new nodes according to dijkstra's algorthim
    if(!hash->contains(from))
    {   
        //Starting values
        fromN = new node;
        fromN->id = from;
        fromN->known = false;
        fromN->d_v = INT_MAX;

        nodeList.push_back(fromN); //Put into nodelist
        hash->insert(from, fromN); //Enter into hashtable
        capacity++; //Increment for knowledge of total graph size
    }
    else
    {
        fromN = (node *) hash->getPointer(from);
    }

    //Same as above except for the receiving node
    if(!hash->contains(to))
    {
        toN = new node;
        toN->id = to;
        toN->known = false;
        toN->d_v = INT_MAX;
        nodeList.push_back(toN);
        hash->insert(to, toN);
        capacity++;
    }
    else
    {
        toN = (node *) hash->getPointer(to);
    }

    //Add new edge to starting node's adjacency list
    weightINT = stoi(weight);
    e->c_vw = weightINT;
    e->destin = toN;
    fromN->adjList.push_back(e);
}

bool graph::startCheck(string &start)
{
    //Check hashtable
    if(hash->contains(start))
    {
        return true;
    }

    return false;
}

void graph::dijkstra(string &start)
{
    //Make heap just large enough
    heap weights(capacity);

    //Set up starting node with correct distance / path
    node *first = (node *) hash->getPointer(start);
    first->d_v = 0;
    first->path.push_back(start);

    //Load all values into the heap
    list<node *>::const_iterator it;
    for(it = nodeList.begin(); it != nodeList.end(); it++)
    {
        weights.insert((*it)->id, (*it)->d_v, *it);
    }

    //Dijsktra's looping sequence
    node *tmp = nullptr;
    for(int i = 0; i < capacity; i++)
    {
        //Get smallest unknown node from heap
        weights.deleteMin(nullptr, nullptr, &tmp);
        tmp->known = true; //Now known

        //Go through adjacency list to potentially change connecting node's d_v
        list<edge*>::const_iterator it;
        for (it = tmp->adjList.begin(); it != tmp->adjList.end() && tmp->d_v != INT_MAX; it++)
        {
            if((!(*it)->destin->known) && (tmp->d_v + (*it)->c_vw) < ((*it)->destin->d_v))
            {
                //Change path
                (*it)->destin->path.clear();
                (*it)->destin->path.insert((*it)->destin->path.begin(), tmp->path.begin(), tmp->path.end());
                (*it)->destin->path.push_back((*it)->destin->id);

                //New d_v added to heap
                (*it)->destin->d_v = (*it)->c_vw + tmp->d_v;
                weights.setKey((*it)->destin->id, ((*it)->c_vw + tmp->d_v));
            }
        }
    }
}

void graph::writeTo(string &output)
{
    //Set up ouput stream
    ofstream outF;
    outF.open(output);

    //Loop through all nodes
    list<node*>::const_iterator it;
    for (it = nodeList.begin(); it != nodeList.end(); it++) 
    {
        outF << (*it)->id << ": ";

        if ((*it)->d_v == INT_MAX) 
        {
            outF << "NO PATH" << "\n";
        } 
        else 
        {
            outF << (*it)->d_v << " [";

            //Loops through string of vertex's for path
            list<string>::const_iterator ite;
            for (ite = (*it)->path.begin(); ite != (*it)->path.end(); ite++) 
            {
                outF << *ite;

                //No comma at the end before the bracket
                if (next(ite, 1) != (*it)->path.end())
                {
                    outF << ", ";
                }
            }

            outF << "]" << "\n";
        }
    }
}
