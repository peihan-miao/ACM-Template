给定n个点,m条边，请选择一些边，使得1<=i<=d(1<=d<=4),i号节点和n - i + 1号节点可以通过选中的边连通，最小化选中的所有边的权值和。
首先我们设计状态：f[i][j]表示根为i，连通状态为j的最小代价（状态只记录关键点）
有两种转移方法：
枚举子树的形态：f[i][S]=min(f[i][S]，f[i][s]+f[i][t])，其中s和t是对S的一个划分,S=s^t
按照边进行松弛：f[i][S]=min(f[i][S]，f[i′][S]+w[i][i′])，其中i和i′之间有边相连
对于第一种转移，我们直接枚举子集 
对于第二种转移，我们用spfa或dij进行状态转移

//谨慎dij！
int n,m,d;
int head[N],tot;
struct edge{
    int v,w,nx;
}e[N];
void add_edge(int u,int v,int w){
    e[tot].v=v; e[tot].w=w; e[tot].nx=head[u];
    head[u]=tot++;
}

struct node{
    int u; ll w;
    bool operator<(const node&t)const{
        return w>t.w;
    }
};

class SteinerTree{
public:
    ll dp[260][N],g[260]; //1<<8
    bool vis[N];
    priority_queue<node>q;

    void Dijkstra(int S){
        memset(vis,0, sizeof(bool)*(n+1));
        while(!q.empty()){
            node x=q.top();q.pop();
            if(vis[x.u]) continue;
            vis[x.u]=1;
            for(int i=head[x.u];~i;i=e[i].nx){
                int v=e[i].v,w=e[i].w;
                if(dp[S][v]>dp[S][x.u]+w){
                    dp[S][v]=dp[S][x.u]+w;
                    q.push(node{v,dp[S][v]});
                }
            }
        }
    }
    void spfa(int S) {
        while (!q.empty()) {
            int u=q.front(); q.pop();
            in[u]=0;
            for (int i=head[u];~i;i=e[i].nx) {
                int v=e[i].v;
                if (dp[S][v]>dp[S][u]+e[i].w) {
                    dp[S][v]=dp[S][u]+e[i].w;
                    if (!in[v]) in[v]=1,q.push(v);
                }
            }
        }
    }
    void solve(){
        int top=pw(2*d);
        for(int i=0;i<top;i++) memset(dp[i],0x3f, sizeof(ll)*(n+1));
        for(int i=1;i<=d;i++) dp[pw(i-1)][i]=dp[pw(i+d-1)][n-i+1]=0;
        for(int S=1;S<top;S++){
            for (int s=(S-1)&S;s;s=(s-1)&S) {
                int t=S^s;
                for(int i=1;i<=n;i++) dp[S][i]=min(dp[S][i],dp[s][i]+dp[t][i]);
            }
            for(int i=1;i<=n;i++) if(dp[S][i]<INF) q.push(node{i,dp[S][i]});
            Dijkstra(S);
            // for (int i=1;i<=n;i++)
            //     if (dp[S][i]<INF&&!in[i])
            //         q.push(i),in[i]=1;
            // spfa(S);
        }
        memset(g,0x3f, sizeof(g));
        top=pw(d);
        for(int S=1;S<top;S++) {
            for(int i=1;i<=n;i++) g[S]=min(g[S],dp[S^(S<<d)][i]);
            for (int s=(S-1)&S;s;s=(s-1)&S) g[S]=min(g[S],g[s]+g[S^s]);
        }
        printf("%lld",g[(1<<d)-1]==INF? -1:g[(1<<d)-1]);
    }
}steinerTree;


int main(){
    int u,v,w;
    scanf("%d%d%d",&n,&m,&d);
    memset(head,-1, sizeof(int)*(n+1)); tot=0;
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    steinerTree.solve();
}