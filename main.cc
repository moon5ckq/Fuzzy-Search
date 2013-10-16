#include "FZ_indexer.h"

int main() {
	vector< pair<unsigned, unsigned > > resultsED;	   
	vector< pair<unsigned, double > > resultsJac;

	char dataFilename[]="1.txt";
	char indexFilename[]="1.index";
	unsigned q=2;
	unsigned tau=3;

	FZ_Indexer indexer;
	indexer.CreateIndex(dataFilename, q, indexFilename); 	
	indexer.LoadIndex(); 
	indexer.SearchED("Swarzzengaer", tau, resultsED);
	// indexer.SearchED("Swarzzengaer", 0.8, resultsJac);

	for (unsigned i = 0; i < resultsED.size(); i++) {
		unsigned id = resultsED[i].first;
		unsigned ed = resultsED[i].second;                                          
	}
	indexer.DestroyIndex(); 
	return 0;
}
