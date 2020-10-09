树状数组：
	树状数组常用于维护前缀信息，如前缀和、前缀乘积等等。最常见的如给你一个长度为n的数组，单点修改，查询区间的和。
	在树状数组中，第i个点储存了右端点为i，区间长度为lowbit(i)的区间元素和，也就是从i-lowbit(i)+1到i的区间和
Lowbit(x)表示求x在二进制下位最低的1连同后面的0所组成的数字，举个例子，6的二进制表示是110(2)，那么lowbit(6)=10(2)=2，也就是lowbit(6)=2

//注意0
//对一个数组进行区间修改可以使用差分思想，即初始是c[N]={0},修改时add(l,val),add(r+1,-val),getsum(i)+a[i]即为更新后结果
struct BIT{
    ll c[N];

    inline int lowbit(int x) {return x&-x;}

    void add(int x,int val){
        for(;x<=n;x+=lowbit(x)){
            c[x]+=val;
        }
    }

    ll sum(int x){
        ll sum=0;
        for(;x>0;x-=lowbit(x)){
            sum+=c[x];
        }
        return sum;
    }
};

树状数组维护前缀和的前缀和：
    主要应用在以下两个方面：1、区间加数，区间求和问题。2、区间加等差数列，单点求值问题。
    设s1表示数组a的前缀和，s2表示s1的前缀和，则有：
    s1[i]=sigma(j=1,i)a[j]
    s2[i]=sigma(j=1,i)s1[j]
    经化简可得： s2[i]=(i+1)sigma(j=1,i)a[j]-sigma(j=1,i)j*a[j]
    因此我们只需要开两个数组维护(i+1)sigma(j=1,i)a[j]和sigma(j=1,i)j*a[j]即可。

更高阶情况查看纸质模板

