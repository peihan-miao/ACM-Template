1、Computer(hdu 2196)
题意:
    给出一棵树，求离每个节点最远的点的距离.

思路:
    方法一:那么我们来设列dp方程吧，我们思考当前点x的最远点距离是怎么得到的，只有两种情况：1、来自他的子树(红色部分) 2、来自他
的子树以外的树（蓝色部分简称父亲部）。第一种情况的话可以直接自底向上树形dp得到每一个节点的子树的最远点距离。 那么第二种情况就有点难办，
父亲部的最远点距离可以从哪里来呢？有两种情况：1、父亲点fa的父亲部 2、父亲点的子树
    对于第二种情况的话会有一种情况需要考虑，想到这又不大家应该也会发现，父亲部的子树可能包括红色的部分，如果我们冒冒然去继承，
那么就会造成没法继承到蓝色部分的解。怎么办呢，我们需要判断一下，假如fa的最远点路径经过了x，那么我们就不继承他，改为继承fa子树的次远点
距离。
    那么我们可以设列dp方程了，我们设f[i][0]为i节点子树的最远点距离，f[i][1]为i节点子树的次远点距离，设f[i][2]为i节点的父亲部的最远
点距离。那么我们列出dp方程：
    当x不在fa的最远点路径上：f[x][2]=max(f[fa][0],f[fa][2])+dist(x,fa)
    当x在fa的最远点路径上：f[x][2]=max(f[fa][1],f[fa][2])+dist(x,fa)
    
    方法二：先从1为根节点，求得一个树直径上一点p,然后以p为根求一个树直径,确定第二个直接端点p2,那么任意一个点的最远点是max(dis[i],
 dis2[i])即可

代码：
int n,dp[N][3],p[N][2];
vector<pii>e[N];
void dfs(int from,int pre){
    dp[from][0]=dp[from][1]=0;
    for(int i=0;i<e[from].size();i++){
        int to = e[from][i].first,w=e[from][i].second;
        if(pre==to) continue;
        dfs(to,from);
        if(dp[from][0]<dp[to][0]+w){
            dp[from][1]=dp[from][0];
            dp[from][0]=dp[to][0]+w;
            p[from][0]=to;
        }else if(dp[from][1]<dp[to][0]+w){
            dp[from][1]=dp[to][0]+w;
            p[from][1]=to;
        }
    }
}

void dfs2(int from,int pre){
    for(int i=0;i<e[from].size();i++){
        int to = e[from][i].first,w=e[from][i].second;
        if(pre==to) continue;
        if(to!=p[from][0]) dp[to][2]=w+max(dp[from][2],dp[from][0]);
        else dp[to][2]=w+max(dp[from][2],dp[from][1]);
        dfs2(to,from);
    }
}

2、Rebuilding Roads(poj1947)
题意:
    给出一棵树，问现在要得到一颗有p个节点的子树，需要最少减掉几条边？
思路:
    设dp[i][j]表示i为根节点的子树含j个节点最少减少几条边.进行树形dp+背包即可
代码：
void dfs(int from,int pre){
    memset(dp[from],0x3f, sizeof(dp[from])); dp[from][1]=0; node[from]=1;
    for(int i=0;i<e[from].size();i++){
        int to=e[from][i];
        if(pre==to) continue;
        dfs(to,from);
        node[from]+=node[to];dp[from][1]++;
    }
    for(int i=0;i<e[from].size();i++){
        int to=e[from][i];
        if(pre==to) continue;
        for(int j=m;j>=1;j--){
            for(int k=1;k<=node[to]&&j-k>=1;k++){
                dp[from][j]=min(dp[from][j],dp[from][j-k]+dp[to][k]-1);
            }
        }
    }
}

3、Starship Troopers(hdu1011)
题意:
    给出每个房间拥有的BUG数和能得到的能量数，然后给出每个房间的联通图，要到下一个房间必须攻破上一个房间，
每个士兵最多消灭20个BUG，就算不足20个BUG也要安排一个士兵.

思路:
    dp[from][j]=max(dp[from][j],dp[from][j-k]+dp[to][k]),关键在于如何确定一个跟节点一定在背包中的情况.

代码:
void dfs(int from,int pre){
    int r = (p[from].w+19)/20;
    for(int i=m;i>=r;i--) dp[from][i]=p[from].v;
    for(int i=0;i<e[from].size();i++){
        int to = e[from][i];
        if(to==pre) continue;
        dfs(to,from);
        for(int j=m;j>=r;j--){
            for(int k=1;j-k>=r;k++){
                dp[from][j]=max(dp[from][j],dp[from][j-k]+dp[to][k]);
            }
        }
    }
}

