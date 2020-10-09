后缀数组模板
int n,m;
int sa[N],c[N],wa[N],wb[N];
int rk[N],height[N];
//sa[i]表示排名为i的后缀的起始位置的下标，rk[i]表示起始位置的下标为i的后缀的排名
//c[i]表示桶，x[i]是第i个元素的第一关键字,y[i]表示第二关键字排名为i的数，第一关键字的位置
//height[i]为LCP(i,i-1)，1<i<=n，显然height[1]=0;
//设h[i]=height[rk[i]]，同样的，height[i]=h[sa[i]]; 则有h[i]>=h[i-1]-1;

void DA(int *s,int n,int m){
    //如果多组数据,x需要初始化
    for(int i=0;i<=m;i++) c[i]=wa[i]=0;
    int *x=wa,*y=wb;
    for(int i=1;i<=n;i++) ++c[x[i]=s[i]];
    for(int i=2;i<=m;i++) c[i]+=c[i - 1];
    for(int i=n;i>=1;i--) sa[c[x[i]]--] = i;
    for(int k=1;k<=n;k<<=1){
        int p = 0;
        for(int i=n-k+1;i<=n;i++) y[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++p] = sa[i]-k;
        for(int i=0;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) ++c[x[i]];
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
        swap(x,y);
        x[sa[1]]=1;
        p=1;
        for(int i=2;i<=n;i++) x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) ? p : ++p;
        if(p==n) break;
        m=p;
    }
    int k=0;
    for (int i=1; i<=n; ++i) rk[sa[i]]=i;
    for (int i=1; i<=n; ++i) {
        if (rk[i]==1) continue;//第一名height为0
        if (k) --k;//h[i]>=h[i-1]-1;
        int j=sa[rk[i]-1];
        while (j+k<=n && i+k<=n && s[i+k]==s[j+k]) ++k;
        height[rk[i]]=k;//h[i]=height[rk[i]];
    }
}

int main() {
    scanf("%s",s+1);
    int n = strlen(s+1);
    //注意下标从s开始，而不是s+1
    DA(s,n,127);
    for(int i=1;i<=n;i++) printf("%d ",sa[i]);
}

后缀数组dc3:
#include <cstdio>
#include <cstring>
#include <algorithm>
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
using namespace std;
//开三倍空间
const int N = 3000005;
int wa[N], wb[N], wss[N], wv[N], sa[N];
int rnk[N], height[N], s[N];
char str[N];
//sa和rnk实际上是从[0,len]的所有值，而s[len]=0,height正常


int c0(int *r, int a, int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}

int c12(int k, int *r, int a, int b) {
    if (k == 2)
        return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
    return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}

void Rsort(int *r, int *a, int *b, int n, int m) {
    for (int i = 0; i < n; i++) wv[i] = r[a[i]];
    for (int i = 0; i < m; i++) wss[i] = 0;
    for (int i = 0; i < n; i++) wss[wv[i]]++;
    for (int i = 1; i < m; i++) wss[i] += wss[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--wss[wv[i]]] = a[i];
}

void dc3(int *r, int *sa, int n, int m) {
    int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; i++) if (i % 3 != 0) wa[tbc++] = i;
    Rsort(r + 2, wa, wb, tbc, m);
    Rsort(r + 1, wb, wa, tbc, m);
    Rsort(r, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else for (i = 0; i < tbc; i++) san[rn[i]] = i;
    for (i = 0; i < tbc; i++) if (san[i] < tb) wb[ta++] = san[i] * 3;
    if (n % 3 == 1) wb[ta++] = n - 1;
    Rsort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++) sa[p] = wa[i++];
    for (; j < tbc; p++) sa[p] = wb[j++];
}

void calheight(int *r, int *sa, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; i++) rnk[sa[i]] = i;
    for (i = 0; i < n; height[rnk[i++]] = k)
        for (k ? k-- : 0, j = sa[rnk[i] - 1]; r[i + k] == r[j + k]; k++);
}

int main() {
    while (scanf("%s", str) == 1 && str[0] != '.') {
        int len = strlen(str);
        for (int i = 0; i < len; i++)
            s[i] = str[i] - 'a' + 1;
        s[len] = 0;
        dc3(s, sa, len + 1, 105);
        calheight(s, sa, len);
        int aa = len - height[rnk[0]];
        int ans = 1;
        if(len % aa == 0) {
            ans = len / aa;
        }
        printf("%d\n", ans);
    }
    return 0;
}

后缀自动机：
//凡是和后缀自动机相关的数组都必须开2倍
int n;
char s[N];
int sz[N<<1],c[N<<1],rk[N<<1];

