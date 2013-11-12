/* 
 * File:   inventry.h
 * Author: marcelle
 *
 * Created on October 14, 2013, 11:12 PM
 */

#ifndef INVENTRY_H
#define	INVENTRY_H

#include <string>
#include "node.h"

using namespace std;

// InvEntry is the index entry that contains the word and the linked list
class InvEntry{
private:
	std::string word; // indexed word
	Node * next; // pointer to the (docid, pos) list

public:
	InvEntry(){};
	InvEntry(std::string w, Node *n);
	~InvEntry();
	void add_item(Node *n); // add doc_id,position info node
	void print_entry_to_file(char* outputfile); // print entry out to console and log to text file
	string getWord(); // return word at entry
};
#endif	/* INVENTRY_H */

