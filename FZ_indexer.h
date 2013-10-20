/* 
 * The FZ_Indexer class handles the creation, deletion, and loading of an index. All 
 * necessary initialization of the indexer component should take place within the 
 * constructor for the FZ_Indexer class. 
 * */

#pragma once
#include <vector>
#include <utility>
#include <map>
#include <string>
using std::vector;
using std::pair;
using std::map;
using std::string;

const int SUCCESS = 1;
const int FAILURE = 0;
const int MAX_STRING_SIZE = 260;

class FZ_Indexer {
public:
	FZ_Indexer   () {};
	~FZ_Indexer  () {};

	bool CreateIndex(const char * dataFilename, unsigned q, const char * indexFilename); // create an index and store it in a file 

	bool DestroyIndex(); // destroy the index file on disk

	bool LoadIndex(); // Load the index from disk if it's not in memory

	bool SearchED(const char *query, unsigned threshold, vector< pair<unsigned, unsigned> > &results);

	bool SearchJaccard(const char *query, double threshold, vector< pair<unsigned, double> > &results);

	vector<string> pattern;
	vector<int> patternCounts;

private:
	
	//int f[MAX_STRING_SIZE][MAX_STRING_SIZE];
	int f[MAX_STRING_SIZE];
	int g[MAX_STRING_SIZE];

	map<string, vector<int> > hash;
	map<string, vector<int> > hashStr;
	vector<int> count;
	int calcEditDis(const string& a, const string& b, int threshold);
	int q, n;

	char data[MAX_STRING_SIZE * 40];
}; 
