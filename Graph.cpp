/*
 * Graph.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: np183
 */

#include "Graph.h"
#include <iostream>
Graph::Graph() {


}

Graph::Graph(const Graph& other) {
	for(int i=0; i<other.nodelist_.size();i++)
	{
	nodelist_.push_back(Node::create(other.nodelist_[i]->id(),other.nodelist_[i]->name()));

	}
	for(int i = 0; i < other.edgelist_.size();i++)
	{
		unsigned int saughtsource = other.edgelist_[i]->source()->id();
		unsigned int saughttarget = other.edgelist_[i]->target()->id();
		for(int k = 0; k<nodelist_.size();k++)
		{
			if(nodelist_[k]->id()==saughtsource)
			{
				for(int l=0;l<nodelist_.size();l++)
				{
					if(nodelist_[l]->id() == saughttarget)
					{
						edgelist_.push_back(new Edge(nodelist_[k],nodelist_[l]));
						break;
					}
				}
				break;
			}
		}
	}

	for(int i=0;i<other.edgelist_.size();i++)
	{
		unsigned int saughtid=edgelist_[i]->source()->id();
		for(int i = 0; i<nodelist_.size();i++) //finding node with saught id
		{
			if (nodelist_[i]->id() == saughtid )
			{
				nodelist_[i]->addEdge(edgelist_[i]->target());
				break;                                                 //does it break only the first for?
			}
		}
	}



}

Graph::Graph(Graph&& other) {
	for(int i=0; i<other.nodelist_.size();i++)
	{
		nodelist_.push_back(other.nodelist_[i]);                // i am just copying pointers it is not deep copy
	}
	for(int i=0; i<other.edgelist_.size();i++) 			//what about build in move for vectors?
	{
		edgelist_.push_back(other.edgelist_[i]);
	}
	{
		for(int i=0; i<other.nodelist_.size();i++)
		{
			other.nodelist_[i]=nullptr;
		}
		for(int i=0; i< other.edgelist_.size();i++)
		{
			other.edgelist_[i]=nullptr;
		}
		other.nodelist_.clear();
		other.edgelist_.clear();
	}

}

Graph::~Graph() {
for(int i=0; i<nodelist_.size();i++)
{
	delete nodelist_[i];                 // i am just copying pointers it is not deep copy
}
for(int i=0; i<edgelist_.size();i++)
{
	delete edgelist_[i];
}

nodelist_.clear();
edgelist_.clear();


}

bool Graph::addNode(uint id, const std::string& name) {
	bool notsameid=true;
	for(int i=0; i< nodelist_.size();i++)
	{
		if(nodelist_[i]->id() == id)
		{
			notsameid=false;
			return notsameid;
		}


	}
	nodelist_.push_back(Node::create(id,name));
	return notsameid;

}

bool Graph::addEdge(uint source, uint target) {
	bool sourceingraph=false;
	bool targetingraph=false;
	unsigned int sourceindex;
	unsigned int targetindex;
	for(int i=0; i<nodelist_.size();i++)            //should I check if they r the same?
	{
	  if(nodelist_[i]->id() ==source)
	  {
		  sourceingraph=true;
		  sourceindex=i;

	  }
	  if(nodelist_[i]->id() == target)
	  {
		  targetingraph=true;
		  targetindex=i;
	  }
	}
	for(int i=0;i<edgelist_.size();i++) //check if nodes are already connected
	{
		if(edgelist_[i]->source()->id()==source && edgelist_[i]->target()->id()==target)
		{
			return false;
		}
	}
	if(sourceingraph == true && targetingraph==true)   // check if the source in target are in graph
	{
		nodelist_[sourceindex]->addEdge(nodelist_[targetindex]);
		edgelist_.push_back(new Edge(nodelist_[sourceindex],nodelist_[targetindex]));

		return true;
	}
	else
	{

		return false;
	}
}

uint Graph::edges() const {
	return edgelist_.size();
}

uint Graph::nodes() const {
	return nodelist_.size();

}

