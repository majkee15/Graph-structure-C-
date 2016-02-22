/*
 * Node.h
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>

class Node;

#include "Edge.h"

class Node {
public:
	Node() = delete;

	// I'm not going to test these functions directly.
	// But if you feel that they are useful for you
	// then you can implement them
	Node(const Node& other) = delete;
	Node(Node&&) = delete;
	~Node();

	static Node* create(unsigned int id, const std::string& name);
	// Creates a node with same id and same name.
	// Does not touch the edges!
	Node* copy() const;

	unsigned int id() const;
	std::string name() const;

	void addEdge(Node*);
	// Check if the node has a succcessor with this id.
	bool successor(unsigned int) const;

	// Return the number of successors the node has
	unsigned int edges() const;
	// Return the i-th successor of the node.
	// The order of edges respects the order
	// they were added to the node.
	const Edge* edge(unsigned int) const;

private:
	Node(unsigned int id, const std::string& name);
	void reallocate_();
	unsigned int id_;
	std::string name_;

	Edge** edges_;
	unsigned int edgesnum_;
	unsigned int edgescap_;

	static constexpr unsigned int CAPACITY_INCREASE = 10;
};

#endif /* NODE_H_ */
