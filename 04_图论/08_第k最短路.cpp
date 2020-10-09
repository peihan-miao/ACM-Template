1、给你一个无向图(有向也可)，可以将图中k个路的值变为0，求s->t的最短距离

输入：
//n,m,s,t,k
3 2 1 3 1
1 2 1
2 3 2

int n,m,s,t,k;
bool vis[N];
ll dp[1005][N];
struct edge{
    int v,nx;
    ll w;
}e[M];
int tot,head[N];
void add_edge(int u,int v,ll w){
    e[tot].v=v;e[tot].w=w;e[tot].nx=head[u];
    head[u]=tot++;
}

struct node{
    int u; ll w;
    bool operator<(const node&t)const{
        return w>t.w;
    }
};

void Dijkstra(int st,int ed,int k){
    memset(dp[k],0x3f, sizeof(ll)*(n+1));
    memset(vis,0, sizeof(bool)*(n+1));
    dp[k][st]=0;
    priority_queue<node>q;
    q.push(node{st,0});
    while(!q.empty()){
        node x=q.top();q.pop();
        if(vis[x.u]) continue;
        vis[x.u]=1;
        for(int i=head[x.u];~i;i=e[i].nx){
            int v=e[i].v; ll w=e[i].w;
            if(vis[v]) continue;
            if(k==0){
                if(dp[k][v]>dp[k][x.u]+e[i].w){
                    dp[k][v]=dp[k][x.u]+e[i].w;
                    q.push(node{v,dp[k][v]});
                }
            }else{
                ll len=min(dp[k-1][x.u],dp[k][x.u]+w);
                if(dp[k][v]>len){
                    dp[k][v]=len;
                    q.push(node{v,len});
                }
            }
        }
    }
}

int main(){
    int u,v,w;
    scanf("%d%d%d%d%d",&n,&m,&s,&t,&k);
    tot=0; memset(head,-1, sizeof(int)*(n+1));
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);add_edge(v,u,w);
    }
    for(int i=0;i<=k;i++) Dijkstra(s,t,i);
    ll ret=INF;
    for(int i=0;i<=k;i++) ret=min(ret,dp[i][t]);
    printf("%lld\n",ret);
}