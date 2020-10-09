1、割点
在无向连通图中，如果将其中一个点以及所有连接该点的边去掉，图就不再连通，那么这个点就叫做割点

Tarjan算法
	可以使用Tarjan算法求割点（注意，还有一个求连通分量的算法也叫Tarjan算法，与此算法类似）。首先选定一个根节点，从该根节
点开始遍历整个图（使用DFS）。对于根节点，判断是不是割点很简单——计算其子树数量，如果有2棵即以上的子树，就是割点。因为如果
去掉这个点，这两棵子树就不能互相到达。对于非根节点，判断是不是割点就有些麻烦了。我们维护两个数组dfn[]和low[]，dfn[u]表示
顶点u第几个被（首次）访问，low[u]表示顶点u及其子树中的点，通过非父子边（回边），能够回溯到的最早的点（dfn最小）的dfn值（
但不能通过连接u与其父节点的边）。对于边(u, v)，如果low[v]>=dfn[u]，此时u就是割点。但这里也出现一个问题：怎么计算low[u]。
假设当前顶点为u，则默认low[u]=dfn[u]，即最早只能回溯到自身。有一条边(u, v)，如果v未访问过，继续DFS，DFS完之后，low[u]=
min(low[u], low[v])；如果v访问过（且u不是v的父亲），就不需要继续DFS了，一定有dfn[v]<dfn[u]，low[u]=min(low[u], dfn[v])。


代码：
//dfs初始为0,tot=0，head=-1
int n,m,head[N],tot,dfn[N],low[N],dfs,iscut[N];
struct node{
    int v,nx;
}edge[M<<1];

void add_edge(int u,int v){
    edge[tot].v=v;
    edge[tot].nx=head[u];head[u]=tot++;
}

//求出所有割点,id为上一条边
void Tarjan(int u,int id){
    int cnt=0;
    dfn[u]=low[u]=++dfs;
    for(int i=head[u];~i;i=edge[i].nx){
        int v=edge[i].v;
        if(i==(id^1)) continue;
        if(!dfn[v]){
            cnt++; Tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]) iscut[u]=1;
        }else low[u]=min(low[u],dfn[v]);
    }
    if(cnt==1&&id==-1) iscut[u]=0;
}


//求一个图中去掉两个点后的最大连通块数
int n,m,head[N],tot,dfn[N],low[N],dfs,iscut[N];
struct node{
    int v,nx;
}edge[M];

void add_edge(int u,int v){
    edge[tot].v=v;
    edge[tot].nx=head[u];
    head[u]=tot++;
}

//一个点时父节点iscut=0，iscut>0时就是砍掉该点后连通块个数
void Tarjan(int u,int pre,int ban){
    int cnt=0;
    dfn[u]=low[u]=++dfs;
    for(int i=head[u];i;i=edge[i].nx){
        int v=edge[i].v;
        if(v==pre||v==ban) continue;
        if(!dfn[v]){
            cnt++; Tarjan(v,u,ban);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]) iscut[u]++;
        }else low[u]=min(low[u],dfn[v]);
    }
	//if(cnt==1&&pre==-1) iscut[u]=0;
}

int main() {
    int x,y;
    while(scanf("%d%d",&n,&m)==2){
        memset(head,0, sizeof(int)*(n+1)); tot=1;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            add_edge(x,y); add_edge(y,x);
        }
        int ret=0;
        //去掉一个点后，求割点
        for(int j=0;j<n;j++){
            memset(dfn,0, sizeof(int)*(n+1));dfs=0;
            //对节点进行初始化
            for(int i=0;i<n;i++) iscut[i]=1; iscut[j]=0;
            int k=0;
            for(int i=0;i<n;i++){
                if(i==j||dfn[i]) continue;
                iscut[i]=0; k++;
                Tarjan(i,i,j);
            }
            for(int i=0;i<n;i++){
                if(i==j) continue;
                ret=max(ret,k+iscut[i]-1);
            }
        }
        printf("%d\n",ret);
    }
}