const Node* Graph::node(uint loc) const {
  if (nodelist_.size()>loc)
  {
	  return nodelist_[loc];
  }
  else
  {
	  return nullptr;
  }
}

const Edge* Graph::edge(uint loc) const {
  if (edgelist_.size()>loc)
  {
	  return edgelist_[loc];
  }
  else
  {
	  return nullptr;
  }
}

int Graph::reach(uint source, uint target) const {
	bool sourcein;
	bool targetin;
	bool targetfound;
	bool sourcefound;
	unsigned int lasttarget = target;
	unsigned int tgrID;

	Node* currenttarget;
	Node* sourceptr=nullptr;
	Node* targetptr=nullptr;
	vector<vector<Node*>> layers;
	vector<int> seen;
	vector<Node*> currentlayer;
	int index=0;


	for (int i= 0; i<nodelist_.size(); i++)
	{
		if(nodelist_[i]->id() == source)
		{
			sourcein=true;
			sourceptr = nodelist_[i];
		}
		if(nodelist_[i]->id() == target)
		{
			targetin=true;
		}
	}

	if(!sourcein && !!targetin)
	{
		return -1;

	}

	if(source == target)    // if they r the same - primitive solution
		{
			return 0;
		}

	if(sourceptr->edges()==0)
		return -1;

	seen.push_back(source);
	currentlayer.push_back(sourceptr);
	layers.push_back(currentlayer);

	// ------------------------BFS breadth first search -----------------------------

	for(int i = 0; i < layers.size(); i++)
	{
		vector<Node*> nodesinlayer;
		for (int j = 0 ; j < layers[i].size();j++)
		{
			currenttarget = layers[i][j];
			for(int k = 0; k < currenttarget->edges();k++)
			{
				targetptr = nullptr;
				targetptr = currenttarget->edge(k)->target();
				tgrID = targetptr->id();
				if(tgrID == lasttarget)
				{
					return i + 1;
				}
				for (int l = 0; l < seen.size();l++)
				{
					if(seen[l] == tgrID)
					{
						break;
					}
				}
				seen.push_back(tgrID);
				nodesinlayer.push_back(targetptr);
			}
		}
		if(nodesinlayer.size() == 0)
		{
			return -1;
		}
		layers.push_back(nodesinlayer);
	}
	return -1;
}







Graph& Graph::operator=(const Graph& other) {
	if(this!=&other)
	{
		nodelist_.clear();
		edgelist_.clear();
		for(int i=0; i<other.nodelist_.size();i++)
			{
			nodelist_.push_back(Node::create(other.nodelist_[i]->id(),other.nodelist_[i]->name()));

			}
			for(int i = 0; i < other.edgelist_.size();i++)
			{
				unsigned int saughtsource = other.edgelist_[i]->source()->id();
				unsigned int saughttarget = other.edgelist_[i]->target()->id();
				for(int k = 0; k<nodelist_.size();k++)
				{
					if(nodelist_[k]->id()==saughtsource)
					{
						for(int l=0;l<nodelist_.size();l++)
						{
							if(nodelist_[l]->id() == saughttarget)
							{
								edgelist_.push_back(new Edge(nodelist_[k],nodelist_[l]));
								break;
							}
						}
						break;
					}
				}

			}
		return *this;
		}
}

Graph& Graph::operator=(Graph&& other) {
	if(this!=&other)
	{
		nodelist_.clear();
		edgelist_.clear();

		for(int i=0; i<other.nodelist_.size();i++)
		{
			nodelist_.push_back(other.nodelist_[i]);                // i am just copying pointers it is not deep copy
		}
		for(int i=0; i<other.edgelist_.size();i++) 			//what about build in move for vectors?
		{
			edgelist_.push_back(other.edgelist_[i]);
		}

		{
			for(int i=0; i<other.nodelist_.size();i++)
			{
				other.nodelist_[i]=nullptr;
			}
			for(int i=0; i< other.edgelist_.size();i++)
			{
				other.edgelist_[i]=nullptr;
			}
			other.nodelist_.clear();
			other.edgelist_.clear();
		}
	}


	return *this;
}

