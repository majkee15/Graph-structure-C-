/*
 * Graph.h
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Edge.h"
#include "vector"
using std::vector;
class Graph {
public:
  // Build an empty graph
  Graph();

  // Copy and move constructors



  Graph(const Graph&);
  Graph(Graph&&);

  // Destructor
  ~Graph();

  // Create a node with these parameters and add to the graph.
  // If a node of this id already exists, this should fail and return false.
  bool addNode(unsigned int id, const std::string& name);

  // Get the id-s of two nodes that should already be in the graph and add an
  // Edge between them.
  // If one of the nodes (or both) does not exist in the graph return false.
  bool addEdge(unsigned int ,unsigned int);

  // Return the number of edges and number of nodes and
  // allow access to them.
  // Some protection by casting the poitners to const pointers.
  // Notice that the order of nodes and order of edges should respect
  // the order in which they were created.
  unsigned int edges() const;
  unsigned int nodes() const;
  const Edge* edge(unsigned int) const;
  const Node* node(unsigned int) const;

  // Return the distance in the graph between the two nodes.
  // If the target is not reachable from the source return -1.
  int reach(unsigned int, unsigned int) const;

  // Assignment operators implementing copy and move semantics
  Graph& operator=(const Graph&);
  Graph& operator=(Graph&&);
private:

vector <Node*> nodelist_;
vector <Edge*> edgelist_;


};

#endif /* GRAPH_H_ */
