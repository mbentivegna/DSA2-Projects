/*
Michael Bentivegna
Dijkstra Assignment
*/

#include <fstream>
#include <iostream>
#include <string>
#include "graph.h"
#include <sstream>

using namespace std;

int main() 
{
    string start, inputFile, outputFile, oneLine;
    graph g;

    cout << "Enter name of graph file: ";
    cin >> inputFile;
    
    ifstream inF;
    inF.open(inputFile);

    while(getline(inF, oneLine))
    {
        string from, to, weight;
        stringstream word(oneLine);

        word >> from;
        word >> to;
        word >> weight;

        g.initialInsert(from, to, weight);
    }

    cout << "Enter name of starting vertex: ";
    cin >> start;

    clock_t begin = clock();
    g.dijkstra(start);
    clock_t end = clock();

    double seconds = ((double)(end-begin)) / CLOCKS_PER_SEC;
    std::cout << "Time taken to apply dijkstra's algorithm (in seconds): " << seconds << "\n";

    cout << "Enter name of output file: ";
    cin >> outputFile;

    g.writeTo(outputFile);
}