2、桥
对于一个无向图，如果删掉一条边后图中的连通分量数增加了，则称这条边为桥或者割边。
	和割点差不多，只要改一处：low[v]>dfn[u]就可以了，而且不需要考虑根节点的问题。
割边是和是不是根节点没关系的，原来我们求割点的时候是指点v是不可能不经过父节点为回到祖先节点（包括父节点），所以顶点u是割点。
如果low[v]==dfn[u]表示还可以回到父节点，如果顶点v不能回到祖先也没有另外一条回到父亲的路，那么u-v这条边就是割边。

//如果图中有重边，且允许两个点形成一个环，则需修改对能否访问父节点的判断，即若当前边指向父节点，但不是从父节点走到当前点的边，
//则可以用父节点的dfn更新当前点的low。
//桥上有防卫，现在要去炸一条桥，使得图不连通，求最少需要的士兵数。
//如果桥上没有防卫也需要一个士兵去炸桥，如果图不连通那么不需要士兵，重边存在则不可能是该边被炸

//dfs初始为0,tot=0，head=-1
int n,m,head[N],tot,dfn[N],low[N],dfs;
int ret;
struct node{
    int v,w,nx;
}edge[M<<1];

void add_edge(int u,int v,int w){
    edge[tot].v=v;edge[tot].w=w;
    edge[tot].nx=head[u];head[u]=tot++;
}

//求出所有割点,id为上一条边
void Tarjan(int u,int id){
    dfn[u]=low[u]=++dfs;
    for(int i=head[u];~i;i=edge[i].nx){
        int v=edge[i].v;
        if(i==(id^1)) continue;
        if(!dfn[v]){
            Tarjan(v,i);
            low[u]=min(low[u],low[v]);
            //或low[v]>dfn[u]
            if(low[v]==dfn[v]) {
                //edge[i]为桥
                ret=min(ret,edge[i].w);
            }
        }else low[u]=min(low[u],dfn[v]);
    }
}

int main() {
    int u,v,w;
    while(scanf("%d%d",&n,&m)==2){
        if(n==0&&m==0) break;
        tot=0;memset(head,-1, sizeof(int)*(n+1));
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w); add_edge(v,u,w);
        }
        int cnt=0;ret=inf;
        memset(dfn,0, sizeof(int)*(n+1)); dfs=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                cnt++; Tarjan(i,-1);
            }
        }
        if(cnt>1){
            printf("0\n");
            continue;
        }
        if(ret==inf){
            printf("-1\n");
            continue;
        }
        printf("%d\n",ret==0?1:ret);
    }
}


3、双联通分量
在一张连通的无向图中，对于两个点u和v，如果无论删去哪条边（只能删去一条）都不能使它们不连通，我们就说u和v边双连通 。
在一张连通的无向图中，对于两个点u和v，如果无论删去哪个点（只能删去一个，且不能删u和v自己）都不能使它们不连通，我们就说u和点双连通 。
边双连通具有传递性，即，若x,y边双连通，y,z边双连通，则x,z边双连通。点双连通不具有传递性.
求解点双连通分量与边双连通分量其实和求解割点与桥密切相关。不同双连通分量最多只有一个公共点，即某一个割点，任意一个割点都是至少两个
点双连通的公共点。不同边双连通分量没有公共点，而桥不在任何一个边双连通分量中，点双连通分量一定是一个边双连通分量。 

怎么判断一个双连通分量中环的个数呢？根据点数跟边数的关系
1.当点数=边数，形成一个环
2.当点数>边数（一条线段，说明这条边是桥）
3.当点数<边数，那么就含1个以上的环了

int co,color[N];
//co初始化为0,颜色相同则说明是属于同一个双联通分量之中，注意根节点为0,若其他点也为0，则说明改点也属于根节点双联通分量中

//边双联通分量
//如何将一个图补成边双联通分量，将图中已有双联通分量合并，然后形成一棵树，统计所以度为1的节点，那么最小值为(leaf+1)/2


