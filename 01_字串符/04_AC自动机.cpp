1、查询一个串可以匹配多少个串
int n;
char s[M];

//ac自动机中dif看具体字符串出现的种类数，而N为字符串数*字符串长度
//nx[i][j]表示i节点若下一个字符为j时转向的节点，fail[i]表示i节点失配时指向的节点
//end[i]表示i节点所包含的状态,tot所表示节点范围为[0,tot-1],root=0
class tree {
public:
    int nx[N][dif], fail[N];
    int end[N];
    int root, tot;

    int newNode() {
        for (int i = 0; i < 26; i++)
            nx[tot][i] = -1;
        end[tot] = 0;
        return tot++;
    }

    void init() {
        tot = 0;
        root = newNode();
    }

	//插入字母注意调整
    void insert(char* s) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; i++) {
            int id = s[i] - 'a';
            if (nx[now][id] == -1)
                nx[now][id] = newNode();
            now = nx[now][id];
        }
        end[now]++;
    }

    void build() {
        queue<int>q;
        fail[root] = root;
        for (int i = 0; i < 26; i++) {
            if (nx[root][i] == -1) {
                nx[root][i] = root;
            }
            else {
                fail[nx[root][i]] = root;
                q.push(nx[root][i]);
            }
        }
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            //if (end[fail[now]]) end[now] = 1; 看情况加入
            for (int i = 0; i < 26; i++) {
                if (nx[now][i] == -1) {
                    nx[now][i] = nx[fail[now]][i];
                }
                else {
                    fail[nx[now][i]] = nx[fail[now]][i];
                    q.push(nx[now][i]);
                }
            }
        }
    }
	
	//查询存在
    int query(char* s) {
        int res = 0,len = strlen(s);
        int now = root;
        for (int i = 0; i < len; i++) {
            now = nx[now][s[i] - 'a'];
            int tmp = now;
            while (tmp != root&&end[tmp]!=0) {
                res += end[tmp];
                end[tmp] = 0;
                tmp = fail[tmp];
            }
        }
        return res;
    }
}ac;

int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        ac.init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",s); ac.insert(s);
        }
        ac.build();
        scanf("%s",s);
        printf("%d\n",ac.query(s));
    }
}

2、查询一个字符串中子串出现可重叠子串个数
int query(char s[]) {
   int res = 0;
   int len = strlen(s);
   int now = root;
   for (int i = 0; i < len; i++) {
        now = nx[now][s[i]];
        int tmp = now;
        while (tmp != root) {
              if(end[tmp]) v[end[tmp]]++;
              tmp = fail[tmp];
        }
   }
   return res;
}

3、有m(m<=10)个长度不超过10的只包括AGCT字符串,现在求产生n(n<=1e9)长度的字符串,并且不包括m个字符串,求种类数
通过ac自动机产生关系矩阵.
build函数中要加入：if (end[fail[now]]) end[now] = 1;
void pre_mat() {
	memset(a.arr, 0, sizeof a.arr);
	for (int i = 0; i < tot; i++) {
		if (end[i]) continue;
		for (int j = 0; j < 4; j++) {
			int k = nx[i][j];
			if (!end[k]) a.arr[i][k]++;
		}
    }
}

或当n小的时候使用dp即可实现
int n,m;
char s[N];

class tree {
public:
    int nx[N][2], fail[N];
    int end[N];
    int root, tot;

    int newNode() {
        for (int i = 0; i < 2; i++)
            nx[tot][i] = -1;
        end[tot] = 0;
        return tot++;
    }

    void init() {
        tot = 0;
        root = newNode();
    }

    void insert(char* s) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; i++) {
            int id = s[i]-'0';
            if (nx[now][id] == -1)
                nx[now][id] = newNode();
            now = nx[now][id];
        }
        end[now]=1;
    }

    void build() {
        queue<int>q;
        fail[root] = root;
        for (int i = 0; i < 2; i++) {
            if (nx[root][i] == -1) {
                nx[root][i] = root;
            }
            else {
                fail[nx[root][i]] = root;
                q.push(nx[root][i]);
            }
        }
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if (end[fail[now]]) end[now] = 1;
            for (int i = 0; i < 2; i++) {
                if (nx[now][i] == -1) {
                    nx[now][i] = nx[fail[now]][i];
                }
                else {
                    fail[nx[now][i]] = nx[fail[now]][i];
                    q.push(nx[now][i]);
                }
            }
        }
    }
}ac;

ll dp[50][N];

int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%s",&n,&m,s);
        ac.init();
        ac.insert(s);
        for(int i=0;i<n;i++){
            if(s[i]=='1') s[i]='0';
            else s[i]='1';
            ac.insert(s);
            if(s[i]=='0') s[i]='1';
            else s[i]='0';
        }
        ac.build();
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j < ac.tot; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][0] = 1;
        for(int i=1;i<=m;i++){
            for(int j=0;j<ac.tot;j++){
                if(ac.end[j]) continue;
                for(int k=0;k<2;k++){
                    int x=ac.nx[j][k];
                    if(!ac.end[x]){
                        dp[i][x]+=dp[i-1][j];
                    }
                }
            }
        }
        ll ret=0;
        for(int i=0;i<ac.tot;i++) ret+=dp[m][i];
        printf("%lld\n",pw(m)-ret);
    }
}

4、给出一个文本串和n次查询，每次查询给出一个模式串和相应标记op——若op为0说明查询文本串时模式串允许重叠，若op为
1说明查询时模式串不能重叠。对每次查询，输出当前模式串在文本串中出现的个数。
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
char str[N];
int n;
char s[2][N][8];
int p[2][N];
int cnt, cnt2;
int v[N],len,vis[N];
int l[N];
int vis2[N*10];


