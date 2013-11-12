#include <fstream>
#include "inventry.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;

InvEntry::InvEntry(std::string w, Node *n)
{
	this->word = w;
	this->next = n;
}


InvEntry::~InvEntry()
{
	Node * tmp;
	while(this->next != NULL) {
		tmp = this->next;
		this->next = this->next->next;
		delete tmp;
		tmp = NULL;
	}
}


// prepend new occurrence of word
// its docId and position
void InvEntry::add_item(Node *n)
{
	// insert new node at front
	n->next = this->next;
	this->next = n;
}

string InvEntry::getWord()
{
	return word;
}

void InvEntry::print_entry_to_file(char* outputfile)
{
	ofstream file;
	file.open(outputfile,ios::app);
	if( file.is_open() ) {

		Node * n = this->next;

		file << this->word << "\t";
		cout << this->word << "\t";
		while( n ){
			file << "(" << n->doc_id << "," << n->position << ")";
			cout << "(" << n->doc_id << "," << n->position << ")";

			if( n->next ){
				file << ",";
				cout << ",";
			}

			n = n->next;
		}
		cout << endl;
		file << endl;
	}
	file.close();
}