4、Find Metal Mineral(hdu 4003)
题意:
    给你一颗有n个节点的树，给出每两个相连节点边的权值（如果你的一个机器人要走这条边花费的能量），再给你k个机器人，问
从s点出发，最少花费多少d能量可以遍历所有的节点。

思路:
    dp[i][j]表示对于以i结点为根结点的子树，放j个机器人所需要的权值和。当j=0时表示放了一个机器人下去，遍历完结点后又
回到i结点了。状态转移方程类似背包,如果最终的状态中以i为根结点的树中有j(j>0)个机器人，那么不可能有别的机器人r到了这棵
树后又跑到别的树中去因为那样的话，一定会比j中的某一个到达i后跑与r相同的路径再回到i，再接着跑它的路径要差(多了一条i回
去的边)这样的话，如果最后以i为根结点的树中没有机器人，那么只可能是派一个机器人下去遍历完后再回来。
    状态转移，使用的“分组背包”思想。使用一维数组的“分组背包”伪代码如下：
for 所有的组i
    for v=V..0
        for 所有的k属于组i
            f[v]=max{f[v],f[v-c[k]]+w[k]}
    对于每个根节点root，有个容量为K的背包,如果它有i个儿子，那么就有i组物品，价值分别为dp[son][0],dp[son][1].....
dp[son][k] ，这些物品的重量分别为0,1,.....k.现在要求从每组里选一个物品（且必须选一个物品）装进root的背包，使得容量
不超过k的情况下价值最大。那么这就是个分组背包的问题了。但是这里有一个问题，就是每组必须选一个物品。对于这个的处理，我
们先将dp[son][0]放进背包，如果该组里有更好的选择，那么就会换掉这个物品，否则的话这个物品就是最好的选择。这样保证每组
必定选了一个。

代码：
void dfs(int from,int pre){
    memset(dp[from],0, sizeof(dp[from]));
    for(int i=0;i<e[from].size();i++){
        int to=e[from][i].first,w=e[from][i].second;
        if(pre==to) continue;
        dfs(to,from);
        for(int j=m;j>=0;j--){
            dp[from][j]+=dp[to][0]+2*w;
            for(int k=1;k<=j;k++)
                dp[from][j]=min(dp[from][j],dp[from][j-k]+dp[to][k]+k*w);
        }
    }
}

5、The Ghost Blows Light(hdu4276)
题意：
    一个有N个节点的树形的地图，知道了每条变经过所需要的时间，现在给出时间T，问能不能在T时间内从1号节点到N节点。
每个节点都有相对应的价值,而且每个价值只能被取一次,问如果可以从1号节点走到n号节点的话，最多可以取到的最大价值为多少。

思路:
    先求出从1号节点到n号节点的最短路，如果花费大于时间T，则直接输出不符合，将最短路上的权值全部赋值为0，在总时间T上
减去最短路的长度，表示最短路已经走过，对其它点进行树形背包求解，需要注意的是如果不是最短路上的边都要走两次，即走过去
还要再走回来,状态转移方程：
    dp[i][j]=max(dp[i][j],dp[i][k]+dp[i][j-2*val-k])
	
6、Fire(poj2152)
题意：
	Z国有N个城市，编号为从1到N。城市之间用高速公路连接，并且每两个城市之间都有唯一一条路径。最近Z国经常发生火灾，所以
政府决定在一些城市修建消防站。在城市K建立消防站要花费W（K）。不同的城市花费不同。如果在城市K没有消防站，则离他最近的
消防站与他的距离不能超过D（K），不同城市的D也不相同。为了省钱，政府希望你能算出修建消防站最小的总花费。

思路：
	dp[i][j]表示以i为根的子树里每个节点都被消防站管理，并且城市i被城市j所建的消防站管理情况下的最小花费。best[i]表示以
i为根的子树的所有节点都被管理时的最小花费，我们的目的就是求出best[1]。而best[i]显然就是dp[i][j]中的最小值（j表示i的所有孩子）
	dis[i]表示以key为中心，城市i到城市key的距离，当距离大于D（key）时，就意味着key不能由i来管理。
	首先dfs到子节点，然后求出以key为中心的所有距离dis，再枚举每个节点i，考虑dp[key][i]，如果dist[i]>d[key]（即key能容忍消防
