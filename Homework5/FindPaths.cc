/* Kushendra Ramrup
CSCI 335
Prof Raja
Assignment 5

This file for part 2 of the assignement re uses the openFile function and makeGraph funtion from
part 1's CreateGraphAndTest file. Using them to read in a file of edges and making a graph from them,
Dijkstra's Algorithm is called on the newly made graph in pathfindDriver where the starting vertex
had to be converted through stoi.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "graph.h"

using namespace std;
/* The function openFile is used for opening input and query files, taking in the string
@filename of a txt file and returning @input a filestream. If it fails to open the input
and eroor message will be delivered. */
ifstream openFile(const string filename) {
  ifstream input;
  input.open(filename);
  if(input.fail()) {
    cout << "Cannot read from " << filename;
    exit(1);
  }
  return input;
}

/* The function makeGraph is used for creating a graph for a txt file that's inputed through string
@filename a filename of a .txt file containing graph the information size and directed edges. The
function returns a Graph object with the specifications from the input file. */
Graph makeGraph(const string filename) {
  ifstream Input = openFile(filename);
  int size(0), vertexA(0), vertexB(0);
  float value(0.0);
  string line;
  stringstream streamLine;
  getline(Input, line);   // Take in size and initialize Graph
  streamLine.str(line);
  streamLine >> size;
  Graph newGraph(size);
  while(getline(Input, line)) {   // Take in directed edges and make the Graph
    streamLine.clear();
    streamLine.str(line);
    streamLine >> vertexA;
    while(streamLine >> vertexB) {
      streamLine >> value;
      newGraph.connectPoints(vertexA, vertexB, value);
    }
  }
  //Close file
  Input.close();
  return newGraph;
}

int pathfindDriver(int argc, char **argv) {
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.
  int starting_vertex = std::stoi(argv[2]);
  const string graph_filename(argv[1]);
  Graph testGraph = makeGraph(graph_filename);   // Create Graph
  testGraph.dijkstra(starting_vertex);

  return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
