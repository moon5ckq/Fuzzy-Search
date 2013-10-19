#include <cstdio>
#include <cstring>
#include <ctime>
#include "FZ_indexer.h"

int main() {
	vector< pair<unsigned, unsigned > > resultsED;	   
	vector< pair<unsigned, double > > resultsJac;

	char dataFilename[]="author.data";
	char indexFilename[]="my.index";
	unsigned q=6;
	unsigned tau=4;

	FZ_Indexer indexer;
	indexer.CreateIndex(dataFilename, q, indexFilename); 	
	indexer.LoadIndex(); 
	
	char s[260];
	/*while (fgets(s, 256, stdin)) {
		while (s[strlen(s) - 1] < ' ') s[strlen(s) - 1] = '\0';
		indexer.SearchED(s, tau, resultsED);
		// indexer.SearchED("Swarzzengaer", 0.8, resultsJac);
		for (unsigned i = 0; i < resultsED.size(); i++) {
			unsigned id = resultsED[i].first;
			unsigned ed = resultsED[i].second;
			printf("%s %u\n", indexer.pattern[id].c_str(), ed);
		}
		resultsED.clear();
	}*/

	long long totalTime = 0;
	int count = 0;
	freopen("author.data", "r", stdin);
	while (scanf("%s", s) != EOF) {
		if (strlen(s) < 30) continue; 
		++count;
		int startTime = clock();
		indexer.SearchED(s, tau, resultsED);
		totalTime += clock() - startTime;
		resultsED.clear();
		printf("%lld %d, %.6lf\n", totalTime, count, totalTime/(double)(count));
	}

	indexer.DestroyIndex(); 
	return 0;
}
