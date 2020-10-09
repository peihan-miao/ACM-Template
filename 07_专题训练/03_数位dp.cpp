1、不要62(hdu2089)
题意：
  求出区间[n,m]中数位没有62和4的个数
思路：
  1、设dp[i][j]表示最高i位时,第i为j符合条件的个数。例如dp[5][0]中包含00532。数位dp的精髓就是逐位比较，最终获得答案。
设count(n)记录[0,n)的个数，因此要获得[n,m]中的个数，需要count(m+1)-count(n)。其中dp[i][j]的状态转移方程为：
1)、dp[i][j]=0 (j==4) 2)、dp[i][j]=sigma(dp[i-1][j]) (j=0,1...,9),当j=6时,需要减去dp[i-1][2]
之后就是将数位拆开，挨个去比较比如102,拆出来为201,此时先去保存100以下的数字，之后去保存102以下，100以上的数字。
最终即可获得答案。

代码：
1、
void init(){
     dp[0][0]=1;
     for(int i=1;i<10;i++){
	for(int j=0;j<10;j++){
		if(j==4){
			dp[i][j]=0;
		}else if(j!=6){
			for(int k=0;k<=9;k++)
				dp[i][j]+=dp[i-1][k];
		}else if(j==6){
			for(int k=0;k<=9;k++)
				dp[i][j]+=dp[i-1][k];
			dp[i][j]-=dp[i-1][2];
		}
	  }
      }
}
int v[N+10];
ll solve(int di){
   ll res=0;
   v[0]=0;
   while(di){
	v[++v[0]]=di%10;
	di/=10;
   }
   v[v[0]+1]=0;
   for(int i=v[0];i>=1;i--){
	for(int j=0;j<v[i];j++){
		if(j!=4&&!(j==2&&v[i+1]==6))
			res+=dp[i][j];
	}
	if(v[i]==4)
		break;
	if(v[i]==2&&v[i+1]==6)
		break;
    }
    return res;
}

