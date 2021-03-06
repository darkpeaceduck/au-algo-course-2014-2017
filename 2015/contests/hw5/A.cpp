
#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define lo int
#define li long long int
#define db double
#define pi 3.14159265358979323
#define eps 1e-6
#define sz(a) (lo)(a).size()
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define DEB(...) fprintf(stderr, __VA_ARGS__)
#define all(a) (a).begin(), (a).end()
using namespace std;

//=====================================================
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
 if(mpos >= MAX_MEM)
	 return malloc(n);
 char *res = mem + mpos;
  mpos += n;
//  assert(mpos <= MAX_MEM);
  return (void *)res;
}
inline void operator delete ( void * ) { }
/** End fast allocation */

inline void * operator new [] ( size_t ) { assert(0); }
inline void operator delete [] ( void * ) { assert(0); }
//===============================================
static const int buf_size = 4096 ;
   inline  int fast_readchar() {
     static char buf[buf_size];
     static int len = 0, pos = 0;
     if (pos == len)
       pos = 0, len = fread(buf, 1, buf_size, stdin);
     if (pos == len)
       return -1;
     return buf[pos++];
   }

   inline  int readUInt() {
     int c = fast_readchar(), x = 0;
     while (c <= 32)
       c = fast_readchar();
     while ('0' <= c && c <= '9')
       x = x * 10 + c - '0', c = fast_readchar();
     return x;
   }

   inline int readInt() {
     int s = 1, c = fast_readchar();
     int x = 0;
     while (c <= 32)
       c = fast_readchar();
     if (c == '-')
       s = -1, c = fast_readchar();
     while ('0' <= c && c <= '9')
       x = x * 10 + c - '0', c = fast_readchar();
     return x * s;
   }

   inline li readLong(){
	   int s = 1, c = fast_readchar();
		li x = 0;
		while (c <= 32)
		  c = fast_readchar();
		if (c == '-')
		  s = -1, c = fast_readchar();
		while ('0' <= c && c <= '9')
		  x = x * 10 + c - '0', c = fast_readchar();
		return x * s;
   }

   inline void readWord( char *s ) {
     int c = fast_readchar();
     while (c <= 32)
       c = fast_readchar();
     while (c > 32)
       *s++ = c, c = fast_readchar();
     *s = 0;
   }

   /** Write */

   static int write_pos = 0;
   static char write_buf[buf_size];

   inline void fast_writechar( int x ) {
     if (write_pos == buf_size)
       fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
     write_buf[write_pos++] = x;
   }

   inline   void fast_flush() {
     if (write_pos)
       fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
   }

   inline void writeInt( int x ) {
     if (x < 0)
       fast_writechar('-'), x = -x;

     char s[24];
     int n = 0;
     while (x || !n)
       s[n++] = '0' + x % 10, x /= 10;
     while (n--)
       fast_writechar(s[n]);
   }

   inline void writeLong( li x ) {
      if (x < 0)
        fast_writechar('-'), x = -x;

      char s[100];
      int n = 0;
      while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
      while (n--)
        fast_writechar(s[n]);
    }

   inline void writeWord( const char *s ) {
     while (*s)
       fast_writechar(*s++);
   }
//=======================
#define MN 101000
#define SM 17
#define INF 2e9
//============================
int p[SM][MN];
int d[MN];
int Sz[MN];
int is_path[MN];
int Index[MN];
int head[MN];
int Count[MN];
int path_counter = 0;
vector<int> g[MN];
vector<vector<int> > segm_tree;


inline int lca(int a, int b) {
  if (d[a] > d[b]) {
   swap(a, b);
  }
  int k = d[b] - d[a];
  for (int i = 0; i < SM; ++i) {
   if (((k >> i) & 1) == 1) {
	   b = p[i][b];
   }
  }
  assert(d[a] == d[b]);
  if (a == b) {
   return a;
  }
  for (int i = SM - 1; i >= 0; --i) {
   if (p[i][a] != p[i][b]) {
	   a = p[i][a];
	   b = p[i][b];
   }
  }
  a = p[0][a];
  b = p[0][b];
  assert(a == b);
  return a;
}

inline void add(int a, int b) {
  d[b] = d[a] + 1;
  p[0][b] = a;
  for (int i = 1; i < SM; ++i) {
   p[i][b] = p[i - 1][p[i - 1][b]];
  }
}

inline void dfs(int id, int fr){
	Sz[id] = 1;
	for(auto to : g[id]){
		if(to == fr)
			continue;
		add(id, to);
		dfs(to, id);
		Sz[id] += Sz[to];
	}
}

inline void make(int id, int fr){
	if(fr == -1 || Sz[id] <= Sz[fr] / 2){
		is_path[id] = path_counter;
		Index[id] = 0;
		head[path_counter++] = id;
	}else{
		is_path[id] = is_path[fr];
		Index[id] = Index[fr] + 1;
	}
	Count[is_path[id]]++;
	for(auto to : g[id]){
		if(to == fr)
			continue;
		make(to, id);
	}
}
///  SEGMENT TREE
inline void inc(int id, int l, int r, int zl, int val, vector<int>&tree){
	if(l == r){
		tree[id] += val;
		return;
	}
	int m = (l + r) / 2;
	if(zl <= m)
		inc(id * 2, l, m, zl, val, tree);
	else
		inc(id * 2 + 1, m + 1, r, zl, val, tree);
	tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
}

inline int geti(int id, int l, int r, int zl, int zr, vector<int> & tree){
	if(zl > zr){
		return 0;
	}
	if(l == zl && r == zr){
		return tree[id];
	}
	int m = (l + r) / 2;
	return max(
			geti(id * 2, l, m, zl, min(zr, m),  tree),
			geti(id * 2 + 1, m + 1, r, max(m + 1, zl), zr, tree)
			);
}

// ========

inline void build(){
   dfs(1, -1);
   make(1, -1);
   segm_tree.resize(path_counter);
   FOR(i, path_counter){
	   segm_tree[i].resize(Count[i] * 4);
   }
}

inline int get_up(int now, int finished){
	int path = is_path[now];
	if(path == is_path[finished]){
		return geti(1, 0, Count[path], Index[finished], Index[now], segm_tree[path]);
	}
	return max(
				geti(1, 0, Count[path], 0, Index[now], segm_tree[path]),
				get_up(p[0][head[path]], finished)
			  );
}

inline int get(int a, int b){
	int lc = lca(a, b);
	return max(get_up(a, lc), get_up(b, lc));
}

inline void query(int a, int val){
	int path = is_path[a];
	inc(1, 0, Count[path], Index[a], val, segm_tree[path]);
}
int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("caves.in", "r", stdin);
    freopen("caves.out", "w", stdout);
#endif
    int n = readInt();
    FOR(i, n - 1){
    	int a= readInt();
    	int b= readInt();
    	g[a].pb(b);
    	g[b].pb(a);
    }
    build();
    int m = readInt();
    FOR(i, m){
    	char c = fast_readchar();
    	int a = readInt();
    	int b = readInt();
    	if(c == 'I'){
    		query(a, b);
    	} else {
    		writeInt(get(a, b));
    		fast_writechar('\n');
    	}
    }
    fast_flush();
};