站到他的最远距离），就将dp[key][i]置为一很大的数（M=1<<30），表示该情况不会被取到。如果能取到，则在此条件下枚举key的孩子，状
态转移方程：dp[key][i]=w[i]+sum(min(best[j],dp[j][i]-w[i]))。即：城市key被城市i管理时，其花费为w[i]与min（各孩子节点的最小花
费，孩子节点j被i管理的最小花费减去i的建设费用）。最后best[key]为dp[key][i]最小的一个。

代码：
int n,w[N],d[N],head[N],tot,best[N],dis[N];
int dp[N][N];
struct node{
    int to,nx,w;
}edge[N<<1];

void add_edge(int from,int to,int val){
    edge[tot].to=to; edge[tot].nx=head[from]; edge[tot].w=val;
    head[from]=tot++;
}

void DFS(int from){
    for(int i=head[from];i;i=edge[i].nx){
        int to=edge[i].to;
        if(dis[to]!=-1) continue;
        dis[to]=dis[from]+edge[i].w; DFS(to);
    }
}

void dfs(int from,int pre){
    for(int i=head[from];i;i=edge[i].nx){
        int to=edge[i].to;
        if(to==pre) continue;
        dfs(to,from);
    }
    memset(dis,-1, sizeof(int)*(n+1));
    dis[from]=0;DFS(from);
    best[from]=inf;
    for(int i=1;i<=n;i++) dp[from][i]=inf;
    for(int i=1;i<=n;i++){
        if(dis[i]<=d[from]){
            dp[from][i]=w[i];
            for(int j=head[from];j;j=edge[j].nx){
                int to=edge[j].to;
                if(to==pre) continue;
                dp[from][i]+=min(best[to],dp[to][i]-w[i]);
            }
            best[from]=min(best[from],dp[from][i]);
        }
    }
}

int main() {
    int t,x,y,z;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&w[i]);
        for(int i=1;i<=n;i++) scanf("%d",&d[i]);
        memset(head,0, sizeof(int)*(n+1)); tot=1;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&x,&y,&z);
            add_edge(x,y,z); add_edge(y,x,z);
        }
        dfs(1,0);
        printf("%d\n",best[1]);
    }
    return 0;
}

7、GeoDefense(hdu4044)
题意：
	地图是一个n个编号为1～n的节点的树，节点1是敌人的基地，其他叶子节点都是你的基地。敌人的基地会源源不断地出来怪兽，
为了防止敌人攻进你的基地，你可以选择造塔。每个节点最多只能造一个塔，且节点i可以有ki种塔供你选择，价钱和攻击力分别为
price_i, power_i，攻击力power_i，效果是让敌人经过这个节点时让敌人的血减少power_i点。那么从敌人的基地到你的任意一个叶
子基地的路径，这条路径上的所有塔的攻击力之和，就是这个基地的抵抗力。敌人的攻击路径是不确定的，为了保护你的所有基地，
你要确定所有基地中抵抗力最低的一个。 你只有数量为m的钱，问最佳方案，可以抵挡敌人的最大血量是多少？也就是，让所有叶子
基地中抵抗力最低的一个的值尽量大，最大是多少？

思路：
	树形dp，dp[u][j]表示到达u点还有j块钱的最大攻击力，那么将j分配给孩子，取孩子的最小值，取分配方案的最大值就行了，
因为每个点都可以建塔，所以更新树形更新完dp[u][j]后再01背包放哪个塔来更新，注意price可以为0

代码：
int n,m;
vector<int>e[N];
int dp[N][M],k[N];
struct node{
    int price,val;
}p[N][505];

void dfs(int from,int pre){
    dp[from][0]=inf;
    for(int i=0;i<e[from].size();i++){
        int to=e[from][i];
        if(to==pre) continue;
        dfs(to,from);
        for(int j=m;j>=0;j--){
            int x=0;
            for(int k=0;k<=j;k++) x=max(x,min(dp[to][k],dp[from][j-k]));
            dp[from][j]=x;
        }
    }
    if(dp[from][0]==inf) dp[from][0]=0;
    for(int i=m;i>=0;i--){
        int x=dp[from][i];
        for(int j=1;j<=k[from];j++){
            if(p[from][j].price<=i){
                x=max(x,dp[from][i-p[from][j].price]+p[from][j].val);
            }
        }
        dp[from][i]=x;
    }
}

int main() {
    int t,u,v;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) e[i].clear();
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            e[u].push_back(v); e[v].push_back(u);
        }
        scanf("%d",&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&k[i]);
            for(int j=1;j<=k[i];j++){
                   scanf("%d%d",&p[i][j].price,&p[i][j].val);
            }
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp[i][j]=0;
        dfs(1,0);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}




