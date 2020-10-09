LCA:
    在一棵没有环的树上，每个节点肯定有其父亲节点和祖先节点，而最近公共祖先，就是两个节点在这棵树上深度最大的
公共的祖先节点。所以LCA主要是用来处理当两个点仅有唯一一条确定的最短路径时的路径。

1、Tarjan离线算法
    什么是Tarjan(离线)算法呢？顾名思义，就是在一次遍历中把所有询问一次性解决，所以其时间复杂度是𝑂(𝑛+𝑞)。
Tarjan算法的优点在于相对稳定，时间复杂度也比较居中，也很容易理解下面详细介绍一下Tarjan算法的基本思路：
    1）选一个点为根节点，从根节点开始。
    2）遍历该点u所有子节点v，并标记这些子节点v已被访问过。
    3）若是v还有子节点，返回2，否则下一步。
    4）合并v到u上。
    5）寻找与当前点u有询问关系的点v。
    6）若是v已经被访问过了，则可以确认u和v的最近公共祖先为v被合并到的父亲节点a。

代码：
//第一行包含三个正整数 N,M,S，分别表示树的结点个数、询问的个数和树根结点的序号。
//输出m次询问的公共祖先
//使用并查集查询结果，其中子节点必须并到父节点的祖先上
//注意并查集parent需要初始化
int n,m,s,ans[N],parent[N];
int ehead[N],etot;
struct edge{
    int v,nx;
}e[N<<1];

void add_edge(int u,int v){
    e[etot].v=v; e[etot].nx=ehead[u];
    ehead[u]=etot++;
}

int qhead[N],qtot;
struct query{
    int v,id,nx;
}q[N<<1];

void add_query(int u,int v,int id){
    q[qtot].v=v; q[qtot].nx=qhead[u]; q[qtot].id=id;
    qhead[u]=qtot++;
}

bool vis[N];

int find(int x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void Merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        parent[fy]=fx;
    }
}

void Tarjan(int u){
    vis[u]=1;
    for(int i=ehead[u];i;i=e[i].nx){
        int v=e[i].v;
        if(vis[v]) continue;
        Tarjan(v);
        Merge(u,v);
    }
    for(int i=qhead[u];i;i=q[i].nx){
        int v=q[i].v;
        if(vis[v]){
            ans[q[i].id]=find(v);
        }
    }
}

int main() {
    int u,v;
    scanf("%d%d%d",&n,&m,&s);
    etot=qtot=1;
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        add_query(u,v,i); add_query(v,u,i);
    }
    memset(vis,0, sizeof(bool)*(n+1));
    for(int i=1;i<=n;i++) parent[i]=i;
    Tarjan(s);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}

2、树上倍增LCA

const int MAX_DEP = 20;

// 倍增2^k的父亲
int fa[N][MAX_DEP];
int dep[N];

int n,m,s;
int head[N],tot=1;
struct edge{
    int v,nx;
}e[N<<1];

void add_edge(int u,int v){
    e[tot].v=v; e[tot].nx=head[u];
    head[u]=tot++;
}

void lineFa(int u,int v){
    fa[u][0]=v;
    for(int i=1;i<MAX_DEP;i++)
        v=fa[u][i]=fa[v][i-1];
}

void dfs(int u,int pre){
    for(int i=head[u];i;i=e[i].nx){
        int v=e[i].v;
        if(v==pre) continue;
        dep[v]=dep[u]+1;
        lineFa(v,u);
        dfs(v,u);
    }
}

int LCA(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    int hu=dep[u],hv=dep[v];
    int tu=u,tv=v;
    for(int det=hv-hu,i=0;det;det>>=1,i++){
        if(det&1) tv=fa[tv][i];
    }
    if(tu==tv) return tu;
    for(int i=MAX_DEP-1;i>=0;i--){
        if (fa[tu][i] == fa[tv][i]) {
            continue;
        }
        tu = fa[tu][i];
        tv = fa[tv][i];
    }
    return fa[tu][0];
}

int main() {
    int u,v;
    scanf("%d%d%d",&n,&m,&s);
    tot=1;
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    dep[s]=0;
    dfs(s,0);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        printf("%d\n",LCA(u,v));
    }
}

3、st表查询
//注意调用LCA_init初始化
int n,m,rt,head[N],tot;
int dfn[N],pos[N],rmq[N],dno;
struct edge{
    int v,nx;
}e[N<<1];
void add_edge(int u,int v){
    e[tot].v=v; e[tot].nx=head[u];
    head[u]=tot++;
}

struct ST {
    int k2[21], st[21][N], Log[N];
    void init_st(int n) {
        k2[0] = 1;
        for (int i = 1; i <= 20; i++) k2[i] = 2 * k2[i - 1];
        Log[0] = -1; for (int i = 1; i <=n ; i++) Log[i] = Log[i / 2] + 1;
        for (int i = 1; i <= n; i++) st[0][i] = i;
        for (int i = 1; i <= Log[n]; i++) {
            for (int j = 1; j + k2[i] - 1 <= n; j++) {
                st[i][j] = (rmq[st[i - 1][j]]<rmq[st[i - 1][j + k2[i - 1]]]) ?
                           st[i - 1][j]:st[i - 1][j + k2[i - 1]];
            }
        }
    }
    int query_min(int x, int y) {
        int len = log2(y - x + 1);
        return (rmq[st[len][x]]<rmq[st[len][y - k2[len] + 1]]) ?
               st[len][x]:st[len][y - k2[len] + 1];
    }
}st;

void dfs(int u,int pre,int dep){
    dfn[++dno]=u;
    rmq[dno]=dep;
    pos[u]=dno;
    for(int i=head[u];i;i=e[i].nx){
        int v=e[i].v;
        if(v==pre) continue;
        dfs(v,u,dep+1);
        dfn[++dno]=u;
        rmq[dno]=dep;
    }
}

void LCA_init(int root,int n){
    dno=0;
    dfs(root,root,0);
    st.init_st(2*n-1);
}

int LCA(int u,int v){
    int pu=pos[u],pv=pos[v];
    if(pu>pv) swap(pu,pv);
    return dfn[st.query_min(pu,pv)];
}

int main() {
    int u,v;
    scanf("%d%d%d",&n,&m,&rt);
    tot=1; memset(head,0, sizeof(int)*(n+1));
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    LCA_init(rt,n);
    for(int i=1;i<=m;i++) {
        scanf("%d%d", &u, &v);
        printf("%d\n", LCA(u, v));
    }
}

4、朴素查询
while(q--){
    scanf("%d%d",&u,&v);
    u=find(ebc[u]); v=find(ebc[v]);
    if(u==v){
        printf("%d\n",ret);
        continue;
    }
    if(dep[u]<dep[v]) swap(u,v);
    int i=u,j=v;
    while(parent[i]!=parent[j]){
        if(dep[parent[i]]<dep[parent[j]]) swap(i,j);
        ret--; i=find(f[i]);
    }
    printf("%d\n",ret);
    while(parent[u]!=parent[v]){
        if(dep[parent[u]]<dep[parent[v]]) swap(u,v);
        parent[u]=i; u=find(f[u]);
    }
}