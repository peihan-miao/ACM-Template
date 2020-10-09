1.Photo Processing(cf 883I)
题意：
    给你n个数，将其进行分组，每组最少k个数，求分组方案中最小的最大值差值，其中差值为一组中max(max-min)的值

思路：
    先将答案进行二分，然后使用dp去处理，设dp[i]表示[1,i]中能否被完整分成满足条件的几段
    
代码：
方法一：通过二分的答案和k值去约束答案，如果dp[i]可行，那么标记dp[i]=1
bool check(int differ){
    memset(dp,0, sizeof(bool)*(n+2));
    int index=1;dp[0]=1;
    for(int i=1;i<=n;i++){
        while(a[i]-a[index]>differ)
            index++;
		    while(i-index+1>=k){
            if(dp[index-1]){
                dp[i]=1;break;
            }
	    index++;
        }
    }
    return dp[n];
}
方法二：last去标记最后一个能似的dp[i]成功的位置，如果dp[n]==n那么说明都可以分段
bool check(int differ){
    int last=0;
    for(int i=k;i<=n;i++){
        int j = dp[i-k];
        if(a[i]-a[j+1]<=differ)
            last=i;
        dp[i]=last;
    }
    return dp[n]==n;
}

2.小D的剧场(https://ac.nowcoder.com/acm/contest/369/A)
题意:
    一串音符，其中对于每三个都有限制，每个位置有49种音符可能，现在让你求总的可能方案数。
    
思路：
    因为每三个才有限制，第三个的方案数只取决于前两个，因此可以列出dp[500][49][49]，dp[i][j][k]表示在i种位置时
第二个位置为j，第三个位置为k的方案数，可列出：dp[t][i][j]=(dp[t][i][j]+dp[t-1][j][k])%mod;

3、最少拦截系统(hdu1257)
题意：
    有n个导弹依次发射，设置的系统第一次可以打任意高度，接下来的高度不能超过上次发射高度，求最少需要几个系统才能
将导弹全部射下。

思路：
    此题其实也不算真正意义上的dp，通过求最大LIS可获得答案，而与之对应的思想是求最大LIS的贪心+二分的方法，这种
方法不能求得最大LIS的真正意义上的值，但是可以求得最大LIS的长度。就是通过这个方法不断更新，加入求得最后答案。因
为每个导弹肯定是去寻找已发射导弹中离他高度最近的导弹，如果没有导弹满足条件，那么就再设一个。从而获得最后答案。

3、Max Sum Plus Plus(hdu1024)
题意：
    给你a[N]数组，(1<=n<=1e6),求k个区间段最大值为多少。
思路：
    设dp[i][j]表示i段区间，j结尾的最大值(j纳入其中)，因此我们可以得到状态转移方程:
dp[i][j]=max{dp[i][j-1],max{dp[i-1][t](i-1<=t<=j-1)}}+a[j].前者因为dp[i][j-1]的值已知，若不增加i，只需要
将a[j]并入最后一个区间即可。后者是还缺一个区间，将a[j]视为独立区间并入其中。但是有2个max显得处理起来极其繁琐，
且(1<=n<=1e6)，因此我们可以设w[i][j]=max{dp[i][t](i<=t<=j)}=max{w[i][j-1],dp[i][j]},从而我们可以将方程化为:
1)dp[i][j]=max{dp[i][j-1],w[i-1][j-1]}+a[j] 2)w[i][j]=max{dp[i][j],w[i][j-1]}  通过观察发现可以使用滚动数
组将其空间大小进行优化，优化结果为: 1)dp[j]=max{dp[j-1],w[t^1][j-1]}+a[j] 2)w[t^1][j]=max{dp[j],w[t^1][j-1]}
针对此数组对于时间的取值上发现，取m段需要n个数，取m-1段需要n-1个数，取m-2段需要n-2个数...因此在取m-(m-i)=i段的时候，
只需要求解n-(m-i)个数组即可

