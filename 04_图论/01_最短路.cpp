1、Dijkstra 
//不能处理负权图，复杂度(V+E)logV
int n,m,tot,head[N];
ll dis[N];
bool vis[N];
struct node{
    int id;
    ll d;
    node(){}
    node(int id,ll d):id(id),d(d){}
    bool operator < (const node& x) const {
        return d>x.d;
    }
};

struct edge{
    int to,nx;
    ll w;
}e[N<<1];

//tot初始化为1
void add_edge(int from,int to,ll w){
    e[tot].to=to; e[tot].w=w;
    e[tot].nx=head[from]; head[from]=tot++;
}

void Dijkstra(int st){
    memset(dis,0x3f, sizeof(ll)*(n+1));
    memset(vis,0, sizeof(bool)*(n+1));
    dis[st]=0;
    priority_queue<node>q;
    node y(st,0);
    q.push(y);
    while(!q.empty()){
        node x=q.top(); q.pop();
        if(vis[x.id]) continue;
        vis[x.id]=1;
        for(int i=head[x.id];i;i=e[i].nx){
            int to=e[i].to,w=e[i].w;
            if(vis[to]) continue;
            if(w+dis[x.id]<dis[to]){
                dis[to]=w+dis[x.id];
                y.d=dis[to]; y.id=to;
                q.push(y);
            }
        }
    }
}

2、Floyd
//可以求任意两个点的最短路，以及输出字典序的路径
int n;
int link[N][N],path[N][N];
int w[N];

void Floyd(int n){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(link[i][k]+link[k][j]+w[k]<link[i][j]){
                    link[i][j]=link[i][k]+link[k][j]+w[k];
                    path[i][j]=path[i][k];
                }else if(link[i][k]+link[k][j]+w[k]==link[i][j]&&path[i][j]>path[i][k]){
                    path[i][j]=path[i][k];
                }
            }
        }
    }
}

int main() {
    int x;
    while(scanf("%d",&n)==1){
        if(n==0) break;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
            scanf("%d",&x);
            if(x==-1) link[i][j]=inf;
            else link[i][j]=x;
            path[i][j]=j;
        }
        for(int i=1;i<=n;i++) scanf("%d",&w[i]);
        Floyd(n);
        int start,endd;
        while(scanf("%d%d",&start,&endd)==2){
            if(start==endd&&start==-1) break;
            printf("From %d to %d :\nPath: ",start,endd);
            int x=start;
            printf("%d",x);
            while(x!=endd){
                printf("-->%d",path[x][endd]);
                x=path[x][endd];
            }
            printf("\nTotal cost : %d\n\n",link[start][endd]);
        }

    }
}

题意：
	有N个城市，然后直接给出这些城市之间的邻接矩阵，矩阵中-1代表那两个城市无道路相连，其他值代表路径长度。
如果一辆汽车经过某个城市，必须要交一定的钱。现在要从a城到b城，花费为路径长度之和，再加上除起点与终点外所
有城市的过路费之和。求最小花费，如果有多条路经符合，则输出字典序最小的路径。

//输入
5
0 3 22 -1 4
3 0 5 -1 -1
22 5 0 9 20
-1 -1 9 0 4
4 -1 20 4 0
5 17 8 3 1
1 3
3 5
2 4
-1 -1
0

//输出
From 1 to 3 :
Path: 1-->5-->4-->3
Total cost : 21

From 3 to 5 :
Path: 3-->4-->5
Total cost : 16

From 2 to 4 :
Path: 2-->1-->5-->4
Total cost : 17

3、spfa
//主要拿来判断负环，负环的概念为环中所有权值和为负数，只需要有个点重复使用次数>n，那么存在负环
bool spfa(int st){
    memset(dis,0x3f, sizeof(ll)*(n+1));
    memset(vis,0, sizeof(bool)*(n+1));
    memset(cnt,0, sizeof(int)*(n+1));
    queue<int>q;
    vis[st]=1;dis[st]=0;q.push(st);cnt[st]++;
    while(!q.empty()){
        int from=q.front();
        q.pop(); vis[from]=0;
        for(int i=head[from];i;i=edge[i].nx){
            int to=edge[i].to;
            if(dis[to]>dis[from]+edge[i].w){
                dis[to]=dis[from]+edge[i].w;
                if(!vis[to]){
                    vis[to]=1;q.push(to); cnt[to]=cnt[from]+1;
                    if(cnt[to]>n) return true;
                }
            }
        }
    }
    return false;
}

//Floyd判负环
bool Floyd(int n){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int t=link[i][k]+link[k][j];
                if(link[i][j]>t)link[i][j]=t;
            }
            if(link[i][i]<0) return true;
        }
    }
    return false;
}