class SuffixAutoMaton{
public:
    int last,tot;
    int nx[N<<1][dif],fa[N<<1],len[N<<1];
    void init(){
        last=tot=1;
        fa[1]=len[1]=0;
        memset(nx[1],0, sizeof(nx[1]));
    }
    inline void insert(int c){
        int p=last,np=++tot;
		memset(nx[np],0, sizeof(nx[np]));
        last=np; len[np]=len[p]+1;
        for(;p&&!nx[p][c];p=fa[p]) nx[p][c]=np;
        if(!p) fa[np]=1;
        else{
            int q=nx[p][c];
            if(len[p]+1==len[q]) fa[np]=q;
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                memcpy(nx[nq],nx[q], sizeof(nx[q]));
                fa[nq]=fa[q]; fa[q]=fa[np]=nq;
                for(;nx[p][c]==q;p=fa[p])
                    nx[p][c]=nq;
            }
        }
        sz[np]=1;
    }
	//求出S的所有出现次数不为1的子串的出现次数乘上该子串长度的最大值。
    ll query(){
        ll ans=0;
        for(int i=1;i<=tot;i++) c[len[i]]++;
        for(int i=1;i<=tot;i++) c[i]+=c[i-1];
        for(int i=1;i<=tot;i++) rk[c[len[i]]--]=i;
        for(int i=tot;i>=1;i--){
            int p=rk[i];
            sz[fa[p]]+=sz[p];
            if(sz[p]>1){
               ans=max(ans,(ll)sz[p]*len[p]);
            }
        }
        return ans;
    }
}SAM;

//set优化nx
class SuffixAutoMaton{
public:
    int last,tot;
    set<pii>nx[N<<1];
    int fa[N<<1],len[N<<1];
    ll ret;
    void init(){
        last=tot=1;
        fa[1]=len[1]=0; nx[1].clear(); ret=0;
    }
    inline void insert(int c){
        int p=last,np=++tot;
        nx[np].clear();
        last=np; len[np]=len[p]+1;
        for(;p;p=fa[p]) {
            auto x=nx[p].lower_bound(make_pair(c,0));
            if(x==nx[p].end()||(*x).first!=c){
                nx[p].insert(make_pair(c,np));
            }else break;
        }
        if(!p) fa[np]=1;
        else{
            int q=(*nx[p].lower_bound(make_pair(c,0))).second;
            if(len[p]+1==len[q]) fa[np]=q;
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                nx[nq]=nx[q];
                fa[nq]=fa[q]; fa[q]=fa[np]=nq;
                for(;;p=fa[p]) {
                    auto x=nx[p].lower_bound(make_pair(c,0));
                    if((*x).second!=q){
                        break;
                    }else{
                        nx[p].erase(x);
                        nx[p].insert(make_pair(c,nq));
                    }
                }
            }
        }
    }
}SAM;

//set优化vector
vector<pii>::iterator ite;

class SuffixAutoMaton{
public:
    int last,tot;
    vector<pii>nx[N<<1];
    int fa[N<<1],len[N<<1];
    ll ret;
    void init(){
        last=tot=1;
        fa[1]=len[1]=0; nx[1].clear(); ret=0;
    }

    int isOK(int p,int c){
        for(auto x:nx[p]){
            if(x.first==c) return x.second;
        }
        return 0;
    }

    void Del(int p,int c){
        for(ite=nx[p].begin();ite!=nx[p].end();ite++){
            if((*ite).first==c){
                nx[p].erase(ite);return;
            }
        }
    }

    inline void insert(int c){
        int p=last,np=++tot;
        nx[np].clear();
        last=np; len[np]=len[p]+1;
        for(;!isOK(p,c);p=fa[p]) nx[p].push_back(make_pair(c,np));
        if(!p) fa[np]=1;
        else{
            int q=isOK(p,c);
            if(len[p]+1==len[q]) fa[np]=q;
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                nx[nq]=nx[q];
                fa[nq]=fa[q]; fa[q]=fa[np]=nq;
                for(;isOK(p,c)==q;p=fa[p]) {
                    Del(p,c);
                    nx[p].push_back(make_pair(c,nq));
                }
            }
        }
        ret+=len[np]-len[fa[np]];
    }
}SAM;

//广义后缀自动机

