概念：
2-SAT，简单的说就是给出n个集合，每个集合有两个元素，已知若干个<a,b>，表示a与b矛盾（其中a与b属于不同的集合）。
然后从每个集合选择一个元素，判断能否一共选n个两两不矛盾的元素。显然可能有多种选择方案，一般题中只需要求出一种即可。

1、tarjan
假设有a1,a2和b1,b2两对，已知a1和b2间有矛盾，于是为了方案自洽，由于两者中必须选一个，所以我们就要拉两条有向边(a1,b1)和(b2,a2)表示选了a1则必须选b1，
选了b2则必须选a2才能够自洽。然后通过这样子建边我们跑一遍Tarjan SCC判断是否有一个集合中的两个元素在同一个SCC中，若有则输出不可能，否则输出方案。
构造方案只需要把几个不矛盾的 SCC 拼起来就好了。

寻求一组可行解：
当x所在的强连通分量的拓扑序在x'所在的强连通分量的拓扑序之后取x为真就可以了。在使用Tarjan算法缩点找强连通分量的过程中，已经为每组强连通分量标记好
顺序了——不过是反着的拓扑序。

2、爆搜模板,可以求字典序可行最优解
struct Twosat {
    int n;
    vector<int> g[N * 2];
    bool mark[N * 2];
    int s[N * 2], c;
    bool dfs(int x) {
        if (mark[x ^ 1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        s[c++] = x;
        for (int i = 0; i < (int)g[x].size(); i++)
            if (!dfs(g[x][i])) return false;
        return true;
    }
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n * 2; i++) g[i].clear();
        memset(mark, 0, sizeof(mark));
    }
    void add_clause(int x, int y) {  // 这个函数随题意变化
        g[x].push_back(y ^ 1);         // 选了 x 就必须选 y^1
        g[y].push_back(x ^ 1);
    }
    bool solve() {
        for (int i = 0; i < n * 2; i += 2)
            if (!mark[i] && !mark[i + 1]) {
                c = 0;
                if (!dfs(i)) {
                    while (c > 0) mark[s[--c]] = false;
                    if (!dfs(i + 1)) return false;
                }
            }
        return true;
    }
}sat;

int main() {
    int x,y;
    while(scanf("%d%d",&n,&m)==2){
        sat.init(n);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            x--;y--;
            sat.add_clause(x,y);
        }
        if(sat.solve()){
            for(int i=0;i<2*n;i++){
                if(sat.mark[i]) printf("%d\n",i+1);
            }
        }else printf("NIE\n");
    }
}

建模情况：

1、(A,B)不能同时选：选了A就要选B'，选了B就要选A'，所以要建立A->B',B->A'边

2、(A,B)不能同时不取：选择了A'就只能选择B，选择了B'就只能选择A,所以要建立A'->B,B'->A的边
   如要a|b==1,其中a和b为真假状态，那么有三种建边情况
   1）a=b=1|0,那么会建边0->1或1->0
   2）a=1,b=0或a=0,b=1,那么会建边0->0,1->1
   3)上述方法

3、如果存在一个图，图中点需要赋予0或1的值，满足边a op b == c,其中op有and，or，xor
   有六种情况需要讨论：
   1）a and b == 1，则需建边a=0->a=1,b=0->b=1。这里需要体会一下，只需要两条即可
   2）a and b == 0, 则需建边a=1->b=0,b=1->a=0。
   3）a or  b == 1, 则需建边a=0->b=1,b=0->a=1。
   4）a or  b == 0, 则需建边a=1->a=0,b=1->b=0。同1情况
   5）a xor b == 1, 则需建边a=0->b=1,a=1->b=0,b=0->a=1,b=1->a=0。
   6）a xor b == 0, 则需建边a=0->b=0,b=0->a=0,a=1->b=1,b=1->a=1。

4、对于(a,b,c)，若a留下，则b，c回家，若b，c留下，a回家，对于(a,b)若a留下，b回家，若b留下，a回家，对于
   有两种情况需要讨论：
   1）a=1->b=0,c=0 b=1,c=1->a=0
   2) a=0->b=1,b=0->a=1
   
5、有n个集合(a,b)，表示炸弹可放的两个位置，要求将n个炸弹都放置，求最大的半径长度
	二分答案，通过二分的数据进行约束，创建2-sat

6、给出n个牛棚、两个特殊点S1,S2的坐标。S1、S2直连。牛棚只能连S1或S2，还有，某些牛棚只能连在同一个S，某些牛棚不能连在同一个S。
求使最长的牛棚间距离最小，距离是曼哈顿距离，使最大值最小。
	二分答案，用2-sat判断是否可行
	1.hate关系的a,b。   a->b^1,b->a^1,a^1->b,b^1->a
	2.friend关系的a,b。 a->b,b->a,a^1->b^1,b^1->a^1
	接下来的也要检查，因为引入参数，就是多了约束条件了
	这四种情况就是i,j到达对方的所有情况了
	3.dis[a]+dis[b]>limit  a->b^1,b->a^1
	4.dis[a^1]+dis[b^1]>limit a^1->b,b^1->a
	5.dis[a]+dis[b^1]+tdis>limit a->b,b^1->a^1
	6.dis[a^1]+dis[b]+tdis>limit a^1->b^1,b->a

7、两者（A，B）要么都取，要么都不取
    建边：a->b,b->a,a^1->b^1,b^1->a^1

8、两者（A，A’）必取A
	建边：a^1->a
	



