2、Beautiful numbers(https://codeforces.com/problemset/problem/55/D)
题意:
    一个正整数，如果它能被数位上每个非零数整除，那么这个数为完美数，求区间[n,m]的完美数个数。
    
思路：
    1、如果一个数能被它所有非0数位整除那么这个数一定被lcm{[1,9]}整除。
    2、存在定理a%(x*n)%x=a%x
    3、[1,9]所有的组合的最小公倍数，最大值为2520，共有48个，2520%lcm[任意组合]=0。
    综上关系，我们可以发现我们需要找到所有满足a%(x*n)%x=a%x=0的结果，显然本题中x*n取值为2520，因此我们可
以将数进行拆分，然后逐层搜索，dp记录数据，设dp[20][50][2525],dp[i][j][k]表示在数位i时，经过离散化过的最小
公倍数hash[lcm]=pos，k表示模后取值，因为lcm最大为2520，因此值只需取到2520即可。

核心代码：
ll dfs(int pos, int tot, int lcm, bool limit) { 
   if (pos == 0) //pos表示当前位数,tot表示取模后值,lcm表示当前最小lcm，limit表示是否可以任意取值
	return (tot%lcm == 0);
   if (!limit&&dp[pos][ha[lcm]][tot] != -1)
	return dp[pos][ha[lcm]][tot];
   ll res = 0;
        int top = limit ? di[pos] : 9; //判断当前有限制
   for (int i = 0; i <= top; i++) {
	res += dfs(pos - 1, (tot * 10 + i) % mod, i ? i * lcm / gcd(i, lcm) : lcm, i == di[pos] && limit);
   } //进一步搜索
   if (!limit) //如果没有限制,那么这个情况的值就确定下来了
 	dp[pos][ha[lcm]][tot] = res;
    return res;
}

3、Beautiful numbers(https://ac.nowcoder.com/acm/contest/163/J)
题意：
    给你一个数,若数位上所有的和能整除这个数,那么这个数可以称为美丽数,求[1,n]之中有多少个美丽数,其中1<=n<=1e12
思路:
    因为1e12数位之中最大数位和只有9*12=108,因此我们可以通过我们可以依次循环数位和，然后使用dfs去暴力搜索情况。
如果存在sigma(di)==mod,那么这个数可以成立。并设dp[12][120][120],设dp[i][j][k]表示在i位时候,数位和为j,被mod
余k的数量。

核心代码：
ll dfs(int pos, int tot, int remain, bool limit) {
   if (pos == -1) //只有当数位和与mod相等时,并且正好模掉,才会有数字满足要求
	return (tot == mod && !remain);
   if (!limit&&dp[pos][tot][remain] != -1)
	return dp[pos][tot][remain];
   ll res = 0;
   int top = limit ? di[pos] : 9;
   for (int i = 0; i <= top; i++) {
 	if (i + tot > mod)
		break;
	res += dfs(pos - 1, i + tot, (10 * remain + i) % mod, limit&&i == di[pos]);
   }
   if (!limit)
	dp[pos][tot][remain] = res;
   return res;
}

反思:
    数位dp的变种中,有一类实际是靠暴力搜索去解决问题,时间复杂度难以估计,但可以通过记忆华搜索进行剪枝,减少不必要的
访问,需要人勇敢去莽。

4、B-number(hdu3652)
题意:
    给你一个n(1<=n<=1000000000),求[1,n]内所有数中含有13，且能被13整除的数。
思路:
    典型的数位dp,设dp[i][j][k],i表示第i位,j表示数%13的结果,k表示状态,其中0表示前面不含13,1表示前一位含1,2表示前面含有13,
这样进行相应的dfs即可获得答案。

核心代码:
ll dfs(int pos, int tot,int state, bool limit) {
   if (pos == -1)
	return (state==2 && !tot);
   if (!limit&&dp[pos][tot][state] != -1)
	return dp[pos][tot][state];
   int top = limit ? di[pos] : 9;
   ll res = 0;
   for (int i = 0; i <= top; i++) {
 	int cstate = state;
	if (state == 1 && i == 3)
		cstate = 2;
	else if (state == 1 && i != 3&&i!=1)
		cstate = 0;
	else if (state == 0 && i == 1)
		cstate = 1;
	res += dfs(pos - 1, (tot * 10 + i) % 13, cstate, limit&&di[pos] == i);
    }
    if (!limit)
	dp[pos][tot][state] = res;
   return res;
}

反思:
    最刚开始,我只是通过flag记录是否存在13,设dp[i][j],这种方法会使一类前面数位不存在13或存在13,但是因为之前有记录而导致return,
使得出错.若是记录dp[i][j][flag],这样会使得也许前面出现13或没出现13,因为已有保存,而使得结果出错.若是记录dp[i][j][[1,9]],这样
使得前面是否出现13,而已有保存，使得结果出错.若记录dp[i][j][flag][[1,9]],这样可以获得答案，但是时间复杂度会很高,因为通过记忆
化搜索的作用就减少很多.因此可以巧妙地使用题解的方法,即dp[i][j][state],state只记录前面是否出现13,前一位没有1的存在,前一位有1
的存在,因为本题关键就是找到13的组合,因为dfs中只要一出现13,那么接下来的搜索都以存在13为基础,而前一位出现1,则可以按照后一位存在3
或存在1，以及其他数字的情况进行搜索。最差的情况就是前面state=0.

5、F(x) (hdu4734)
题意:
    存在一个函数F(x)=An*2^(n-1)+An-1*2^(n-2)+...+A1*1,其中x=(AnAn-1An-2...A1),现在求x=[0,B]中,求F(x)<=F(A)的个数
    
思路：
    显然是一道数位dp题,这题的t(1<=t<=10000),如若使用memset(dp),那么dp空间不应该开过10000,因为时间只有500ms,显然无法
有有效的开数组方法解决问题.因此我们可以换一个思路,只需要初始化一次,之后的搜索只需要继续沿用之前的数组即可.根据题解,发现
可以开dp[12][4600],dp[i][j]表示在第i个位置时,还剩下j个数字量可以继续装,类似于背包思想.至于若从0开始计数,显然说不通,且
状态不正确。

核心代码:
ll dfs(int pos, int tot, bool limit) {
    if (pos == -1)
        return tot>=0;
    if (!limit&&dp[pos][tot] != -1)
        return dp[pos][tot];
    int res = 0;
    int top = limit ? di[pos] : 9;
    for (int i = 0; i <= top; i++) {
        int ntot = tot - i * (1 << pos);
        if (ntot <0)
            break;
        res += dfs(pos - 1, ntot, limit&&di[pos] == i);
    }
    if (!limit)
        dp[pos][tot] = res;
    return res;
}

反思:
    对于因为初始化时间复杂度过高的情况,可以考虑通过只初始化一次,将接下来沿用之前的状态保存.

6、Balanced Number(hdu 3709)
题意:
    一个数如果在数位中有一个位置满足诸如4139,取3为中轴,有2*4+1*1==9*1,则此数为平衡数.求[n,m]之中有多少个平衡数

思路:
    遍历每个位置为中轴,设dp[20][20][2000],其中dp[i][j][k]表示数位i,中轴为j,从左开始算起到右的总平衡值,如若
tot==0,说明存在平衡.

核心代码:
ll dfs(int pos, int tot, int pivot, bool limit) {
   if (pos == -1)
	return tot==0;
   if (!limit&&dp[pos][pivot][tot] != -1)
	return dp[pos][pivot][tot];
   ll res = 0;
   int top = limit ? di[pos] : 9;
   for (int i = 0; i <= top; i++) {
	int tmp = tot + i * (pos - pivot);
	if (tmp < 0)
		break;
	res += dfs(pos - 1, tmp, pivot, limit&&di[pos] == i);
   }
   if (!limit)
	dp[pos][pivot][tot] = res;
   return res;
}

反思:
    只想着如何拆分两个,其实只需要两个合并在一起即可,要心中牢记若是拆开失败,就想着如何合并
    
7、Balanced Number(https://vjudge.net/contest/285467#problem/K)
题意:
    如果一个数它出现的位数中,奇数出现的个数为偶数，偶数出现的个数为奇数,例如6222,那么称为平衡数。求区间[n,m]中有多少个
平衡树。

思路:
    因为总共有3种状态,即一个数出现0次,奇数次，偶数次.那我们可以使用三进制进行状态压缩,那么[0,9]的情况共有3**10,因此可以
开一个dp[22][60000],dp[i][j]表示在第i个位置,j状态下有多少种可能。

核心代码：
ll dfs(int pos,int state,bool limit){
    if(pos==-1)
        return judge(state);
    if(!limit&&dp[pos][state]!=-1)
        return dp[pos][state];
    ll res=0;
    int top=limit?di[pos]:9;
    for(int i=0;i<=top;i++){
        res+=dfs(pos-1,(state==0&&i==0)?0:change(state,i),limit&&di[pos]==i);
    }
    if(!limit)
        dp[pos][state]=res;
    return res;
}

反思:
    数位dp关键是状态的保存，之前一直想不到如何解决，就是因为之前走过的状态无法保存,最初有想到状态压缩保存进制,但是只考虑到了
二进制，难以保存难以保存状态，因此可以考虑3进制，这样就可以方便地保存3种状态，进行判断，今后做题如果状态偏多，可以考虑多进制
操作。

8、Seven Segment Display(zoj3962)
题意:
    有一个时钟以十六进制八位显示，如FFFFFFFF,但是转化需要能量，现在给你时间，每秒十六进制加一，求最终需要消耗多少能量。
思路：
    这题可以转化为数位dp,设dp[10][80],dp[i][j]表示在i位时,前面消耗总能量为j时花费的总能量为多少。设a，b，b=a+n-1,若
b超出了8位十六进制，只需转化为solve(16^8)+solve(b)-solve(a-1)即可。
反思：
    最初想到的是dp[i][j][k],j表示数位，k表示能量，方程意义是满足满足条件的个数,但是有bug至今也不清楚，但是明显这个可以
简化，因为无论当前为是什么数，对最终结果没有任何影响，所以应该考虑清楚再写。如果一个思路不通，可以寻找是否再存其他意义的
状态方程。

8、吉哥系列故事——恨7不成妻(hdu4507)
题意:
    求一个区间[N,M]内所有的满足条件的数的平方和,其中满足的条件有:1、数位中不能存在7. 2、数位整数的每一位加起来的和不是7
的整数倍. 3、这个整数不是7的整数倍.

思路:
    设node dp[i][j][k]表示i位时,位数和模为j,整数模为k,node中包含cnt表示个数,sum表示每个数的和,sqrsum表示平方和.本题的
关键发现(x1+x2+...+xn)^2=x1^2+2*x1*(x2+...xn)+(x2+...+xn)^2=x1^2+2*x1*(x2+...xn)+x2^2+2*x2*(x3+...xn)+
(x3+...xn)^2=.... 无限递归下去。

核心代码：
node dfs(int pos, int tot, int tot2, bool limit) {
     node res; res.cnt = res.sqrsum = res.sum = 0;
     if (pos == -1) {
	res.cnt = (tot != 0 && tot2 != 0);
	return res;
     }
     if (!limit&&dp[pos][tot][tot2].cnt != -1)
	return dp[pos][tot][tot2];
     int top = limit ? di[pos] : 9;
     for (int i = 0; i <= top; i++) {
	    if (i == 7)
		continue;
	node tmp = dfs(pos - 1, (tot + i) % 7, (tot2 * 10 + i) % 7, limit&&di[pos] == i);
	ll A = p[pos] * i%mod;
	res.cnt = (res.cnt + tmp.cnt) % mod;
	res.sum = (res.sum + tmp.sum + A*tmp.cnt%mod) % mod;
	res.sqrsum = (res.sqrsum + A * A%mod*tmp.cnt%mod + tmp.sqrsum + 2 * A%mod*tmp.sum%mod) % mod;
     }
     if (!limit)
	dp[pos][tot][tot2] = res;
     return res;
}

反思：
    本题关键在于难以处理和,其实要是耐心推导公式可以发现规律,另外dp方程不一定只能有一个数值,可以定义一个结构体去
保存更多状态.

9、pair(https://ac.nowcoder.com/acm/contest/887/H)
题意：
    给你A,B,C,现在求有多少个(x,y)满足x&y>c||x^y<c,其中(1<=x<=A,1<=y<=B,1<=A,B,C<=1e9)

思路：
    是一个数位dp的题目,为了简化问题我们可以先取反,即答案变为A*B-cnt(x&y<=c&&x^y>=c)+max(0ll,A-C+1)+max(0ll,B-C+1),因为x,y
都大于0,因此需要减去x=0和y=0的情况.那么我们可以设dp[32][2][2][2][2],dp[i][j][k][l][m],其中i表示第i位,j表示AND限制是否存在,
k表示XOR限制是否存在,l表示x是否有限制,m表示y是否有限制.

代码：
ll dfs(int len,int AND,int XOR,int limit1,int limit2){
    if(len<0)
        return 1;
    if(dp[len][AND][XOR][limit1][limit2]!=-1) return dp[len][AND][XOR][limit1][limit2];
    int top=limit1?(A>>len)&1:1;
    int top2=limit2?(B>>len)&1:1;
    int c=(C>>len)&1;
    ll cnt=0;
    for(int i=0;i<=top;i++){
        for(int j=0;j<=top2;j++){
            if((!AND||(i&j)<=c)&&(!XOR||(i^j)>=c)){
                cnt+=dfs(len-1,AND&&(i&j)==c,XOR&&(i^j)==c,limit1&&i==top,limit2&&j==top2);
            }
        }
    }
    return dp[len][AND][XOR][limit1][limit2] = cnt;
}
 
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>A>>B>>C;
        memset(dp,-1, sizeof(dp));
        cout<<(A*B-dfs(30,1,1,1,1)+max(0ll,A-C+1)+max(0ll,B-C+1))<<endl;
    }
    return 0;
}