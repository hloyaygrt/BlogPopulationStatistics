#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<long long> Array;
vector<vector<int> > dynProg;

void Init() {
	Array.clear();
	dynProg.clear();
}

int answerQuery(int l, int r) {
	return dynProg[l][r];
}

void pushBackQuery(IP& ip) {
	long long res = 0;
	long long st = 1;

	for (int i = 3; i >= 0; i--)
		res += (long long)ip.data[i] * st, st *= 1000LL;

	Array.push_back(res);
	
	unordered_set<long long> used;
	vector<int> curLayer(Array.size(), 0);

	for (int i = Array.size() - 1; i >= 0; i--) {
		used.insert(Array[i]);
		curLayer[i] = used.size();
	}

	dynProg.push_back(curLayer);
}