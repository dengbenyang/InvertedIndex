
#ifndef __NODE__
#define __NODE__

class Node{
public:
	int doc_id, position;
	Node * next;

	Node(int docid, int pos, Node * next);
	~Node();
};

#endif
