
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
#define all(a) (a).begin(), (a).end()
using namespace std;

//=====================================================
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
  char *res = mem + mpos;
  mpos += n;
  assert(mpos <= MAX_MEM);
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
#define MN 200000
#define SM MN * 4
//=======================
struct node{
	int x;
	node *l, *r;
	node(int _x) : x(_x), l(NULL), r(NULL) {}
};

typedef node * tree;
int get_sum(tree a){
	return a ? a->x : 0;
}
void upd(tree a){
	if(!a)
		return;
	a->x = get_sum(a->l) + get_sum(a->r);
}

void inc(tree &a, int l, int r, int zl, int val){
	if(l == r){
		a->x = val;
		return;
	}
	int m = (l + r) / 2;
	if(zl <= m){
		if(!a->l)
			a->l = new node(0);
		inc(a->l, l, m, zl, val);
	}else{
		if(!a->r)
			a->r = new node(0);
		inc(a->r, m + 1, r, zl, val);
	}
	upd(a);
}
int geti(tree a, int l, int r, int zl, int zr){
	if(!a)
		return 0;
	if(zl > zr)
		return 0;
	if(l == zl && r == zr){
		return a->x;
	}
	int m = (l + r) / 2;
	return geti(a->l, l, m, zl, min(zr, m))+
		   geti(a->r, m + 1, r, max(m+1,zl), zr);
}
//================================

vector<int> Tree[SM];

void build(int id, int l, int r, vector<int> &from){
	if(l == r){
		Tree[id].pb(from[l]);
		return;
	}
	int m = (l + r ) / 2;
	build(id * 2, l , m, from);
	build(id * 2 + 1, m + 1, r, from);
	Tree[id].resize(r - l + 1);
	merge(all(Tree[id * 2]), all(Tree[id * 2 + 1]),
			Tree[id].begin());
}

int get_it(int id, int l, int r , int zl, int zr, int L, int R, int n){
	if(zl  > zr)
		return 0;
	if(l == zl && r == zr){
		return upper_bound(all(Tree[id]), R) -
				lower_bound(all(Tree[id]), L);
	}
	int m = (l + r) / 2;
	return get_it(id * 2, l, m, zl, min(m, zr), L, R, n) +
		   get_it(id * 2 + 1, m + 1, r ,max(m + 1, zl), zr, L, R, n);
}

int main()
{
#ifdef MYLOCAL
    freopen("input.txt", "r", stdin);
 //   freopen("A9.out", "w", stdout);
#else
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
#endif
    int n = readInt();
    int m = readInt();
    vector<int> from(n);
    FOR(i, n){
    	from[i] = readInt();
    }
    build(1, 0, n - 1, from);
    FOR(i, m){
    	int l = readInt(),
			r = readInt(),
			L = readInt(),
			R = readInt();
    	l--; r--;
    	writeInt(get_it(1, 0, n - 1, l, r, L, R, n));
    	fast_writechar('\n');
    }
    fast_flush();
};
