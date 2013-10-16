#include "FZ_indexer.h"

/*
 * This method creates an index on the strings stored in the given data file name. 
 * The format of the file is as follows: 
	* each line represents a string. 
	* The ID of each string is its line number, starting from 0. 
 * The index is created and  serialized to a file on the disk, and the file name is indexFilename. 
 */
bool FZ_Indexer::CreateIndex(const char * dataFilename, unsigned q, const char * indexFilename) {
	return SUCCESS;
}


/*
 * This method should destroy the index and delete the correspond index file on
 * disk (if any).
 */

bool FZ_Indexer::DestroyIndex() {
	return SUCCESS;
}

/*
 * This method should load the index from the disk into memory. If it's not in memory. 
 * Return an error if the index has not been constructed. 
 */

bool FZ_Indexer::LoadIndex() {
	return SUCCESS;
}

/*
 * It should do a search using the index by finding all the strings in the data
 * file whose edit distance to the query string is within the threshold. The 
 * format of result is a pair of integers which respectively stand for the 
 * qualified string ID and the edit distance between the qualified string and 
 * query string. All results are stored in a vector, sorted based on the 
 * qualified string IDs in an ascending order. Return an error if the index is 
 * not constructed or not loaded in memory.
 */

bool FZ_Indexer::SearchED(const char *query, unsigned threshold, vector< pair<unsigned, unsigned> > &results) {
	return SUCCESS;
}


/*
 * It should do a search using the index by finding all the strings in the data
 * file whose jaccard similarity to the query string is not smaller than the threshold. The 
 * format of result is a pair of number which respectively stand for the 
 * qualified string ID and the jaccard similarity between the qualified string and 
 * query string. All results are stored in a vector, sorted based on the 
 * qualified string IDs in an ascending order. Return an error if the index is 
 * not constructed or not loaded in memory.
 */

bool FZ_Indexer::SearchJaccard(const char *query, double threshold, vector< pair<unsigned, double> > &results) {
	return SUCCESS;
}
