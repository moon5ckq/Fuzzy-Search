#include "FZ_indexer.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>

//#define debug(format, ...) 
#define debug(format, ...) printf((format), ##__VA_ARGS__)

/*
 * This method creates an index on the strings stored in the given data file name. 
 * The format of the file is as follows: 
	* each line represents a string. 
	* The ID of each string is its line number, starting from 0. 
 * The index is created and  serialized to a file on the disk, and the file name is indexFilename. 
 */
bool FZ_Indexer::CreateIndex(
	const char * dataFilename, unsigned q, const char * indexFilename) {
	this->q = q;
	n = 0;

	FILE *fin = fopen(dataFilename, "r");
	if (fin == NULL) return FAILURE;
	
	while (fgets(data, 10000, fin)) {
		int len = strlen(data);
		while (data[len - 1] < ' ') --len;
		
		//Edit Distance
		pattern.push_back(string(data, len));
		for (int i = 0; i <= len - (int)q; ++i) {
			hash[string(data + i, q)].push_back(n);
		}
		if (len < q) hash[string(data, len)].push_back(n);

		//Jaccard
		int c = 0;
		//patterns.push_back(vector<string>());
		for (int i = 0, p = 0; i <= len; ++i)
			if (i == len || data[i] == ' ') {
				if (p != i) {
					string str(data + p, i - p);
					hashStr[str].push_back(n);
					//patterns[n].push_back(str);
					c++;
				}
				p = i + 1;
			}
		patternCounts.push_back(c);

		++n;
	}
	count.resize(n);

	fclose(fin);

	//debug("%d %u\n", n, hash.size());

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
bool FZ_Indexer::SearchED(
	const char *query, unsigned threshold,
	vector< pair<unsigned, unsigned> > &results) {

	//int curr = clock();

	string qstr(query);
	int len = strlen(query);
	memset(&count[0], 0, sizeof(int) * count.size());
	map<string, int> grams;
	for (int i = 0; i <= len - q; ++i)
		if (hash.count(string(query + i, q)))
			grams[string(query + i, q)] ++;
	if (len < q) grams[string(data, len)] ++;
	
	//debug("%d ", clock() - curr);
	//curr = clock();

	for (map<string, int>::iterator i = grams.begin(); i != grams.end(); ++i) {
		const int *list = &hash[i->first][0];
		//vector<int>& list = hash[i->first];
		int n = hash[i->first].size();
		int pre = -1, c = i->second;
		for (int j = 0; j < n; ++j) {
			if (pre != list[j]) {
				pre = list[j];
				c = i->second;
			}
			if (c) {
				count[pre] ++;
				c--;
			}
		}
	}
	//debug("%d ", clock() - curr);
	//curr = clock();
	//int p = 0;
	int tmp = 1 - q - static_cast<int>(threshold) * q;
	int tmp2 = tmp + len;
	for (int i = 0; i < n; ++i)
		if (count[i] >= tmp2 &&
			count[i] >= static_cast<int>(pattern[i].size()) + tmp) {
			//++p;
			int dis = calcEditDis(qstr, pattern[i], threshold);
			if (dis <= threshold) {
				results.push_back(std::make_pair<unsigned, unsigned>(i, dis));
			}
		}
	//debug("%d %d\n", clock() - curr, p);

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
bool FZ_Indexer::SearchJaccard(
	const char *query, double threshold,
	vector< pair<unsigned, double> > &results) {

	int len = strlen(query), c = 0;
	memset(&count[0], 0, sizeof(int) * count.size());

	for (int i = 0, p = 0; i <= len; ++i)
		if (i == len || query[i] == ' ') {
			if (i != p) {
				string str(query + p, i - p);
				const int *list = &hashStr[str][0];
				int m = hashStr[str].size();
				for (int j = 0; j < m; ++j)
					count[list[j]] ++;
				c++;
			}
			p = i + 1;
		}
	//debug("%d\n", n);
	
	int tmp = static_cast<int>(ceil(threshold * c));
	for (int i = 0; i < n; ++i) {
		if (count[i] >= tmp) {
			double j = count[i] /
				static_cast<double>(patternCounts[i] + c - count[i]);
			if (j >= threshold)
				results.push_back(std::make_pair<unsigned, double>(i, j));
		}
	}

	return SUCCESS;
}

int FZ_Indexer::calcEditDis(const string& a, const string& b, int threshold) {
	int n = a.size(), m = b.size();
	//if (a == b) return 0;
	if (std::abs(n - m) > threshold) return threshold + 1;
	const char *x = &a[0] - 1, *y = &b[0] - 1;
	for (int i = 0; i <= m; ++i)
		f[i] = i;
	int *p = f, *q = g;
	for (int i = 1; i <= n; ++i) {
		bool flag = true;
		q[0] = i;
		for (int j = 1; j <= m; ++j) {
			if (p[j] > q[j-1]) q[j] = q[j-1] + 1;
			else q[j] = p[j] + 1;
			if (q[j] > p[j-1] + (x[i] != y[j]))
				q[j] = p[j-1] + (x[i] != y[j]);
			flag &= q[j] > threshold;
		}
		if (flag) return threshold + 1;
		std::swap(p, q);
	}
	return p[m];
}
