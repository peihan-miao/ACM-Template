1、前缀和与差分
    对于一个数组a定义数组s[i]=sigma(j=1,i)a[j]
//为了避免数组越位，下标从1开始用
for(int i=1;i<=n;i++)
    s[i]=s[i-1]+a[i];

    定义数组d[i]= 1、i==0,di[i]=a[i] 2、i>=1,d[i]=a[i]-a[i-1]

//为了避免数组越位，下标从1开始用
for(int i=n;i>=1;i--)
    d[i]=a[i]-a[i-1];
    
    发现对于原数组a的区间加数操作对应差分数组d只改变了两个地方。因为差分数组的前缀和数组为原数组，所以对差分数组的
修改，在原数组上产生的影响是这个位置以后的一个后缀影响。给d[l]加上x就相当于给a[l],a[l+1],a[l+2]....a[n]全部加上x。
给d[r+1]加上-x就相当于给a[r+1],r[r+2],....a[n]全部加上-x。那么如果要给a[l],a[l+1]...a[r]全部加上x就很简单了。

void add(int l,int r,int x){
    d[l]+=x;
    d[r+1]-=x;
}

注意我们操作的是数组d，是差分数组，不是原数组。也就是说如果你最后要输出原数组a的话还要在做一遍前缀和还原。

2、静态维护区间加等差数列的求和问题
	维护一个数组，先进行m次操作，然后查询每个位置的值，每个操作给定四个参数l,r,a,k表示从l到r依次加上一个首项为a，公差为k的等差数列。
其中[l,r]区间分别加上[a,a+k,a+2k,...a+(r-l)k]

int n,m,d2[N],l,r,a,k;
void add(int l,int r,int a,int k){
    d2[l]+=a;
    d2[l+1]+=k-a;
    d2[r+1]-=(r-l+1)*k+a;
    d2[r+2]-=(l-r)*k-a;
}
void iter(){
    for(int i=1;i<=n;++i) d2[i]+=d2[i-1];
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        scanf("%d%d%d%d",&l,&r,&a,&k);
        add(l,r,a,k);
    }
    iter(); //第一次为了将每项额外加的补齐
    iter(); //还原完整数组
    for(int i=1;i<=n;++i) printf("%d%c",d2[i],i==n?'\n':' ');
    return 0;
}

3、二维前缀和与差分
    对于一个二维数组a定义s[i][j]=sigma(p=0,i)sigma(q=0,j)a[p][q]为数组a的前缀和数组
//为了避免数组越位，下标从1开始
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
    }
}
    那么定义d[i][j]为差分数组
为了避免数组越位，下标从1开始
for(int i=n;i;i--){
    for(int j=m;j;j--){
        d[i][j]=a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1];
    }
}

静态数组的求和问题
sum(l1,r1,l2,r2)=s[r1][r2]-s[l1-1][r2]-s[r1][l2-1]+s[l1-1][l2-1]。这个是利用了简单的容斥原理，纸上画画图就能理解
因为s[i][j]是一个左上矩形的矩阵和，所以s[r1][r2]这个矩阵在减去s[l1-1][r2]与s[r1][l2-1]矩阵后，它们共有的s[l1-1][l2-1]
部分被减了两次，所以再加上一次。
ll sum(int l1,int r1,int l2,int r2){
    return s[r1][r2]-s[l1-1][r2]-s[r1][l2-1]+s[l1-1][l2-1];
}

进行m次区间修改后的静态单点求值问题
    推导过程类似一维的前缀和与差分，其实就是反过来考虑差分数组对原数组的影响是一个后缀影响（这里可以理解为影响整个右下角矩阵）
void add(int l1,int r1,int l2,int r2,int x){
    d[l1][l2]+=x;
    d[r1+1][l2]-=x;
    d[l1][r2+1]-=x;
    d[r1+1][r2+1]+=x;
}
    同理，d数组可以靠一次前缀和操作还原为原数组，如果是矩阵求和问题还可再做一遍前缀和。


4、高维前缀和
    同理三维只需要三个维度进行处理即可
for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
        a[i][j]=a[i][j]+a[i][j-1];
    }
}
for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
        a[i][j]=a[i][j]+a[i-1][j];
    }
}

5、状压dp前缀和
for(int i=0;i<w;++i)//依次枚举每个维度
{
    for(int j=0;j<(1<<w);++j)//求每个维度的前缀和
    {
        if(j&(1<<i))s[j]+=s[j^(1<<i)]; 
    }
}


6、菱形差分
题目：
    地方阵地可以看做是n×m的矩形，航空母舰总共会派出q架飞机。飞机有两种，第一种飞机会轰炸以(xi, yi)为中心，
对角线长为li的正菱形(也就是两条对角线分别于x轴 y轴平行的正方形)，而第二种飞机只会轰炸正菱形的上半部分(包括第xi行)
(具体看样例解释)。现在小a想知道所有格子被轰炸次数的异或和，注意：不保证被轰炸的格子一定在矩形范围内，若越界请忽略

输入：
    第一行三个整数n, m, q分别表示矩阵的长/宽/询问次数，接下来q行，每行四个整数opt,x,y,l表示飞机类型，轰炸的坐标，以及对角线长度
保证l为奇数！

4 5 4
1 2 2 1
1 3 3 5
1 3 2 3
2 2 4 3

轰炸后结果为：

0 0 1 1 0
0 3 2 2 1
2 2 2 1 1
0 2 1 1 0
最后把所有元素异或后为2

代码：
int n,m,q,base=500;
int op,x,y,L;
int a[N][N],b[N][N];
 
void down(int x,int y,int L){
    a[x+L+1][y]++;
    a[x+1][y+L]--;
 
    b[x+1][y-L+1]++;
    b[x+L+1][y+1]--;
}
 
void up(int x,int y,int L){
    a[x-L][y]++;
    a[x+1][y-L-1]--;
 
    b[x-L][y+1]--;
    b[x+1][y+2+L]++;
}
 
int main() {
    read(n); read(m); read(q);
    while(q--){
        read(op); read(x); read(y); read(L);
        x+=base; y+=base;
        if(op==1) down(x,y,L/2);
        up(x,y,L/2);
    }
    int ans=0;
    for(int i=1;i<=n+base*2;i++){
        int x=0;
        for(int j=1;j<=m+base*2;j++){
            x+=a[i][j]+b[i][j];
            if(i>base&&i<=n+base&&j>base&&j<=m+base) ans^=x;
            a[i+1][j-1]+=a[i][j];
            b[i+1][j+1]+=b[i][j];
        }
    }
    printf("%d\n",ans);
}









