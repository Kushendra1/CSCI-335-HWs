#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH
/* Kushendra Ramrup
CSCI 335
Prof Raja
Assignment 5

The graph class and vertex structure used in both parts of the assignment.

*******************************PUBLIC MEMBERS********************************
  Graph(const int size = 0) : vertices_(size), total_{size} -> graph constructor
  void connectPoints(const int pointA, const int pointB, float value) -> adds directed edge between two vertices
  float isConnected(const int pointA, const int pointB) -> determines if thre is an edge already between two vertices
  void dijkstra(const int pointA) -> public accessor for the private dikstra func and also outputs results in required format
******************************PRIVATE MEMBERS********************************
  Vertex structure
  ----------------------------------------------------------------------------
    Vertex() : vertex_{0}, real_ver_{false}, distance_{0.0}, prev_{nullptr} -> default constructor
    Vertex(int vertex) : vertex_{vertex}, real_ver_{false}, distance_{0.0}, prev_{nullptr} -> parameterized constructor
    bool operator<(const Vertex & rhs) const -> operator < definition
    ~Vertex() -> Destructor
    vector<Vertex*> adjacent_vertices_ -> list of adjacent vertices
    vector<float> values -> list of edge weights
    int vertex_ -> the vertex being worked with
    bool real_ver_ -> to see if the vertex is in the graph
    float distance_ -> the distance between two vertices
    Vertex* prev_ -> a pointer to the vertex before vertex_
  ----------------------------------------------------------------------------
  vector<Vertex> vertices_ -> a list of all vertices
  int total_ -> the total count of vertices
  void dijkstraAlgorithm(const int pointA) -> performs Dijkstra's algorithm using a beginning vertex
  void printPath(Vertex &ver) -> outputs a path to a certain vertex
  bool path(const Vertex &ver, const int pointA)  -> determines if a path already exists to a vertex
*/
#include <iostream>
#include <vector>
#include <limits.h>
#include <iomanip>
#include "binary_heap.h"
using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outsode those statements

class Graph {
  public:
    // Default "big five" --
   // Zero-parameter constructor.
   /*Graph() = default;

   // Copy-constructor.
   Graph(const Graph &rhs) = default;

   // Copy-assignment.
   Graph& operator=(const Graph &rhs) = default;

   // Move-constructor.
   Graph(Graph& rhs) = default;

   // Move-assignment.
   Graph& operator=(Graph& rhs) = default;

   //Destructor
   ~Graph() = default; */

   // Constructor
   // @size Number of vertices to be created in the Graph.
    Graph(const int size = 0) : vertices_(size), total_{size} {

      // Set all proper/intuitive identities (NOT counting from 0).
      for(int i = 0; i < size; i++) {
        vertices_[i] = Vertex(i+1);
      }
    }

    /* The connectPoints function connects two vertices by adding a directed edge between them. It takes in
     @pointA and integer of the origin vertex, @pointB an integer of the target vertex, ad  @value
     a float weight for the new edge. Then, if conditions are met, it
     adds the edge between the two vertices. */
    void connectPoints(const int pointA, const int pointB, float value) {
      if(isConnected(pointA, pointB) != -1.0 || pointA == pointB) {  // Check if an edge already exists
        return;
      }
      vertices_[pointA - 1].adjacent_vertices_.push_back(&(vertices_[pointB-1]));  // Add edge properties to origin vertex - target and weight.
      vertices_[pointA - 1].values.push_back(value);

    }

    /* The isConnected function checks for already existing edges between two points @pointA and
    @pointB, both are integers representing the origin vertex and target vertex respectfully.
    Then the Function returns a float variable @value of the edge.
    If there is no edge then it returns -1. */
    float isConnected(const int pointA, const int pointB) {
      float value = -1.0;
      auto ver1 = vertices_[pointA - 1].adjacent_vertices_.begin();
      auto ver2 = vertices_[pointA - 1].values.begin();
      auto ver3 = vertices_[pointA - 1].adjacent_vertices_.end();
      for(auto i = ver1; i != ver3; i++) {
        if((*i)->vertex_ == pointB) {
          value = *ver2;
          break;
        }
        ver2++;
      }
      return value;
    }

    /* Public function that acts as an accessor for the private dijkstraAlgorithm function, in order
    to run Dijkstra's ALgorithm on the graph. @pointA is an integer reprsenting the origin vertex,
    needed. Then Dijkstra's algorithm is executed by calling the
    private function and the path information is outputed. */
    void dijkstra(const int pointA) {
      dijkstraAlgorithm(pointA);       // Call private func for Dijkstra's algorithm.
      for(int i = 0; i < total_; i++) {      // Output results
        /*If there does NOT exist a path to a particular vertex in the graph, the output for the path to that
        vertex should display: not_possible */
        if(vertices_[i].distance_ == INT_MAX) {
          cout << vertices_[i].vertex_ << ": ";
          cout<< "not_possible" <<endl;
        }
        else {
          cout << vertices_[i].vertex_ << ": ";
          printPath(vertices_[i]);
          cout << "cost: " << fixed << setprecision(1) << vertices_[i].distance_ << endl;
        }
      }
    }

private:
  struct Vertex {
  /* The Default Constructor of the structure, used to make vertex objects with the following properties
  @vertex_ represents the vertex, @real_ver_ short for real vertex represents whether or not the vertex is
  in the graph, @distance_ represents the distance between the vertices, and @prev_ represents the vertex
  before the vertex being dealt with.
  */
  Vertex() : vertex_{0}, real_ver_{false}, distance_{0.0}, prev_{nullptr} { }

