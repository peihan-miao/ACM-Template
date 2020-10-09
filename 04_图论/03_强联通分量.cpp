1、tarjan
//初始化dfs=top=cnt=0,tot=1;
//如果多组数据head[N], dfn[N], low[N], Stack[N], color[N]都得初始化
//用来判强联通分量，若存在路径u->v,v->u，那么会归并到一个集合之中
//时间复杂度为O(v+e)
//若将一个图n个点转化为一整个强联通分量，只需要统计整个图出度和入度，答案为其中最大值
int n, m;
int head[N], dfn[N], low[N], Stack[N], color[N];
bool vis[N];
int dfs, tot, top, cnt;

struct node {
    int from, to, nx;
} edge[M];

void add_edge(int from, int to) {
    edge[tot].from = from;
    edge[tot].to = to;
    edge[tot].nx = head[from];
    head[from] = tot++;
}

void Tarjan(int x) {
    dfn[x] = ++dfs; low[x] = dfs;
    vis[x] = 1; Stack[++top] = x;
    for (int i = head[x]; i; i = edge[i].nx) {
        int tmp = edge[i].to;
        if (!dfn[tmp]) {
            Tarjan(tmp); low[x] = min(low[tmp], low[x]);
        } else if (vis[tmp]) low[x] = min(low[x], dfn[tmp]);
    }
    if (dfn[x] == low[x]) {
        vis[x] = 0; color[x] = ++cnt;
        while (Stack[top] != x) {
            color[Stack[top]] = cnt;
            vis[Stack[top--]] = false;
        }
        top--;
    }
}

void gao(){
    //多组注意初始化
    for(int i=1;i<=n;i++){
        if(color[i]==0) Tarjan(i);
    }
    for(int i=1;i<=n;i++) printf("%d ",color[i]);
    //重新建图，进行操作
}

2、kosaraju
//通过两次dfs得到强联通分量，注意要正反建图，初始化tot=tot2=1
//时间复杂度为O(v+e)

int n,m,cnt;
int head[N],head2[N],tot,tot2;
int color[N];
bool vis[N];
struct node{
    int to,nx;
}edge[N],edge2[N];
stack<int>st;

void dfs1(int from){
    vis[from]=1;
    for(int i=head[from];i;i=edge[i].nx){
        int to=edge[i].to;
        if(!vis[to]) dfs1(to);
    }
    st.push(from);
}

void dfs2(int from){
    color[from]=cnt;
    for(int i=head2[from];i;i=edge2[i].nx){
        int to=edge2[i].to;
        if(!color[to]) dfs2(to);
    }
}

void Kosaraju(){
    memset(color,0, sizeof(int)*(n+1));
    memset(vis,0, sizeof(bool)*(n+1)); cnt=0;
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs1(i);
    while(!st.empty()){
        int x=st.top(); st.pop();
        if(!color[x]){
            cnt++;
            dfs2(x);
        }
    }
}


