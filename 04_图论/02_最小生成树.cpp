把一个连通无向图的生成树边按权值递增排序，称排好序的边权列表为有序边权列表，则任意两棵最小生成树的有序边权列表是相同的。

1、Prim
//时间复杂度(V+E)logV

struct node{
    int id,w;
    bool operator <(const node&x) const {
        return w>x.w;
    }
};

ll Prim(){
    ll res=0; node x; int cnt=0;
    priority_queue<node>q; q.push(node{1,0});
    while(!q.empty()){
        node y=q.top(); q.pop();
        if(vis[y.id]) continue;
        res+=y.w; vis[y.id]=1; cnt++;
        for(int i=head[y.id];i;i=edge[i].nx){
            int to=edge[i].to,w=edge[i].w;
            if(vis[to]) continue;
            q.push(node{to,w});
        }
    }
    if(cnt==n) return res;
    return -1;
}

2、Kruscal
//时间复杂度ElogE
//将权值从大到小排列可生成最大生成树

int n,m,tot,parent[N];
struct node{
    int from,to,w;
}edge[N];

int find(int x){
    if (x != parent[x]) parent[x] = find(parent[x]);
    return parent[x];
}

bool cmp(node x,node y){
    return x.w<y.w;
}

ll Kruskal(){
    ll res=0;
    for(int i=1;i<=n;i++) parent[i]=i;
    sort(edge+1,edge+1+m,cmp); int cnt=0;
    for(int i=1;i<=m;i++){
        if(cnt==n-1) return res;
        int fx=find(edge[i].from),fy=find(edge[i].to);
        if(fx!=fy){
            parent[fx]=fy;
            res+=edge[i].w;
            cnt++;
        }
    }
    if(cnt!=n-1) return -1;
    else return res;
}

//检验最小生成树唯一性可以使用Kruscal求出所有边，然后将逐一枚举将边去掉，尝试是否能生成最小生成树
ll Kruskal(){
    ll ret=0; int cnt=0; v[0]=0;
    for(int i=1;i<=n;i++) parent[i]=i;
    sort(edge+1,edge+1+m,cmp);
    for(int i=1;i<=m;i++){
        if(cnt==n-1) break;
        int fx=find(edge[i].from),fy=find(edge[i].to);
        if(fx!=fy){
            parent[fx]=fy; cnt++; ret+=edge[i].w; v[++v[0]]=i;
        }
    }
    for(int i=1;i<=v[0];i++){
        ll sum=0; cnt=0;
        for(int j=1;j<=n;j++) parent[j]=j;
        for(int j=1;j<=m;j++){
            if(j==v[i]) continue;
            int fx=find(edge[j].from),fy=find(edge[j].to);
            if(fx!=fy){
                parent[fx]=fy; cnt++; sum+=edge[j].w;
            }
            if(cnt==n-1&&ret==sum) return -1;
            else if(cnt==n-1) break;
        }
    }
    return ret;
}







