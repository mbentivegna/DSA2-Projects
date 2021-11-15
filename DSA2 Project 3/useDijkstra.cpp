/*
Michael Bentivegna
Dijkstra Assignment

    This project begins by processing a user provided input file to generate a corresponding weighted directed graph.  After prompting the user
for the starting vertex, the program runs dijkstra's algorithm to determine the shortest path to each node.  The results are then printed to a 
specified output file.
*/

#include <fstream>
#include <iostream>
#include <string>
#include "graph.h"
#include <sstream>

using namespace std;

int main() 
{
    //Initialize strings and graph
    string start, inputFile, outputFile, oneLine;
    graph g;

    //Handle input file
    cout << "Enter name of graph file: ";
    cin >> inputFile;

    ifstream inF;
    inF.open(inputFile);

    //Read line by line til end of file
    while(getline(inF, oneLine))
    {
        //String processing
        string from, to, weight;
        stringstream word(oneLine);

        word >> from;
        word >> to;
        word >> weight;

        //Get graph setup
        g.initialInsert(from, to, weight);
    }

    //Loop until valid starting vertex is given
    while(true)
    {
        cout << "Enter name of starting vertex: ";
        cin >> start;

        if(g.startCheck(start))
        {
            break;
        }
    }

    //Run and time dijkstra's algorithm
    clock_t begin = clock();
    g.dijkstra(start);
    clock_t end = clock();

    double seconds = ((double)(end-begin)) / CLOCKS_PER_SEC;
    std::cout << "Time taken to apply dijkstra's algorithm (in seconds): " << seconds << "\n";

    //Get output file and run function for valid output syntax
    cout << "Enter name of output file: ";
    cin >> outputFile;

    g.writeTo(outputFile);
}