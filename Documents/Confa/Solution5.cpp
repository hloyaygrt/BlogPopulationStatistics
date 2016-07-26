#include <map>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = (int)5e6 + 105;

struct node
{
	int l, r;
	int sum;
	node() {
		l = 0, r = 0, sum = 0;
	}
	node(int l, int r, int sum):l(l), r(r), sum(sum){}
};

node tree[23 * maxn + 1005];
vector<int> roots;
int sz;

int vertCopy(int v) {
	tree[++sz] = tree[v];
	return sz;
}

int makeRoot() {
	if (!roots.empty()) {
		int pos = vertCopy(roots.back());
		roots.push_back(pos);
		return pos;
	} else {
		roots.push_back(++sz);
		return sz;
	}
}

map<long long, int> compress;
map<int, int> findRoot;
int cur[maxn], timer;

void update(int v, int tl, int tr, int pos, int delta) {
	tree[v].sum += delta;
	if (tl == tr)
		return;
	int tm = (tl + tr) >> 1;
	if (pos <= tm)
		update(tree[v].l = vertCopy(tree[v].l), tl, tm, pos, delta);
	else
		update(tree[v].r = vertCopy(tree[v].r), tm + 1, tr, pos, delta);
}

int query(int v, int tl, int tr, int l, int r) {
	// assert
	if (v == 0)
		return 0;
	if (l > r)
		return 0;
	if (tl == l && tr == r)
		return tree[v].sum;

	int tm = (tl + tr) >> 1;
	return query(tree[v].l, tl, tm, l, min(r, tm)) + 
		   query(tree[v].r, tm + 1, tr, max(l, tm + 1), r);
}

void Init() {
    for (int i = 0; i < maxn; i++){
        cur[i] = -1;
    }
    for (int i = 0; i < 23 * maxn + 105; i++)
        tree[i] = node();
	timer = 0;
	roots.clear();
	findRoot.clear();
	sz = 0;
	compress.clear();
}

int answerQuery(int l, int r) {
	return query(findRoot[r], 0, maxn - 1, l, r);
}

void pushBackQuery(IP& ip) {
	long long res = 0;
	long long st = 1;

	for (int i = 3; i >= 0; i--)
		res += (long long)ip.data[i] * st, st *= 1000LL;

	if (!compress.count(res))
		compress[res] = compress.size();

	int x = compress[res];
	if (cur[x] != -1)
		update(makeRoot(), 0, maxn - 1, cur[x], -1);

	int nw = makeRoot();

	findRoot[timer] = nw;
	cur[x] = timer;

	update(nw, 0, maxn - 1, cur[x], 1);
	timer++;
}