#ifndef _GRAPH_H
#define _GRAPH_H

#include <fstream>
#include <list>
#include <string>
#include <climits>
#include "heap.h"

using namespace std;

class graph 
{

    public:
        graph();

        void initialInsert(string &from, string &to, string &str_weight);

        void dijkstra(string &start);

        void writeTo(string &outputFile);

    private:
        int capacity;
        hashTable *hash;
        class node;

        class edge 
        {
            public:
                int c_vw;
                node *destin;
        };

        class node 
        {
            public:
                bool known;
                int d_v;
                string id; 

                list<edge *> adjList;
                list<string> path;
        };

        list<node *> nodeList; 
};

#endif