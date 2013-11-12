#include <fstream>
#include "invindex.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;

InvIndex::InvIndex()
{
	InvIndexSize = 0;
}

InvIndex::~InvIndex()
{
    
}

void InvIndex::build_index(char * inputfile) // build index from the input file
{
	string line;
	ifstream file;

	file.open(inputfile,ios::in);
	if( file.is_open() ) {
		while( getline(file,line) ) {
			process_line(line);
		}
	}
	file.close();
}

bool InvIndex::process_line(string line)
{
	int notSet = -1;
	string currentWord = "";
	int docId = notSet;
	int wordPos = 0;

	for(int i = 0; i <= line.length(); i++){

		// get last word of doc
		if( i == line.length() ) {
			process_word(docId,currentWord,wordPos);
			break;
		}

		if( isspace(line.at(i))  ){

			if( docId == notSet ){
				if( ! is_word(currentWord) ) {
					docId = atoi(currentWord.c_str());
				}
			}

			if( docId != notSet && is_word(currentWord) ) {
				process_word(docId,currentWord,wordPos);
			}
			currentWord = "";
			wordPos++;
		}else{
			currentWord += tolower(line.at(i));
		}
	}
	return true;
}

bool InvIndex::is_word(string s)
{
	for(int i = 0; i < s.length(); i++){
		if( isdigit(s.at(i)) ){
			return false;
		}
	}
	return true;
}

bool InvIndex::process_word(int docId, string word, int wordPos)
{
	int notIndexed = -1;
	int wordIndex = is_indexed(word);

	if( wordIndex == notIndexed ){
		Node * n = new Node(docId, wordPos, NULL);
		InvEntry * entry = new InvEntry(word, n);

		// index word
		int i = index_to_insert(word);
		insert_word_at_index(entry,i);

		InvIndexSize++;
	}else{
		// word indexed, append new Node at returned index
		Node * n = new Node(docId, wordPos, NULL);
		entries[wordIndex].add_item(n);
	}
	return true;
}

bool InvIndex::insert_word_at_index(InvEntry* entry, int i)
{
	InvEntry * tmp = new InvEntry[InvIndexSize];

	// copy over current InvIndex
	for(int j=0; j<InvIndexSize; j++){
		tmp[j]=entries[j];
	}

	// insert new entry
	entries[i] = *entry;

	// shift down entries after the inserted entry
	for(int k=i; k<InvIndexSize; k++) {
		entries[k+1] = tmp[k];
	}

	delete [] tmp;
	return true;
}

int InvIndex::index_to_insert(string word)
{
	for(int i=0; i < InvIndexSize; i++){
		if( word <= entries[i].getWord() ){
			return i;
		}
	}
	return InvIndexSize;
}


// returns index of InvEntry if word is indexed
// otherwise, return -1
int InvIndex::is_indexed(string word)
{
	// binary search
	int listSize = InvIndexSize;
	int notIndexed = -1;

	// set left and right boundary beyond array bounds
	int l = 0;
	int r = listSize-1;

	// stop when l and r converge on the same index
	while(l <= r) {
		// check middle of subarray
		int i = l+((r-l)/2);
		string midArrayWord = entries[i].getWord();

		if( midArrayWord > word ){
			r = i-1;
		}else if( midArrayWord < word ){
			l = i+1;
		}else{
			return i;
		}
	}
	return notIndexed;
}


void InvIndex::save_print_index(char * outputfile)
{
	for(int i = 0; i < InvIndexSize; i++) {
		entries[i].print_entry_to_file(outputfile);
	}

}
