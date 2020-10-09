1、Print Article(hdu 3507)
题意：
    给出N个单词，每个单词有个非负权值Ci，现要将它们分成连续的若干段，每段的代价为此段单词的权值和，还要加一个常数M，
即(∑Ci)^2+M。现在想求出一种最优方案，使得总费用之和最小。

思路：
    斜率dp裸题,n=500000,设dp[i]表示[1,n]的最优结果,显然满足dp[i]=min{dp[k]+sigma(c[k+1],c[i])+M},显然斜率优化即可.

2、Lawrence(hdu2829)
题意:
    给出一条笔直无分叉的铁路上有n个仓库，每个仓库有一个v[i]代表价值,每两个仓库之间算作一段铁路，现在有m次攻击机会，一次攻
击可以炸毁一段铁路;m次攻击后，剩余的总价值为：Σ(v[i]*v[j]),i和j为所有任意两个互相可到达的仓库.现要求选定m段铁路进行攻击炸毁，
然后使得总价值最小.

思路:
    设dp[i][j]是前i个仓库,炸掉j段铁路后,剩余总价值的最小值.(显然,j<i)设w[a][b]表示铁路完好的情况下，从a仓库到b仓库的总价值,
那么,就有:dp[i][j]=min(dp[k][j-1]+w[k+1][i]),j≤k<i; 方程的意义是：炸毁仓库k和仓库k+1之间的那段铁路（即第k段铁路），算出总
价值，枚举k找到最小的.
    那么如何计算w[k+1][i]呢? w[1][i]=w[1][k]+w[k+1][i]+(v[1]+v[2]+…+v[k])×(v[k+1]+v[k+2]+…+v[i])=w[1][k]+w[k+1][i]+
sum[k]×(sum[i]-sum[k]),即w[k+1][i]=w[1][i]-w[1][k]-sum[k]×(sum[i]-sum[k])
    我们把w[k+1][i]的计算式带入状态转移方程得到:dp[i][j]=min{dp[k][j-1]+w[1][i]-w[1][k]-sum[k]×(sum[i]-sum[k])}
那么，对于这个DP，j一个循环、i一个循环、k一个循环，就是O(n3)的时间复杂度;需要斜率优化，优化到O(n2)即可。

3、Cross the Wall(Uvalive 5097)
题意：
    有N个长方形，要穿过一张纸，最多可以在这张纸上剪掉K个长方形，剪掉一个长方形的代价为该长方形的长*宽，现在问所有长方形都通过的
最小代价

思路：
    首先,排除掉那个无用的长方形,无用的长方形指的是h[i]<h[j]且w[i]<[j](h指长,w指宽)接着排序,排序按照长递减,宽递增,那么拥有单调性
后可以列方程了,对于方程dp[i][j]表示最多有i个洞,j个矩形的最优值,因此即使i>1,也可以从1开始遍历.

代码:
sort(p+1,p+1+n,cmp);
int tot=1;
for(int i=2;i<=n;i++){
    if(p[i].w<=p[tot].w) continue;
    p[++tot]=p[i];
}
n=tot;
for(int i=1;i<=n;i++) dp[1][i]=p[1].h*p[i].w;
ll ans=dp[1][n];
m=min(m,n);
for(int k=2;k<=m;k++){
    int tail=0,head=0;
    q[tail++]=0; dp[k][k]=0;
    for(int i=1;i<=n;i++){
        while (tail>1+head&&isOK(k,i,q[head+1],q[head])) head++;
        dp[k][i]=getsum(k,i,q[head]);
        while (tail>1+head&&isOK2(k,i,q[tail-1],q[tail-2])) tail--;
        q[tail++]=i;
    }
    ans=min(ans,dp[k][n]);
}
printf("%lld\n",ans);

4、Picnic Cows(hdu3045)
题意:
    给你一些牛，把它们分成若干组，每一头牛有自己的价值，每一组的牛的个数不少于T，每一组贡献的价值为这一组内的牛与最小
价值牛的差的和，问所有组贡献的价值最小是多少。

思路:
    这题dp方程容易想出dp[i]=dp[k]+sum[i]-sum[k]-(i-k)*a[k+1];(k>=m && i-(k+1)+1>=m)，但是在处理的时候有一定的技巧
int j = i-t+1; if(j<t) continue; while(tail>1+head&&isOK2(j,q[tail-1],q[tail-2])) tail--; q[tail++]=j;

5、Tree Construction(hdu3516)
题意：
    平面上有点,每次只能向上和向右连接,每次连接的长度就是代价,求把n个点连接成一棵树的最小代价
    
思路：
    f[i][j]表示把[i,j]中的点合成一棵树的最小代价,f[i][j]=min{f[i][k]+f[k+1][j]+abs(x[k+1]−x[i])+abs(y[k]−y[j])} 