  /* The Parameterized Constructor of the structure, used to make vertex objects with the following properties
  @vertex_ represents the vertex, @real_ver_ short for real vertex represents whether or not the vertex is
  in the graph, @distance_ represents the distance between the vertices, and @prev_ represents the vertex
  before the vertex being dealt with.
  @vertex is the new vertex made
  */
  Vertex(int vertex) : vertex_{vertex}, real_ver_{false}, distance_{0.0}, prev_{nullptr} { }

  // Operator <is used to see the distance in a copy object and if it is less
  bool operator<(const Vertex & rhs) const {
    return distance_ < rhs.distance_;
  }

  // Destructor
  ~Vertex() {
    prev_ = nullptr;
  }

  // Data members
  vector<Vertex*> adjacent_vertices_; //list of adjacent vertices in respect to the vertex worked on.
  vector<float> values; //list of edge weights for each edge, the "value" of the edge
  int vertex_; //the vertex being worked with
  bool real_ver_; //to see if the vertex is in the graph
  float distance_; //the distance between two vertices
  Vertex* prev_; //a pointer to the vertex before vertex_

  };

  vector<Vertex> vertices_; // a list of all vertices
  int total_; // the total amount of vertices

  /* The dijkstraAlgorithm function performs Dijkstra's algorithm for a given beginning vertex, in this
  case the integer @pointA -will be used to calculate paths and distances. The function uses a
  priority queue from a binary heap for selection of vertices. It also reinserts a vertex into the
  queue after the distance of an unknown vertex is updated and ignores known vertices that have been
  dequeued. The graph the functon will work on must be properly initialized.If the conditions are met then
  Dijkstra's will be executed, distance values will be recorded in all vertices and so will a pointer
  in the vertices to the previous one. */
  void dijkstraAlgorithm(const int pointA) {
    BinaryHeap<Vertex> binary_vertex_heap;     // Create Queue and initialize all vertices

    for(int i = 0; i < total_; i++) {  //assign distance of infinity for each vertex
      vertices_[i].distance_ = INT_MAX;       //the infinite distance is no connection
      vertices_[i].real_ver_ = false;
    }
    vertices_[pointA-1].distance_ = 0.0;
    binary_vertex_heap.insert(vertices_[pointA-1]); // Insert origin into the queue
    while(true) {
      bool success = false;
      int vertex = 0; // Selected vertex identity.
      while(!binary_vertex_heap.isEmpty() && !success) {
        vertex = (binary_vertex_heap.findMin()).vertex_;
        binary_vertex_heap.deleteMin();

        if(!vertices_[vertex - 1].real_ver_) {
          success = true;
        }
      }
      if(!success) {       // If no unknown vertices remain then stop algorithm.
        break;
      }
      Vertex &selected = vertices_[vertex-1];       // Else operate on selected vertex.
      selected.real_ver_ = true;

      auto ver1 = selected.adjacent_vertices_.begin();
      auto ver2 = selected.values.begin();
      auto ver3 = selected.adjacent_vertices_.end();

      /* The following code block goes through vertices next to the selected one and if it is unknown
      and the sum of the distance and cost is less than the previous known distance and path is
      updated the vertex is reinserted. */
      for(auto pointA = ver1; pointA != ver3; pointA++) {
        if(!(*pointA)->real_ver_) {
          float ver_cost = *ver2;

          if((selected.distance_ + ver_cost) < (*pointA)->distance_) {
            (*pointA)->distance_ = selected.distance_ + ver_cost;
            (*pointA)->prev_ = &selected;
            binary_vertex_heap.insert(*(*pointA));
          }
        }
        ver2++;
      }
    }
  }

  /* The function printPath is used for outputing a path to a vertex, by calling itself recursively
  to go back in the path. It takes in vertex @ver to print the path from origin. If Dijkstra's
  algorithm has been run to make the path from an origin vertex to ver, then the path  will be
  printed out. */
  void printPath(Vertex &ver) {
    if(ver.prev_ != nullptr)
      printPath(*(ver.prev_));
    cout << ver.vertex_  << " ";
  }

  /* The function printPath is used to determine is a path exists to a particular vertex in the graph.
  It takes in vertex @ver and integer @pointA the starting point and vertex to travel to. If there is
  not a path, then this helper would return false and allow outputing of "not_possible" in Dijkstra */
  bool path(const Vertex &ver, const int pointA) {
    if(ver.prev_ == nullptr){
      if(ver.vertex_ == pointA) {
        return true;
      } else {
        return false;
      }
    } else {
      return path(*(ver.prev_), pointA);
    }
  }

};


#endif /* STUDENT_GRAPH */