1、直接建立新节点
给定两个字符串，求出在两个字符串中各取出一个子串使得这两个子串相同的方案数。两个方案不同当且仅当这两个子串中有一个位置不同。
//每次加入新字符串需要将last=1,此模板有时候有节点表示完全相同的东西len[fa[i]]==len[i]如果直接进行基数排序会wa SAM能直接基数
//排序代表拓扑序成立的条件是len[i]严格大于len[fa[i]]，（比如ab,abc）因此不能使用基数排序，而是建立fail树进行答案计数。
class SuffixAutoMaton{
public:
    int last,tot;
    int nx[N<<1][dif],fa[N<<1],len[N<<1];
    ll sz[2][N<<1];
    void init(){
        last=tot=1;
        fa[1]=len[1]=0;
        memset(nx[1],0, sizeof(nx[1]));
    }
    inline void insert(int c,int op){
        int p=last,np=++tot;
        memset(nx[np],0,sizeof(nx[np]));
        last=np; len[np]=len[p]+1;
        for(;p&&!nx[p][c];p=fa[p]) nx[p][c]=np;
        if(!p)
            fa[np]=1;
        else{
            int q=nx[p][c];
            if(len[p]+1==len[q]) fa[np]=q;
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                memcpy(nx[nq],nx[q], sizeof(nx[q]));
                fa[nq]=fa[q]; fa[q]=fa[np]=nq;
                for(;nx[p][c]==q;p=fa[p])
                    nx[p][c]=nq;
            }
        }
        sz[op][np]=1;
    }

    int head[N<<1],cnt;
    struct Edge{
        int to,nx;
    }e[N];

    inline void addedge(int a,int b){
        e[cnt]=(Edge){b,head[a]}; head[a]=cnt++;
    }

    ll ret;

    void dfs(int u){
        for(int i=head[u];i;i=e[i].nx){
            int v=e[i].to;
            dfs(v);
            sz[0][u]+=sz[0][v]; sz[1][u]+=sz[1][v];
            ret+=(len[v]-len[u])*sz[0][v]*sz[1][v];
        }
    }

    void query(){
        memset(head,0, sizeof(int)*(tot+1));cnt=1;
        for(int i=2;i<=tot;i++) addedge(fa[i],i);
        ret=0; dfs(1);
        printf("%lld\n",ret);
    }
}SAM;

//若想直接使用基数排序可以在main函数中进行一个小操作
//通过画{ab,abc}可知，节点(2,4)和节点(3,5)其实代表一样的东西，因此直接在main函数将p进行转移
//使得基数排序时不会出错
int main(){
    SAM.init();
    scanf("%s",s);
    n=strlen(s);
    int p=1;
    for(int i=0;i<n;i++)
        SAM.insert(s[i]-'a'),p=SAM.nx[p][s[i]-'a'],SAM.sz[0][p]++;
    SAM.last=p=1;
    scanf("%s",s);
    n=strlen(s);
    for(int i=0;i<n;i++)
        SAM.insert(s[i]-'a'),p=SAM.nx[p][s[i]-'a'],SAM.sz[1][p]++;
    SAM.calc();
}


//选择性建立新节点
class SuffixAutoMaton{
public:
    int last,tot;
    int nx[N<<1][26],fa[N<<1],len[N<<1];
    int sz[2][N<<1],rk[N<<1],c[N<<1];
    void init(){
        last=tot=1;
        fa[1]=len[1]=0;
        memset(nx[1],0, sizeof(nx[1]));
    }
    //新字符串插入时需要提前将last设置为1
    inline void insert(int c){
        int p=last;
        if(nx[p][c]&&len[nx[p][c]]==len[p]+1){
            last=nx[p][c];return;
        }
        int np=++tot;
        memset(nx[tot],0, sizeof(nx[tot]));
        last=np; len[np]=len[p]+1;
        for(;p&&!nx[p][c];p=fa[p]) nx[p][c]=np;
        if(!p) fa[np]=1;
        else{
            int q=nx[p][c];
            if(len[p]+1==len[q]) fa[np]=q;
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                memcpy(nx[nq],nx[q], sizeof(nx[q]));
                fa[nq]=fa[q]; fa[q]=fa[np]=nq;
                for(;nx[p][c]==q;p=fa[p])
                    nx[p][c]=nq;
            }
        }
    }

    void query(){
        ll ret=0;
        for(int i=1;i<=tot;i++) c[len[i]]++;
        for(int i=1;i<=tot;i++) c[i]+=c[i-1];
        for(int i=1;i<=tot;i++) rk[c[len[i]]--]=i;
        for(int i=tot;i>=1;i--){
            int p=rk[i];
            sz[0][fa[p]]+=sz[0][p]; sz[1][fa[p]]+=sz[1][p];
            ret+=(ll)sz[0][p]*sz[1][p]*(len[p]-len[fa[p]]);
        }
        printf("%lld\n",ret);
    }


}SAM;

int main(){
    SAM.init();
    scanf("%s",s);
    int len=strlen(s),p=1;
    for(int i=0;i<len;i++){
        int c=s[i]-'a';SAM.insert(c);
        p=SAM.nx[p][c];SAM.sz[0][p]++;
    }
    SAM.last=p=1;
    scanf("%s",s);
    len=strlen(s);
    for(int i=0;i<len;i++){
        int c=s[i]-'a';SAM.insert(c);
        p=SAM.nx[p][c];SAM.sz[1][p]++;
    }
    SAM.query();
}