然后利用四边形不等式进行优化,需要注意的是,这个dp应该先枚举区间长度，初始时s[i][i]=i

6、Post Office(1160)
题意:
     一条高速公路，有N个村庄，每个村庄均有一个唯一的坐标，选择P个村庄建邮局，问怎么选择，才能使每个村庄到其最近邮局的距离
和最小？最后打印这个最小值。

思路：
     dp[i][j]表示有i个邮局,前j个村庄的最优结果,对于dp[i][j]=min{dp[i-1][k]+w[k+1][j]}的情况,对于这种式子可以使用四边形
不等式优化,对于这种情况优化的不等式为in[i-1][j]<=in[i][j]<=in[i][j+1],并且需要逆推,因为in[i][j+1]的存在,所以第二维度从
for(n->i),并且需要注意越界的情况in[i][v+1]=v-1;

代码：
int main() {
    while(scanf("%d%d",&v,&p)==2){
        for(int i=1;i<=v;i++) {
            scanf("%lld",&a[i]);
            s[i]+=s[i-1]+a[i];w[i][i]=0;in[i][i]=i;
        }
        for(int len=2;len<=v;len++){
            for(int i=1;i+len-1<=v;i++){
                int j=i+len-1;
                w[i][j]=INF; int index;
                for(int k=in[i][j-1];k<=in[i+1][j];k++){
                    ll x = a[k]*(2*k-i-j+1)+s[j]+s[i-1]-2*s[k];
                    if(w[i][j]>x){
                        w[i][j]=x; index=k;
                    }
                }
                in[i][j]=index;
            }
        }
        for(int i=1;i<=v;i++) dp[1][i]=w[1][i],in[1][i]=1;
        for(int i=2;i<=p;i++){
            in[i][v+1]=v-1; dp[i][i]=0;
            for(int j=v;j>=i+1;j--){
                dp[i][j]=INF;
                for(int k=in[i-1][j];k<=in[i][j+1];k++){
                    ll x = dp[i-1][k]+w[k+1][j];
                    if(dp[i][j]>=x) dp[i][j]=x,in[i][j]=k;
                }
            }
        }
        printf("%lld\n",dp[p][v]);
    }
}

7、Batch Scheduling(poj1180)
题意：
    N个任务排成一个序列在一台机器上等待完成(顺序不得改变),这N个任务被分成若干批,每批包含相邻的若干任务.从时刻0开始,
这些任务被分批加工,第i个任务单独完成所需的时间是Ti.在每批任务开始前,机器需要启动时间S,而完成这批任务所需的时间是各个任
务需要时间的总和(同一批任务将在同一时刻完成)。每个任务的费用是它的完成时刻乘以一个费用系数Fi。请确定一个分组方案，使得
总费用最小.（1<=N<=10000）

思路:
    S表示启动时间，T[i]是前i个任务的时间和，C[i]是前i个任务的开销和f[i][j]=Min{f[i-1][k]+(S*i+T[j])*(c[j]-c[k])};
看了别人的结题报告,找到了优化到O(n*n)的方法。就是从n往前推。
    sumT[i]表示从i到n的任务所需要的时间总和,sumF[i]表示从i到n的费用系数总和，dp[i]表示对于从i到n的任务安排的最优解。
那么很容易可以得出这样一个简单的DP状态转移方程：(注:数组存储从1到n)
    dp[i]=min{dp[j]+(S+sumT[i]-sumT[j])*sumF[i]{i<j<=n+1}  边界条件 dp[n+1] = 0
    从后往前推效率可以降一维的原因：
    正向思考,在前面的分块情况不清楚的时候是没法决定下一块的开销的,但是反过来,假设前面都没有分块,先算后面的开销,然后.
如果前面要分块，后面的开销就会全部多出来的一个S，将这个S算进当前的分块开销里面，于是倒过来动态成为可能。

8、Best Cow Fences(poj2018)
题意:
    给定一个非负序列，求长度大于F的连续子序列的平均数最大.

思路:
    在实数上二分平均数mid，判断a中是否有长度大于F平均数大于等于mid，再进行调整二分区间设定一个b数组，b[i]=a[i]-mid
当b[i]的区间和大于等于0的时候说明区间平均数大于等于mid,用sum数组表示b数组前缀和,再求出长度大于等于F的所有区间中的最大
区间和=前缀和-前面的最小前缀和(要保证区间长度大于F),判读和是否大于等于0
    第二个方式可以通过斜率优化找最优值,可以画图分析可得

代码:
bool isOK(double x){
    for(int i=1;i<=n;i++) s[i]=s[i-1]+cow[i]-x;
    double minn = inf;
    for(int i=f;i<=n;i++){
        minn=min(minn,s[i-f]);
        if(s[i]-minn>=0) return true;
    }
    return false;
}