class tree {
public:
	int nx[600005][26], fail[600005];
	vector<int>end[600005];
	int root, tot;

	int newNode() {
		for (int i = 0; i < 26; i++)
			nx[tot][i] = -1;
		end[tot].clear();
		vis2[tot] = 0;
		return tot++;
	}

	void init() {
		tot = 0;
		root = newNode();
	}

	void insert(char s[8], int x) {
		int len = strlen(s);
		int now = root;
		for (int i = 0; i < len; i++) {
			int id = s[i]-'a';
			if (nx[now][id] == -1)
				nx[now][id] = newNode();
			now = nx[now][id];
		}
		end[now].push_back(x);
	}

	void build() {
		queue<int>q;
		fail[root] = root;
		for (int i = 0; i < 26; i++) {
			if (nx[root][i] == -1) {
				nx[root][i] = root;
			}
			else {
				fail[nx[root][i]] = root;
				q.push(nx[root][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (nx[now][i] == -1) {
					nx[now][i] = nx[fail[now]][i];
				}
				else {
					fail[nx[now][i]] = nx[fail[now]][i];
					q.push(nx[now][i]);
				}
			}
		}
	}

	void query1() {
		int now = root;
		for (int i = 0; i < len; i++) {
			int id = str[i] - 'a';
			now = nx[now][id];
			int tmp = now;
			while (tmp != root) {
				if (end[tmp].size()) {
					vis2[tmp]++;					
				}
				tmp = fail[tmp];
			}
		}
		for (int i = 0; i < tot; i++) {
			if (vis2[i]) {
				for (int j = 0; j < end[i].size(); j++) {
					v[end[i][j]]+=vis2[i];
				}
			}
		}
	}
	void query2() {
		int now = root; int step = 0;
		for (int i = 0; i < len; i++) {
			int id = str[i] - 'a'; step++;
			now = nx[now][id];
			int tmp = now;
			while (tmp != root) {
				if (end[tmp].size() && (step - vis[tmp]) >= l[end[tmp][0]]) {
					vis[tmp] = step;
					vis2[tmp]++;
				}
				tmp = fail[tmp];
			}
		}
		for (int i = 0; i < tot; i++) {
			if (vis2[i]) {
				for (int j = 0; j < end[i].size(); j++) {
					v[end[i][j]] += vis2[i];
				}
			}
		}
	}
}ac;

int main() {
	int t=1,pos;
	while(scanf("%s",str)==1){
		len = strlen(str);
		cnt = cnt2 = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &pos); v[i] = vis[i] = l[i] = 0;
			if (pos == 0) {
				scanf("%s", s[pos][++cnt]);
				p[pos][cnt] = i;
			}
			else {
				scanf("%s", s[pos][++cnt2]);
				l[i] = strlen(s[pos][cnt2]);
				p[pos][cnt2] = i;
			}
		}
		ac.init();
		for (int i = 1; i <= cnt; i++) 
			ac.insert(s[0][i], p[0][i]);
		ac.build();
		ac.query1();
		ac.init();
		for (int i = 1; i <= cnt2; i++) 
			ac.insert(s[1][i], p[1][i]);
		ac.build();
		ac.query2();
		printf("Case %d\n",t++);
		for (int i = 1; i <= n; i++)
			printf("%d\n", v[i]);
		printf("\n");
	}
}

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 600000+10
#define INF 0x3f3f3f3f
using namespace std;
int ans[MAXN][2];
int node[100000+10];//记录串在Trie中的结束点
int n;
int op[100000+10];
struct Trie
{
    int next[MAXN][26], fail[MAXN];
    int pos[MAXN];//记录当前节点的字符在模式串的位置
    int last[MAXN];//记录当前节点上一个匹配的位置
    int L, root;
    int newnode()
    {
        for(int i = 0; i < 26; i++)
            next[L][i] = -1;
        //End[L++] = 0;
        pos[L++] = 0;//这里忘写了，MLE到死。。。
        return L-1;
    }
    void init()
    {
        L = 0;
        root = newnode();
    }
    void Insert(char *s, int id)
    {
        int now = root;
        for(int i = 0; s[i]; i++)
        {
            if(next[now][s[i]-'a'] == -1)
                next[now][s[i]-'a'] = newnode();
            now = next[now][s[i]-'a'];
            pos[now] = i+1;
        }
        node[id] = now;//记录串结束点
    }
    void Build()
    {
        queue<int> Q;
        fail[root] = root;
        for(int i = 0; i < 26; i++)
        {
            if(next[root][i] == -1)
                next[root][i] = root;
            else
            {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        }
        while(!Q.empty())
        {
            int now = Q.front();
            Q.pop();
            for(int i = 0; i < 26; i++)
            {
                if(next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else
                {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
    }
    void solve(char *s)
    {
        memset(last, -1, sizeof(last));
        memset(ans, 0, sizeof(ans));
        int len = strlen(s);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            now = next[now][s[i]-'a'];
            int temp = now;
            while(temp != root)
            {
                ans[temp][0]++;
                if(i - last[temp] >= pos[temp])
                {
                    ans[temp][1]++;
                    last[temp] = i;
                }
                temp = fail[temp];
            }
        }
    }
};
Trie ac;
char str[100000+10];
char s[10];
int main()
{
    int k = 1;
    while(scanf("%s", str) != EOF)
    {
        ac.init(); scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d%s", &op[i], s);
            ac.Insert(s, i);
        }
        ac.Build(); ac.solve(str);
        printf("Case %d\n", k++);
        for(int i = 0; i < n; i++)
            printf("%d\n", ans[node[i]][op[i]]);
        printf("\n");
    }
    return 0;
}
