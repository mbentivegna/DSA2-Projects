/*
Michael Bentivegna
Dijkstra Assignment
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
    node *fromN, *toN;
    edge *e = new edge;
    int weightINT;

    if(!hash->contains(from))
    {   
        fromN = new node;
        fromN->id = from;
        fromN->known = false;
        fromN->d_v = INT_MAX;
        nodeList.push_back(fromN);
        hash->insert(from, fromN);
        capacity++;
    }
    else
    {
        fromN = (node *) hash->getPointer(from);
    }

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

    weightINT = stoi(weight);
    e->c_vw = weightINT;
    e->destin = toN;
    fromN->adjList.push_back(e);
}

void graph::dijkstra(string &start)
{
    heap weights(capacity);

    node *first = (node *) hash->getPointer(start);
    first->d_v = 0;
    first->path.push_back(start);

    list<node *>::const_iterator it;
    for(it = nodeList.begin(); it != nodeList.end(); it++)
    {
        weights.insert((*it)->id, (*it)->d_v, *it);
    }

    node *tmp = nullptr;
    for(int i = 0; i < capacity; i++)
    {
        weights.deleteMin(nullptr, nullptr, &tmp);
        tmp->known = true;

        list<edge*>::const_iterator it;
        for (it = tmp->adjList.begin(); it != tmp->adjList.end() && tmp->d_v != INT_MAX; it++)
        {
            if((!(*it)->destin->known) && (tmp->d_v + (*it)->c_vw) < ((*it)->destin->d_v))
            {
                (*it)->destin->path.clear();
                (*it)->destin->path.insert((*it)->destin->path.begin(), tmp->path.begin(), tmp->path.end());
                (*it)->destin->path.push_back((*it)->destin->id);
                (*it)->destin->d_v = (*it)->c_vw + tmp->d_v;

                weights.setKey((*it)->destin->id, ((*it)->c_vw + tmp->d_v));
            }
        }
    }
}

void graph::writeTo(string &output)
{
    ofstream outF;
    outF.open(output);

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

            list<string>::const_iterator ite;
            for (ite = (*it)->path.begin(); ite != (*it)->path.end(); ite++) 
            {
                outF << *ite;
                if (next(ite, 1) != (*it)->path.end())
                {
                    outF << ", ";
                }
            }

            outF << "]" << "\n";
        }
    }
}
