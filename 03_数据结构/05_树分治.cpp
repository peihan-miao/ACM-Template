//多组测试数据，每次输入n、m，和一棵n个点的有边权的树，问你满足x到y距离小于等于m的无序点对(x,y)的个数是多少。
int n,k,head[N],tot;
bool vis[N];
int part[N],cnt[N],root,deep[N],d[N],dtot,sn;
ll ans;
struct node{
    int to,nx,val;
}edge[N*2];

void add_edge(int from,int to,int val){
    edge[tot].to=to;
    edge[tot].val=val;
    edge[tot].nx=head[from];
    head[from]=tot++;
}

//求取重心
void getRoot(int from,int pre){
    cnt[from]=1; part[from]=0;
    for(int i=head[from];i;i=edge[i].nx){
        int to=edge[i].to;
        if(to==pre||vis[to]) continue;
        getRoot(to,from); cnt[from]+=cnt[to];part[from]=max(part[from],cnt[to]);
    }
    part[from]=max(part[from],sn-cnt[from]);
    if(part[root]>part[from]) root=from;
}

//求取树深度
void getDeep(int from,int pre){
    d[++dtot]=deep[from];
    for(int i=head[from];i;i=edge[i].nx){
        int to=edge[i].to;
        if(to==pre||vis[to]) continue;
        deep[to]=deep[from]+edge[i].val;
        getDeep(to,from);
    }
}

//计算答案贡献
ll calc(int from){
    dtot=0; getDeep(from,0);
    sort(d+1,d+1+dtot);
    ll sum=0;
    int i=1,j=dtot;
    while(i<j){
        if(d[i]+d[j]<=k) sum+=j-i,i++;
        else j--;
    }
    return sum;
}

//分治
void Divide(int from){
    deep[from]=0; ans+=calc(from); vis[from]=1;
    for(int i=head[from];i;i=edge[i].nx){
        int to=edge[i].to;
        if(vis[to]) continue;
        deep[to]=edge[i].val; ans-=calc(to); sn=part[to];
        root=0; getRoot(to,0); Divide(root);
    }
}

int main() {
    part[0]=inf;
    int u,v,w;
    while(scanf("%d%d",&n,&k)==2){
        if(n==0&&k==0) break;
        tot=1;
        memset(head,0, sizeof(int)*(n+1));
        memset(vis,0, sizeof(bool)*(n+1));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w); add_edge(v,u,w);
        }
        ans=root=0; sn=n;
        getRoot(1,0); Divide(root);
        printf("%lld\n",ans);
    }
    return 0;
}