#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

/*
Name: Kushendra Ramrup
CSCI 335
Creates a graph and table(for the dijkstra algorithm & functionality
Private members:
std::map<int,std::vector<std::pair<int,double>>> graph;
std::map<int,Vertex> table;
*/

// Graph class
//
// ******************PUBLIC OPERATIONS*********************
// auto begin( )
// auto end( )
// bool insert( int vertex ) -> Insert vertex into graph
// bool insert( int vertex, std::pair<int,double> p ) -> Insert pair at vertex on the graph
// bool find( int vertex, int query_vertex ) -> Checks if vertex has query_vertex as an adjacent vertex
// double weight( int vertex, int query_vertex ) -> Returns weight of query
// double cost( int vertex ) -> Returns distance from table
// Vertex * table_vertex( int vertex ) -> Returns pointer to table vertex
// void printTable( ) -> Prints contents of the table
// bool possible( int starting_vertex, Vertex * v ) -> Returns true if path is possible
// void printPath( Vertex* v ) -> Prints path to query_vertex
// void dijkstra( int starting_vertex ) -> creates table and fills its contents

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <limits>
#include "binary_heap.h"

struct Vertex {
  //Data Members
  int vertex;
  std::vector<std::pair<int,double>> adjacent_vertices;
  bool known_ = false;
  double distance;
  Vertex * previous_vertex_;
};

class Graph {
 public:

  //PART 1 IMPLEMANTIONS------------------------------------------
  /*
    Accessor function for iterating through the graph
    accesses graph.begin()
  */
  auto begin() {
    return graph.begin();
  }

  /*
    Accessor function for iterating through the graph
    accesses graph.end()
  */
  auto end() {
    return graph.end();
  }

  /*
    Returns true if the insertion of vertex is successful
    If a vertex already exits, return false
  */
  bool insert(int vertex) {
    auto index = graph.find(vertex);
    if(index == graph.end()) {
      std::vector<std::pair<int,double>> v;
      graph.insert(std::make_pair(vertex,v));
      return true;
    } else {
      return false;
    }
  }

  /*
    Returns true if the insertion of vertex is successful
    If a vertex already exits, insert the pair into the vertex's vector
  */
  bool insert(int vertex, std::pair<int,double> p) {
    auto index = graph.find(vertex);
    if(index == graph.end()) { //DOES NOT EXIST ON GRAPH YET
      //instantiates a vector with the vertex cost pair
      std::vector<std::pair<int,double>> v;
      v.push_back(p);
      //inserts the vertex and vector into the map
      graph.insert(std::make_pair(vertex, v));
    } else { //EXISTS ON GRAPH
      //Acessess vector on the graph at vertex and insert p
      graph[vertex].push_back(p);
    }
    return true;
  }

  /*
    Returns true if a query_vertex is an adjacent vertex to vertex
    If the query does not exist in graph[vertex]'s vector, return false
  */
  bool find(int vertex, int query_vertex) {
    auto index = graph.find(vertex);
    if(index != graph.end()) { // if vertex found
      for(auto x: graph[vertex]) { //for each item in vertex's vector
	if(x.first == query_vertex) {
	  return true; //if the pair's first is the query_vertex
	}
      }
      return false; //adjacent_vertex is not in the vector
    } else { //vertex not found
      return false;
    }
  }

  /*
    Returns (double)weight if a query_vertex is an adjacent vertex to vertex and returns the pair's second
    Returns -1 if the query_vertex does not exist in the vector if the vertex does not exist
  */
  double weight(int vertex, int query_vertex) {
    auto index = graph.find(vertex);
    if(index != graph.end()) {
      for(auto x: graph[vertex]) {
	if(x.first == query_vertex) {
	  return x.second;
	}
      }
      return -1; //query_vertex DOES NOT EXIST
    } else {
      return -1; //vertex DOES NOT EXIST
    }
  }

  // PART 2 IMPLEMENATIONS -----------------------------------------------

  /*
    Returns the table's vertex's cost
  */
  double cost(int vertex) {
    return table[vertex].distance;
  }

  /*
    Returns Vertex pointer to the vertex in table
  */
  Vertex * table_vertex(int vertex) {
    return & table[vertex];
  }

  /*
    Prints the contents of the table (for testing purposes)
  */
  void printTable() {
    for(auto it = table.begin(); it != table.end(); ++it) {
      std::cout << it->second.vertex;
      for(auto item: it->second.adjacent_vertices) {
	std::cout << " {" << item.first << ", " << item.second << "}";
      }
      std::cout << " " << it->second.known_ << " " << it->second.distance;
      std::cout << "\n";
    }
  }

  /*
    Returns true if the previous_vertex_ from v to starting_vertex exists
  */
  bool possible(int starting_vertex, Vertex * v) {
    if(v->previous_vertex_ == nullptr) {
      if(v->vertex == starting_vertex) {
	return true;
      } else {
	return false;
      }
    } else {
      return possible(starting_vertex,v->previous_vertex_);
    }
  }

  /*
    Prints the previous_vertex_ from v to starting_vertex exists
  */
  void printPath( Vertex* v ) {
    if(v->previous_vertex_ != nullptr) {
      printPath(v->previous_vertex_);
      cout << " ";
    }
    std::cout << v->vertex;
  }

  void dijkstra(int starting_vertex) {
    //Creates table with initial/default values -> table set up
    for(auto it = graph.begin(); it != graph.end(); ++it) {
      int index = it->first;
      double d = std::numeric_limits<double>::infinity();
      Vertex v = {index, it->second , false , d, nullptr };
      table.insert(std::make_pair(index,v));
    }

    BinaryHeap<int> priority_queue; //Stores vertices
    table[starting_vertex].distance = 0; //starting_vertex
    priority_queue.insert(starting_vertex);

    while(!priority_queue.isEmpty()) {
      int v = priority_queue.findMin();
      table[v].known_ = true; //current vertex marked as known_
      priority_queue.deleteMin();

      //for each adjacent vertex
      for(auto w: table[v].adjacent_vertices) {
	double previous_vertex__cost = w.second;
	if(table[w.first].known_ == false) { //NOT known_ OR CHECKED
	  if(table[v].distance + previous_vertex__cost < table[w.first].distance) {
	    Vertex * w_pointer = & table[w.first];
	    //UPDATE W
	    priority_queue.insert(w.first);
	    w_pointer->distance = table[v].distance + previous_vertex__cost;
	    w_pointer->previous_vertex_ = & table[v];
	  }
	} else if(table[w.first].known_ == true && table[v].distance + previous_vertex__cost < table[w.first].distance) { //known_ BUT THE DISTANCE IS SHORTER THAN WHAT'S RECORDED ON THE TABLE
	  Vertex * w_pointer = & table[w.first];
	  //UPDATE W
	  priority_queue.insert(w.first);
	  w_pointer->distance = table[v].distance + previous_vertex__cost;
	  w_pointer->previous_vertex_ = & table[v];
	}
      }
    }
  }

 private:
  std::map<int,std::vector<std::pair<int,double>>> graph; //Part 1
  std::map<int,Vertex> table; //Part 2: Dijkstar Algo
};



#endif
