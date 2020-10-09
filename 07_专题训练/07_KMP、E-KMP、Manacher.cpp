KMP内容：

1、KMP最小循环节、循环周期：

定理：假设S的长度为len，则S存在最小循环节，循环节的长度L为len-next[len]，子串为S[0…len-next[len]-1]。

（1）如果len可以被len - next[len]整除，则表明字符串S可以完全由循环节循环组成，循环周期T=len/L。

（2）如果不能，说明还需要再添加几个字母才能补全。需要补的个数是循环个数L-len%L=L-(len-L)%L=L-next[len]%L，L=len-next[len]。

注意：对于补全最小循环节，n % (n - Next[n]) == 0 && n / (n - Next[n]) > 1 表示无需再补循环节，n - Next[n] - n % (n - Next[n])表示
补全最小循环节的最少个数。

1）求最小循环节周期>1的情况
for(int i=1;i<=n;i++){
    if(i%(i-nx[i])==0&&i/(i-nx[i])>1)
        printf("%d %d\n",i,i/(i-nx[i]));
}

2）求最小循环节周期
printf("%d\n",(n%(n-nx[n])==0)?(n/(n-nx[n])):1);

3）补全最小循环节,周期要K>=2
if (n % (n - Next[n]) == 0 && n / (n - Next[n]) > 1){	
    printf("0\n");
    continue;
}
int len = n - Next[n]; // 最小循环节
printf("%d\n", len - n % len);

2、KMP将一个字符串补成代价最小的回文串
    只需将字符串倒过来，进行KMP匹配，结果2*n-i即可。
int KMP() {
    int i, j;
    getNext();
    i = j = 0;
    while (j < n&&i<n) {
        while (i != -1 && x[i] != y[j])
            i = nx[i];
        i++;j++;
    }
    return 2*n-i;
}

3、求一个字符串的所有前缀在字符串中出现过多少次
    设dp[i]表示以i结尾的所有成立的字符串个数，因此状态转移返程为dp[i]=(dp[nx[i]]+1)%mod
for(int i=1;i<=n;i++){
    dp[i]=(dp[nx[i]]+1)%mod;
    res=(res+dp[i])%mod;
}

4、构造一个k([1,1e9])个字符串，字符限定来自提供的y,但是不能出现x字符串,求可以组合出来的字符串的最大数量。
    考虑到k最大为1e9,需要通过矩阵快速幂解决问题,因此关键就是构造矩阵.矩阵构造需要通过next数组,可以将矩阵长度限定为[0,n-1],其意义是
前i个字符已经匹配成功，需要匹配下一个字符。如果匹配成功则转移到下一个位置，如果匹配失败则通过next数组所转移到位置即可。
for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
        int t = i;
        while(t>0&&y[j]!=x[t])
              t=nx[t];
              if(y[j]==x[t]||t==-1)
                 t++;
              A.arr[i][t]++;
     }
 }
 
 5、给定一个字符矩阵(1<=r<=10000,1<=c<=75),求最小的子矩阵可以将矩阵全部覆盖，运行多余。
    本题最初使用的方法是求所有的行的最小循环节和列的最小循环节,然后求最小公倍数相乘即是答案。但实际上有一组样例会否决情况，
 Input
 2 8
 ABCDEFAB
 ABCDEABC
 2 8
 ABCDEFAB
 AAAABAAA
 Output
 16
 12
    显然上述方法存在问题，因此得寻找其他方法。注意到1<=c<=75，我们可以设立一个vis[N]数组,vis[i]表示长度为i的循环串出现的个数，
如果出现vis[i]==r,则说明这个循环串是可行的。这样最小满足的即是最小矩阵的列大小，接下来求行大小，因为列大小确定，我们只需要对r行
字符串进行求next数组,求出他们的最小循环节即是最小行大小。精彩之处在于使用整个字符串数组进行匹配。
void solve_col(){
    int i,j;
    j=nx[0]=-1;
    i=0;
    while(i<r){
        while(-1!=j&&strcmp(cow[i],cow[j])!=0)
            j=nx[j];
        nx[++i]=++j;
    }
    ans_row=r-nx[r];
}

E-KMP内容：
    定义母串S和子串T,S的长度为n，T的长度为m;求字符串T与字符串S的每一个后缀的最长公共前缀。也就是说,设有extend数组:extend[i]
表示T与S[i,n-1]的最长公共前缀，要求出所有extend[i](0<=i<n)。
（注意到，如果存在若干个extend[i]=m，则表示T在S中完全出现，且是在位置i出现，这就是标准的KMP问题，所以一般将它称为扩展KMP算法。）

1、求一个字符串所有前缀在字符串中出现次数和
    对该字符串进行e-kmp,得到nx[n]数组，显然sum(nx[0]...nx[n-1])就是答案。