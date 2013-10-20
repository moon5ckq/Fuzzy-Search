#include <cstdio>
#include <cstring>
#include <ctime>
#include "FZ_indexer.h"

int main() {
	vector< pair<unsigned, unsigned > > resultsED;	   
	vector< pair<unsigned, double > > resultsJac;

	char dataFilename[]="dblp_sample_data.txt"; //"author.data";
	char indexFilename[]="my.index";
	unsigned q=7;
	unsigned tau=4;
	double tauj = 0.501;

	FZ_Indexer indexer;
	indexer.CreateIndex(dataFilename, q, indexFilename); 	
	indexer.LoadIndex(); 
	
	char s[260];
	while (fgets(s, 256, stdin)) {
		while (s[strlen(s) - 1] < ' ') s[strlen(s) - 1] = '\0';
		indexer.SearchED(s, tau, resultsED);
		//indexer.SearchJaccard(s, tauj, resultsJac);
		//for (unsigned i = 0; i < resultsJac.size(); ++i)
		//	printf("%u %lf\n", resultsJac[i].first, resultsJac[i].second);
		for (unsigned i = 0; i < resultsED.size(); i++) {
			unsigned id = resultsED[i].first;
			unsigned ed = resultsED[i].second;
			printf("%s %u\n", indexer.pattern[id].c_str(), ed);
		}
		resultsJac.clear();
		resultsED.clear();
	}

	return 0;

	long long totalTime = 0;
	int count = 0, line = 0;
	freopen(dataFilename, "r", stdin);
	while (scanf("%s", s) != EOF) {
		//if (strlen(s) < 30) continue;
		//line ++;
		//if (line % 1000 != 1) continue;
		
		//++count;
		int startTime = clock();
		//indexer.SearchED(s, tau, resultsED);
		indexer.SearchJaccard(s, tauj, resultsJac);
		totalTime += clock() - startTime;
		for (unsigned i = 0; i < resultsJac.size(); ++i)
			printf("%u %lf\n", resultsJac[i].first, resultsJac[i].second);
		//printf("%u %lld %d, %.6lf\n",
		//	resultsED.size(), totalTime, count, totalTime/(double)(count));
		//for (unsigned i = 0; i < resultsED.size(); ++i)
		//	printf("%u %u\n", resultsED[i].first, resultsED[i].second);
		//puts("");
		resultsED.clear();
		resultsJac.clear();
	}
	fprintf(stderr, "%lf\n", totalTime / (double)CLOCKS_PER_SEC);

	indexer.DestroyIndex(); 
	return 0;
}
