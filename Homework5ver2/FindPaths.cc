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
  float edgeWeight(0.0);
  string line;
  stringstream sLine;
  getline(Input, line);   // Take in size and initialize Graph
  sLine.str(line);
  sLine >> size;
  Graph newGraph(size);
  while(getline(Input, line)) {   // Take in directed edges and make the Graph
    sLine.clear();
    sLine.str(line);
    sLine >> vertexA;
    while(sLine >> vertexB) {
      sLine >> edgeWeight;
      newGraph.connectPoints(vertexA, vertexB, edgeWeight);
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
  float edgeWeight (0.0);
  string line;
  stringstream ssLine;
  while(getline(queryInput, line)) {   // For each query, check if edge exists betwen a and b
    ssLine.clear();
    ssLine.str(line);
    ssLine >> vertexA >> vertexB;
    edgeWeight = testGraph.isConnected(vertexA, vertexB);
    if(vertexA == vertexB) {
      cout << vertexA << " " << vertexB << ": not_connected";
    }
    else if(edgeWeight != -1.0) {
      cout << vertexA << " " << vertexB << ": connected " << edgeWeight;
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

int pathfindDriver(int argc, char **argv) {
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.
  int starting_vertex = std::stoi(argv[2]);
  const string graph_filename(argv[1]);
  Graph testGraph = makeGraph(graph_filename);   // Create Graph
  testGraph.dijkstra(starting_vertex);
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