void Tarjan(int u,int id,int cnt){
    low[u]=dfn[u]=++dfs;
    bcc[u]=cnt; st.push(u);
    for(int i=head[u];~i;i=edge[i].nx){
        int v=edge[i].v;
        if(id==(i^1)) continue;
        if(!dfn[v]) {
            Tarjan(v, i,cnt);
            low[u] = min(low[u],low[v]);
        }else low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u]){
        blocks++;
        int curr;
        do{
            curr=st.top();
            st.pop();
            ebc[curr]=blocks;
        }while(curr!=u);
    }
}


//一个无向连通图中，每个点都有值，现在求去掉一个桥后，得到的两个连通图价值和之差最小
void Tarjan(int u,int id){
    dfn[u]=low[u]=++dfs;
    st.push(u);
    for(int i=head[u];~i;i=edge[i].nx){
        int v=edge[i].v;
        if(id==(i^1)) continue;
        if(!dfn[v]){
            Tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(low[v]==dfn[v]){
                int cnt=0,x;
                do{
                    x=st.top();st.pop();cnt+=a[x];
                }while(x!=v);
                ret=min(ret,abs(sum-2*cnt));
                a[u]+=cnt;
            }
        }else low[u]=min(low[u],dfn[v]);
    }
}

//blocks=0,ebc表示第i个点属于哪一个双联通分量
//instack去除不知道会不会有事
stack<int>st;
int blocks,ebc[N];
int instack[N];

void Tarjan(int u,int id){
    low[u]=dfn[u]=++dfs;
    st.push(u);
    instack[u]=1;
    for(int i=head[u];~i;i=edge[i].nx){
        int v=edge[i].v;
        if(id==(i^1)) continue;
        if(!dfn[v]) {
            Tarjan(v, i);
            low[u] = min(low[u],low[v]);
        }else if(instack[v]&&dfn[v]<dfn[u]) low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u]){
        blocks++;
        int curr;
        do{
            curr=st.top();
            st.pop();
            instack[curr]=0;
            ebc[curr]=blocks;
        }while(curr!=u);
    }
}

点双连通分量 BCC
　　对于一个连通图,如果任意两点至少存在两条“点不重复”的路径,则说图是点双连通的（即任意两条边都在一个简单环中）,点双连通的
极大子图称为点双连通分量。 通常来说,如果要求任意两条边在同一个简单环中,那么就是求点-双连通
　　易知每条边属于一个连通分量，且连通分量之间最多有一个公共点，且一定是割点。
   无向连通图中割点一定属于至少两个BCC，非割点只属于一个BCC。
   注意：两个直接连接的点也是bcc,但是单个点不算bcc

//一个公园中有n个景点，景点之间通过无向的道路来连接，如果至少两个环公用一条路，路上的游客就会发生冲突；
//如果一条路不属于任何的环，这条路就没必要修，问，有多少路不必修，有多少路会发生冲突

//bcc存的是点双联通分量中的点，初始化bcc_cnt=-1，bccno为-1
vector<int>bcc[N];
int bcc_cnt,bccno[N];
stack<node>st;

void Tarjan(int u,int id){
    dfn[u]=low[u]=++dfs;
    for(int i=head[u];~i;i=edge[i].nx){
        int v=edge[i].v;
        if(id==(i^1)) continue;
        if(!dfn[v]){
            st.push(edge[i]);
            Tarjan(v,i);
            low[u]=min(low[u],low[v]);
            //判断桥
            if(low[v]==dfn[v]) ret++;
            int cnt=0;node x;
            //获得点双联通分量
            if(low[v]>=dfn[u]){
                bcc_cnt++; bcc[bcc_cnt].clear();
                do{
                    cnt++;
                    x=st.top(); st.pop();
                    if(bccno[x.u]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u]=bcc_cnt;
                    }
                    if(bccno[x.v]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v]=bcc_cnt;
                    }
                }while(x.u!=u||x.v!=v);
                if(bcc[bcc_cnt].size()<cnt) ret2+=cnt;
            }
        }else if(dfn[v]<dfn[u]){ //加入还没有加入过的边
            st.push(edge[i]);
            low[u]=min(low[u],dfn[v]);
        }
    }
}


