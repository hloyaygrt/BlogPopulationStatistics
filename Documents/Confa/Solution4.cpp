#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <deque>
#include <utility>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <iterator>
#include <cstdio>
#include <cstring>
#include <cstdlib>


using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#define f first
#define s second
#define pb push_back
#define mp make_pair

const int maxn = 10000050;
const int inf = 2e9;
const double eps = 1e-8;
const int base = 1073676287;

struct node {
	int key, prior, cnt;
	node * l, * r;
	int sz;
	node() {}
	node ( int _key ) {
		key = _key;
		l = r = NULL;
		prior = ( rand() << 16 ) + rand();
		cnt = 1;
		sz = 1;
	}
};

typedef node * pnode;

int getSize( pnode T ) {
	return T ? T -> sz : 0;
}

void merge( pnode &T, pnode L, pnode R ) {
	if ( !L ) {
		T = R;
		return;
	}
	if ( !R ) {
		T = L;
		return;
	}
	if ( L -> prior > R -> prior ) {
		merge( L -> r, L -> l, R );
		T = L;
		T -> sz = getSize( T -> l ) + getSize( T -> r ) + T -> cnt;
		return;
	}
	merge( R -> l, L, R -> l );
	T = R;
	T -> sz = getSize( T -> l ) + getSize( T -> r ) + T -> cnt;
}

void split( pnode T, int x, pnode &L, pnode &R ) {
	if ( !T ) {
		L = R = NULL;
		return;
	}
	if ( T -> key > x ) {
		split( T -> l, x, L, T -> l );
		R = T;
		R -> sz = getSize( R -> l ) + getSize( R -> r ) + R -> cnt;
		return;
	}
	split( T -> r, x, T -> r, R );
	L = T;
	L -> sz = getSize( L -> l ) + getSize( L -> r ) + L -> cnt;
}

void TreapDelete( pnode T ) {
	if ( T ) {
		TreapDelete( T -> l );
		TreapDelete( T -> r );
		delete T;
	}
}

pnode Tree[4 * maxn + 105];
pnode L;
pnode R;
pnode M;
map < ll, int > compress;
int timer;
int curNum;
int cur[maxn];

void Add( int v ) {
	split( Tree[v], curNum - 1, L, R );
	merge( Tree[v], L, new node( curNum ) );
	merge( Tree[v], Tree[v], R );
}

void Erase ( int v ) {
	if ( !Tree[v] )
		return;
	pnode T = Tree[v];
	while ( T && T -> key != inf )
		T = T -> r;
	if ( T ) {
		--T -> cnt;
		--T -> sz;
	}
	Add( v );
}

void EraseNext ( int v, int tl, int tr, int pos ) {
	Erase( v );
	if ( tl == tr )
		return;
	int mid = ( tl + tr ) >> 1;
	int newV = v << 1;
	if ( pos <= mid ) 
		EraseNext( newV, tl, mid, pos );
	else
		EraseNext( newV + 1, mid + 1, tr, pos );
}

void Insert( int v ) {
	pnode T = Tree[v];
	while ( T && T -> key != inf )
		T = T -> r;
	if ( T ) {
		++T -> cnt;	
		++T -> sz;
	}
	else
		merge( Tree[v], Tree[v], new node( inf ) );
}

void InsertNext ( int v, int tl, int tr, int pos ) {
	Insert( v );
	if ( tl == tr )
		return;
	int mid = ( tl + tr ) >> 1;
	int newV = v << 1;
	if ( pos <= mid )
		InsertNext( newV, tl, mid, pos );
	else
		InsertNext( newV + 1, mid + 1, tr, pos );
}

int FindAns ( int v, int tl, int tr, int l, int r, int cnt ) {
	if ( l > r )
		return 0;
	if ( tl == l && tr == r ) {
		split( Tree[v], cnt, L, R );
		int ans = getSize( R );
		merge( Tree[v], L, R );
		return ans;
	}
	int mid = ( tl + tr ) >> 1;
	int newV = v << 1;
	return FindAns( newV, tl, mid, l, min( mid, r ), cnt ) +
		   FindAns( newV + 1, mid + 1, tr, max( mid + 1, l ), r, cnt );
}

void ClearTree( int v ) {
	if ( Tree[v] ) {
		ClearTree( v << 1 );
		ClearTree( v << 1 | 1 );
		TreapDelete( Tree[v] );
	} 
}

void Init() {
	compress.clear();
	timer = 0;
	curNum = 0;
	ClearTree( 1 );
	TreapDelete( L );
	TreapDelete( R );
}

int answerQuery(int l, int r) {
	int res =  FindAns( 1, 1, maxn, l + 1, r + 1, r + 1 );
	// cerr << res << endl;
	return res;
}

// debug //
void out(pnode v) {
	if (v) {
		out(v->l);
		cout << (v->key) << ' ' << (v->cnt) << endl;
		out(v->r);
	}
}
// fuckup //

void pushBackQuery(IP& ip) {
	ll x = 0LL;
	for ( int j = 3; j >= 0; j-- ) {
		x *= 1000LL;
		x += 1LL * ip.data[j];
	}
	int c;
	if ( compress.find( x ) == compress.end() ) {
		c = timer;
		compress.insert( mp( x, ++timer ) );
	}
	else 
		c = compress[x];
	EraseNext( 1, 1, maxn, cur[c] );
	cur[c] = ++curNum;
	InsertNext( 1, 1, maxn, cur[c] );
	out( Tree[1] ); 
	cout << "===\n";
}