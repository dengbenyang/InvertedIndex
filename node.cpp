
#include "node.h"

Node::Node(int did, int pos, Node * n)
{
	this->doc_id = did;
	this->position = pos;
	this->next = n;
	return;

}

Node::~Node()
{

}