核心代码：
scanf("%d",&n);
for(int i=1;i<=n;i++){
    scanf("%d",&a[i]);
    pre[i]=pre[i-1]+a[i];
    w[0][i]=0;
}
int t=1;
for(int i=1;i<=k;i++){
    dp[i]=w[t][i]=pre[i];
    for(int j=i+1;j<=n+i-k;j++){
        dp[j]=max(dp[j-1],w[t^1][j-1])+a[j];
        w[t][j]=max(dp[j],w[t][j-1]);
    }
    t^=1;
}
printf("%lld\n",w[t^1][n]);

3、Phalanx(hdu2859)
题意：
    给你一个n*n的矩阵,(1<=n<=1000),求该矩阵中最大的对称矩阵，对称先为左下角到右上角。

思路：
    对对称线进行dp,设dp[i][j]表示由(i,j)点为左下角点的最大对称矩阵边长。若dp[i][j]=q,那么显然以(i,j)向上和向右q-1个对应
点都是相同的，因此dp[i][j]的值可以由dp[i-1][j+1]为保证，即(i-1,j+1)构成的为已知内部是对称矩阵，那么只需要扫一遍剩下的对应
点即可。

反思：
    写题目的时候要多思考一下反向，因为出题者为了增加难度经常反向出题。
    
4、Making the Grade(poj3666)
题意：
    给你一个a[n]数组，每次可以对一个位置上的数进行+1或者-1，求最小操作次数使得数组最后成为一个单调不减或者单调不增序列。

思路：
    通过贪心考虑，显然数组的最大值一定会出现在原a[n]数组之中，而a[n]数组最大值为1e9,我们可以通过离散化考虑这个问题，设
dp[i][j]表示到第i个数字的时候，最大值为第j小数字的最小花费费用。得dp[i][j]=min(dp[i-1][k](1<=k<=j))+abs(a[i]-b[j]).
其中b[n]为原数组a[n]重新从小到大排序后的数组，这样可以保证dp[i][j]在最大值为j大小的时候所花费的费用最小。这里使用了离散
化思想。

反思：
    对于数据较为杂乱，难以处理的时候可以将数据进行离散化，从1-n排序上去。
    
5、Jury Compromise(poj1015)
题意：
    有评审员会打出两个值，pi和di(0<=pi,di<=20).现在有n(1<=n<=200)个评审员,要选取m(1<=m<=20),其中要满足Pi=sigma(pi),
Di=sigma(di),要求|Pi-Di|最小，如若有相同则Pi+Di越大越好,并输出方案。

思路:
   最初的想法是设dp[i][j][2],i表示选到第i个评审员，包含i在内共有j个，0表示差和，1表示加和。因为|Pi-Di|不存在最优子结构，
比如前者有10和-10，因为-10的Pi+Di比10的大，选择了-10的，但是当下次遇到-5的时候显然应该取上10的，应该这个方法无法成立。
   换种思路，因为20*20=400，因此极限差值为[-400,400],我们可以将其提升到[0,800]进行背包处理。设state[i][j]:
typedef struct {
    int sum;
    bool vaild;
    int path[M];
}node;
state[i][j]表示有i个评审员时，差和为j的情况。其中sum记录最大值,vaild记录该方案是否存在,path[M]记录到该方法的操作顺序。
接下来的操作和背包一样，最后按照题目要求输出答案即可。

