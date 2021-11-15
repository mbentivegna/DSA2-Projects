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

        //Inititalizes large hash table and 0 capacity
        graph();

        //Sets up initial graph
        void initialInsert(string &from, string &to, string &str_weight);

        //Checks if beginning value entered by the user is in the graph
        bool startCheck(string &start);

        //Run dijstra's algorthim on the generated graph
        void dijkstra(string &start);

        //Write the correct output format to specified file
        void writeTo(string &outputFile);

    private:
        int capacity;
        hashTable *hash;
        class node;

        //Nested class for graph edges
        class edge 
        {
            public:
                int c_vw;
                node *destin;
        };

        //Nested class for graph vertices
        class node 
        {
            public:
                bool known;
                int d_v;
                string id; 

                list<edge *> adjList;
                list<string> path; //This is to make printing the path easier
        };

        list<node *> nodeList; 
};

#endif