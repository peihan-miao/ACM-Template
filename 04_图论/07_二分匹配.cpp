1、匈牙利算法(O(n*m))

二分图最小顶点覆盖 = 二分图最大匹配；
最小覆盖要求用最少的点（Ｘ集合或Ｙ集合的都行）让每条边都至少和其中一个点关联。

DAG图的最小路径覆盖 = 节点数（n）- 最大匹配数；
最小路径覆盖：用尽量少的不相交简单路径覆盖有向无环图Ｇ的所有结点。1~n匹配1~n的最大匹配数。

二分图最大独立集 = 节点数（n）- 最大匹配数；
二分图最大独立集要求从二分图中选出一些点，使这些点两两互不相邻。即没有独立集中任意两点没有边相连

最大匹配数：最大匹配的匹配边的数目

最小点覆盖数：选取最少的点，使任意一条边至少有一个端点被选择

最大独立数：选取最多的点，使任意所选两点均不相连

最小路径覆盖数：对于一个 DAG（有向无环图），选取最少条路径，使得每个顶点属于且仅属于一条路径。路径长可以为 0（即单个点）。

int k,n,m,girl[N];
vector<int>g[N];
bool vis[N];
//n表示男生数，m表示女生数，girl[i]表示i女生搭档的男生
bool Match(int x){
    for(int i=0;i<g[x].size();i++){
        int y=g[x][i];
        if(!vis[y]){
            vis[y]=1;
            if(!girl[y]||Match(girl[y])){
                girl[y]=x; return true;
            }
        }
    }
    return false;
}

void gao(int n,int m){
    int ret=0;
    memset(girl,0, sizeof(int)*(m+1));
    for(int i=1;i<=n;i++){
        memset(vis,0, sizeof(bool)*(m+1));
        if(Match(i)) ret++;
    }
    printf("%d\n",ret);
}
