#include <cstdio>
#include <cstring>
#include "FZ_indexer.h"

int main() {
	vector< pair<unsigned, unsigned > > resultsED;	   
	vector< pair<unsigned, double > > resultsJac;

	char dataFilename[]="dblp_sample_data.txt";
	char indexFilename[]="my.index";
	unsigned q=2;
	unsigned tau=3;

	FZ_Indexer indexer;
	indexer.CreateIndex(dataFilename, q, indexFilename); 	
	indexer.LoadIndex(); 
	
	char s[260];
	while (fgets(s, 256, stdin)) {
		while (s[strlen(s) - 1] < ' ') s[strlen(s) - 1] = '\0';
		indexer.SearchED(s, tau, resultsED);
		// indexer.SearchED("Swarzzengaer", 0.8, resultsJac);
		for (unsigned i = 0; i < resultsED.size(); i++) {
			unsigned id = resultsED[i].first;
			unsigned ed = resultsED[i].second;
			printf("%s %u\n", indexer.pattern[id].c_str(), ed);
		}
		resultsED.clear();
	}
	indexer.DestroyIndex(); 
	return 0;
}
