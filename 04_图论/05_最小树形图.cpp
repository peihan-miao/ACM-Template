朱刘算法(O(VE))
一、相关定义
定义：设G = (V,E)是一个有向图，它具有下述性质：1、G中不包含有向环；2、存在一个顶点vi，它不是任何弧的终点，而V中的
其它顶点都恰好是唯一的一条弧的终点，则称 G是以vi为根的树形图。
最小树形图就是有向图G = (V, E)中以vi为根的树形图中权值和最小的那一个。
另一种说法：最小树形图，就是给有向带权图一个特殊的点root，求一棵以root为根节点的树使得该树的的总权值最小。
性质：最小树形图基于贪心和缩点的思想。
缩点：将几个点看成一个点，所有连到这几个点的边都视为连到收缩点,所有从这几个点连出的边都视为从收缩点连出

算法概述：
为了求一个图的最小树形图，1、先求出最短弧集合E0；2、如果E0不存在，则图的最小树形图也不存在；3、如果E0存在且不具有环，
则E0就是最小树形图；4、如果E0存在但是存在有向环，则把这个环收缩成一个点u，形成新的图G1，然后对G1继续求其的最小树形图，
直到求到图Gi，如果Gi不具有最小树形图，那么此图不存在最小树形图，如果Gi存在最小树形图，那么逐层展开，就得到了原图的最
小树形图。

模板1：
题意：
	给出n(1<=n<=1000)个点,m(1<=m<=10000)条边，求出最小树形图，并输出根节点，点从0开始
输入：
3 1
0 1 1

4 4
0 1 10
0 2 10
1 3 20
2 3 30

输出：
impossible

40 0

int n,m,pos,pre[N],id[N],vis[N];
//in[i]存最小入边权,pre[v]为该边的起点
ll in[N];
struct node{
    int u,v;
    ll w;
}edge[M];

ll Directed_MST(int root,int V,int E){
    //存最小树形图总权值
    ll ret=0;
    while(1){
        //1.找每个节点的最小入边
        for(int i=0;i<V;i++) in[i]=INF;
        for(int i=0;i<E;i++){
            int u=edge[i].u,v=edge[i].v;
            if(edge[i].w<in[v]&&u!=v){
                in[v]=edge[i].w;
                pre[v]=u;
                //这个点就是实际的起点
                if(root==u) pos=i;
            }
        }
        //判断是否存在最小树形图
        for(int i=0;i<V;i++){
            if(i==root) continue;
            //除了根以外有点没有入边,则根无法到达它说明它是独立的点 一定不能构成树形图
            if(in[i]==INF) return -1;
        }
        //2.找环
        int cnt=0;
        memset(id,-1, sizeof(int)*(n+1));
        memset(vis,-1, sizeof(int)*(n+1));
        in[root]=0;
        for(int i=0;i<V;i++){
            ret+=in[i];
            int v=i;
            while(vis[v]!=i&&id[v]==-1&&v!=root){
                vis[v]=i;
                v=pre[v];
            }
            if(v!=root&&id[v]==-1){
                for(int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
                id[v]=cnt++;
            }
        }
        if(cnt==0) break; //无环则break
        for(int i=0;i<V;i++){
            if(id[i]==-1) id[i]=cnt++;
        }
        ////3.建立新图   缩点,重新标记
        for(int i=0;i<E;i++){
            int u=edge[i].u,v=edge[i].v;
            edge[i].u=id[u]; edge[i].v=id[v];
            if(id[u]!=id[v]){
                edge[i].w-=in[v];
            }
        }
        V=cnt;
        root=id[root];
    }
    return ret;
}

int main() {
    while(scanf("%d%d",&n,&m)==2){
        ll sum=0;
        for(int i=0;i<m;i++){
            scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].w);
            edge[i].u++;edge[i].v++;
            sum+=edge[i].w;
        }
        sum++;
        //增加超级节点0,节点0到其余各个节点的边权相同（此题中边权要大于原图的总边权值）
        for(int i=m;i<n+m;i++){
            edge[i].u=0; edge[i].v=i-m+1; edge[i].w=sum;
        }
        ll ans=Directed_MST(0,n+1,m+n);
        //n+1为总结点数,m+n为总边数
        //ans代表以超级节点0为根的最小树形图的总权值,
        //将ans减去sum,如果差值小于sum,说明节点0的出度只有1,说明原图是连通图
        //如果差值>=sum,那么说明节点0的出度不止为1,说明原图不是连通图
        if(ans==-1||ans-sum>=sum) printf("impossible\n\n");
        else printf("%lld %d\n\n",ans-sum,pos-m);
    }
    return 0;
}

模板2：
题意：
	给定包含n个结点，m条有向边的一个图。试求一棵以结点r为根的最小树形图，并输出最小树形图每条边
的权值之和，如果没有以r为根的最小树形图，输出 -1。

输入：
4 6 1 //n,m,root
1 2 3
1 3 1
4 1 2
4 2 2
3 2 1
3 4 1

输出：
3

int n,m,pos,pre[N],id[N],vis[N],root;
//in[i]存最小入边权,pre[v]为该边的起点
ll in[N];
struct node{
    int u,v,w;
}edge[M];

ll Directed_MST(int root,int V,int E){
    ll ret=0;
    while(1){
        for(int i=1;i<=V;i++) in[i]=INF;
        for(int i=1;i<=E;i++){
            int u=edge[i].u,v=edge[i].v;
            if(edge[i].w<in[v]&&u!=v){
                in[v]=edge[i].w;
                pre[v]=u;
            }
        }
        for(int i=1;i<=V;i++){
            if(root==i) continue;
            if(in[i]==INF) return -1;
        }
        int cnt=0;
        memset(id,-1, sizeof(int)*(n+1));
        memset(vis,-1, sizeof(int)*(n+1));
        in[root]=0;
        for(int i=1;i<=V;i++){
            ret+=in[i];
            int v=i;
            while(vis[v]!=i&&id[v]==-1&&v!=root){
                vis[v]=i;
                v=pre[v];
            }
            if(v!=root&&id[v]==-1){
                id[v]=++cnt;
                for(int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
            }
        }
        if(cnt==0) break; //无环则break
        for(int i=1;i<=V;i++){
            if(id[i]==-1) id[i]=++cnt;
        }
        ////3.建立新图,缩点,重新标记
        for(int i=1;i<=E;i++){
            int u=edge[i].u,v=edge[i].v;
            edge[i].u=id[u]; edge[i].v=id[v];
            if(id[u]!=id[v]){
                edge[i].w-=in[v];
            }
        }
        V=cnt;
        root=id[root];
    }
    return ret;
}

int main(){
    scanf("%d%d%d",&n,&m,&root);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    printf("%lld\n",Directed_MST(root,n,m));
    return 0;
}

