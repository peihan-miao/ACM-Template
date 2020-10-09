#pragma comment(linker, “/STACK:1024000000,1024000000”)
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
#include<sstream>
#include<map>
#include<queue>
#include<set>
#include<bitset>
#include<list>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
#define pw(k) ((1ll)<<(k))
const ull hash1 = 201326611;
const double eps = 1e-8;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const int N = 2e6+10;
const int M = 12;
const int dif = 26;
const double PI = acos(-1.0);
ll Mod(ll x){ return (x%mod+mod)%mod;}
void BinaryBitset(int n) { cout << bitset<sizeof(int) * 4>(n) << endl; }
inline int getBinary(int x){int cnt=0; for(;x;x-=(x & (-x))) cnt++;return cnt;}

int main() {
#ifdef ACM_LOCAL
    freopen("./std.in", "r", stdin);
    //freopen("./std.out","w",stdout);
    auto start = clock();
#endif

#ifdef ACM_LOCAL
    auto end = clock();
    cerr << "Run Time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
#endif
}