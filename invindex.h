#ifndef __INVINDEX__
#define __INVINDEX__

#include <string>
#include "node.h"
#include "inventry.h"
#define MAXENTRIES 10000

using namespace std;
class InvIndex{
private:
	InvEntry entries[MAXENTRIES];
public:
	InvIndex();
	~InvIndex();
	void build_index(char * inputfile); // build index from the input file
	void save_print_index(char * outputfile); // save the index to the file and also print it to the screen
private:
	int is_indexed(string word); // is word already in index
	bool is_word(string s); // is word or number
	bool process_line(string line); // chop line into words and process each word
	bool process_word(int docId, string word, int wordPos); // index if new word, add doc info if already indexed
	int index_to_insert(string word); // where to insert new word in current index
	bool insert_word_at_index(InvEntry* entry, int i); // perform insert operation of new word in current index at entry i
private:
	int InvIndexSize; // return current size of index
};
#endif
