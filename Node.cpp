/*
 * Node.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: np183
 */

#include "Node.h"

using std::string;

Node::Node(unsigned int id, const string&  name)
: id_{id}, name_{name}, edges_{nullptr}, edgesnum_{0}, edgescap_{0} {
}

//Node::Node(Node&& other)
//: id_{other.id_}, name_{std::move(other.name_)}, edges_{other.edges_}, edgesnum_{other.edgesnum_}, edgescap_{other.edgescap_} {
//	other.edges_=nullptr;
//	other.edgesnum_=0;
//	other.edgescap_=0;
//}
//
Node::~Node() {
	for (unsigned int i=0 ; i<edgesnum_ ; ++i) {
		delete edges_[i];
	}
	if (edges_) {
		delete [] edges_;
	}
}

Node* Node::create(unsigned int id, const string& name) {
	return new Node(id, name);
}

Node* Node::copy() const {
	return new Node(id_, name_);
}

unsigned int Node::id() const {
	return id_;
}

string Node::name() const {
	return name_;
}

void Node::addEdge(Node* other) {
	if (edgesnum_==edgescap_) {
		reallocate_();
	}
	edges_[edgesnum_++] = new Edge(this,other);
}

bool Node::successor(unsigned int target) const {
	for (unsigned int i=0 ; i<edgesnum_ ; ++i) {
		if (edges_[i]->target()->id() == target) {
			return true;
		}
	}
	return false;
}

unsigned int Node::edges() const {
	return edgesnum_;
}

const Edge* Node::edge(unsigned int loc) const {
	if (loc >= edgesnum_) {
		return nullptr;
	}
	return edges_[loc];
}

void Node::reallocate_() {
	Edge** temp{new Edge*[edgescap_ + CAPACITY_INCREASE]};
	for (unsigned int i=0 ; i<edgescap_ ; ++i) {
		temp[i] = edges_[i];
	}
	for (unsigned int i=edgescap_ ; i<edgescap_ + CAPACITY_INCREASE ; ++i) {
		temp[i] = nullptr;
	}
	if (edges_) {
		delete [] edges_;
	}
	edges_ = temp;
	edgescap_ += CAPACITY_INCREASE;
}
