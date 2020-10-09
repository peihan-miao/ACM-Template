int n;
vector<int>e[N];
int min_p,min_part;
int node[N];
//树的重心也叫树的质心。对于一棵树n个节点的无根树，找到一个点，使得把树变成以该点为根的有根
//树时，最大子树的结点数最小。换句话说，删除这个点后最大连通块（一定是树）的结点数最小。
//性质：
//1、树中所有点到某个点的距离和中，到重心的距离和是最小的，如果有两个距离和，他们的距离和一样。
//2、把两棵树通过一条边相连，新的树的重心在原来两棵树重心的连线上。
//3、一棵树添加或者删除一个节点，树的重心最多只移动一条边的位置。
//4、一棵树最多有两个重心，且相邻。

//min_p,min_part是求得重心

void dfs(int from,int pre){
    node[from]=1; int max_part=0;
    for(int i=0;i<e[from].size();i++){
        int to=e[from][i];
        if(pre==to) continue;
        dfs(to,from);
        node[from]+=node[to];
        max_part=max(max_part,node[to]);
    }
    max_part=max(max_part,n-node[from]);
    if(max_part<min_part){
        min_p=from; min_part=max_part;
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
        min_p=0; min_part=inf;
        dfs(1,0);
        printf("%d %d\n",min_p,min_part);
    }
    return 0;
}