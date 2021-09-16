/* Kushendra Ramrup
CSCI 335
Prof Raja
Assignment 5

The file for part 1 of the assignment with the functions openFile and makeGraph. openFile was made as a
helper so I didn't have to re type the enitre ifstream input and error message everytime I needed to use it
and is describe below. makeGraph is the function that takes the information from the txt files and creats
a graph with the properties from the txt. The first line is the number of vertices. Each vertex is represented
by an integer from 1 to N.
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
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

/* The function queryGraph is used for querying a an already existing directed graph. It takes in
a string @query_filename of txt file containing edge queries with an oigin vertex and target vertex
and a graph object @testGraph to be queried. The function outputs the results of the edge queries. */
void queryGraph(const string query_filename, Graph & testGraph) {
  ifstream queryInput = openFile(query_filename);   // Open query file
  int vertexA(0), vertexB(0);
  float value (0.0);
  string line;
  stringstream ssLine;
  while(getline(queryInput, line)) {   // For each query, check if edge exists betwen a and b
    ssLine.clear();
    ssLine.str(line);
    ssLine >> vertexA >> vertexB;
    value = testGraph.isConnected(vertexA, vertexB);
    if(vertexA == vertexB) {
      cout << vertexA << " " << vertexB << ": not_connected";
    }
    else if(value != -1.0) {
      cout << vertexA << " " << vertexB << ": connected " << value;
    }
    else {
      cout << vertexA << " " << vertexB << ": not_connected";
    }
    cout << endl;
  }
  //cout << endl;
  //Close file
  queryInput.close();
}

int graphTestDriver(int argc, char **argv) {
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.
  const string graph_filename(argv[1]);
  const string query_filename(argv[2]);

  Graph testGraph = makeGraph(graph_filename);   // Create Graph
  queryGraph(query_filename, testGraph);   // Test Graph

  return 0;
}

int main(int argc, char **argv) {
  if (argc != 3) {
		cout << "Usage: " << argv[0] << " <graphtxtfilename>" << "<querytxtfilename>" << endl;
		return 0;
  }
  graphTestDriver(argc, argv);
  return 0;
}
