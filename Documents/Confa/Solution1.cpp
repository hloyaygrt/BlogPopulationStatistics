#include <iostream>
#include <vector>
#include <unordered_set>
// #include "headerShit.cpp"
// #include "Ip.cpp"

using namespace std;

vector<long long> Array;

void Init() {
	Array.clear();
}

int answerQuery(int l, int r) {
	unordered_set<long long> used;
	used.clear();

	for (int i = l; i <= r; i++) {
		used.insert(Array[i]);
	}
	
	return (int)used.size();
}

void pushBackQuery(IP& ip) {
	long long res = 0;
	long long st = 1;

	for (int i = 3; i >= 0; i--)
		res += (long long)ip.data[i] * st, st *= 1000LL;

	Array.push_back(res);
}