核心代码：
int dp() {
    for (int i = 1; i <= n; i++) {
        int sub = a[i][0] - a[i][1];
        int add = a[i][0] + a[i][1];
        for (int j = m; j >= 1; j--) {
            for (int x = 0; x <= 800; x++) {
                if (state[j - 1][x].vaild&&x + sub >= 0 && x + sub <= 800) {
                    if (state[j - 1][x].sum + add >= state[j][x + sub].sum) {
                        state[j][x + sub].sum = state[j - 1][x].sum + add;
                        state[j][x + sub].vaild = 1;
                        for (int index = 1; index < j; index++)
                            state[j][x + sub].path[index] = state[j - 1][x].path[index];
                        state[j][x + sub].path[j] = i;
                    }
                }
            }
        }
    }
    for (int i = 0; i <= Base; i++) {
        if (state[m][i + Base].vaild || state[m][Base - i].vaild) {
            int sumMax = -1;
            if (state[m][i + Base].vaild)
                sumMax = state[m][i + Base].sum;
            if (state[m][Base - i].vaild&&state[m][Base - i].sum > sumMax)
                return Base - i;
            return Base + i;
        }
    }
}

反思：
    dp要考虑是否存在最优子结构，如果没有最优子结构是行不通的.并且数据量小的时候可以考虑背包。

6、Blank(http://acm.hdu.edu.cn/showproblem.php?pid=6578)
题意：
    现在有n,m(1<=n,m<=100),现在可以填4个数字0,1,2,3.现在有m个要求,即[l,r]区间内只能出现x种数字,n数列组成的方案数

思路：
    设dp[2][N][N][N],表示数字[0,1,2,3]最后一次出现的位置,dp[i][j][k][q]表示排序后i>j>k>q.那么我们可以得到四种转移方程
    dp[0][0][0][0]=1;
    for(int i=1,p = 1; i <= n; i++, p ^= 1){
        for (int j = 0; j <= i; j++)
            for (int k = 0; k <= j; k++)
                for (int q = 0; q <= k; q++)
                    dp[p][j][k][q] = 0;
        for(int j=0;j<i;j++) {
            for (int k = 0; k <= j; k++) {
                for (int q = 0; q <= k; q++) {
                    Mod(dp[p][j][k][q]+=dp[p^1][j][k][q]);
                    Mod(dp[p][i-1][k][q]+=dp[p^1][j][k][q]);
                    Mod(dp[p][i-1][j][q]+=dp[p^1][j][k][q]);
                    Mod(dp[p][i-1][j][k]+=dp[p^1][j][k][q]);
                }
            }
        }
        for(int j=0;j<i;j++){
            for(int k=0;k<=j;k++){
                for(int q=0;q<=k;q++){
                    for(pii t:v[i]){
                        if(1+(j>=t.first)+(k>=t.first)+(q>=t.first)!=t.second)
                            dp[p][j][k][q]=0;
                    }
                }
            }
        }
    }
    ll ans=0;
    for(int i=0,p=n&1;i<n;i++){
        for(int j=0;j<=i;j++){
            for(int k=0;k<=j;k++){
                Mod(ans+=dp[p][i][j][k]);
            }
        }
    }

7、炫酷雪花(https://ac.nowcoder.com/acm/contest/331/H)
题意：
    小希把接下来连续的要做作业的时间分成n个单位，每个单位时间内小希都会受到ai的寒冷值侵袭，她可以选择在任何一些
时间站起来蹦蹦跳跳，以使得这个单位的寒冷值不侵袭她。小希最大能承受的寒冷程度是K，但是她想选择尽可能多的时间做作业，请你帮帮她！
小希受到的寒冷程度即为不蹦蹦跳跳的时间的寒冷值总和。要求输出最最多学习的时间和字典序最小的可行方案
1<=n<=5000,0<=k<=1e15,0<=a<=1e9

思路：
    先进行贪心，从小到大排序得到最多的学习时间。设dp[i][j],表示i~n时间内，最多可以抖动j次的最小时间，那么转移方程为
dp[i][j]=min(dp[i+1][j]+a[i],dp[i+1][j-1])。然后从1->n遍历，设sum为到i位置时寒冷总和，那么存在如下关系：
1、sum+a[i]+dp[i+1][cnt]<=k,则sum+=a[i] 2.sum+a[i]+dp[i+1][cnt]>k,则cnt--





