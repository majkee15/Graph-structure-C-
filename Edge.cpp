/*
 * Edge.cpp
 */

#include "Edge.h"

Edge::Edge(Node* source, Node* target) : source_{source}, target_{target} {
}

Edge::~Edge() {
}

Node* Edge::source() const {
	return source_;
}

Node* Edge::target() const {
	return target_;
}
