/*
 * Edge.h
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge;

#include "Node.h"

class Edge {
public:
	Edge() = delete;
	Edge(Node*, Node*);
	// Feel free to implement these functions as well
	Edge(const Edge&) = delete;
	Edge(Edge&&) = delete;

	~Edge();

	Node* source() const;
	Node* target() const;
private:
	Node* source_;
	Node* target_;
};

#endif /* EDGE_H_ */
