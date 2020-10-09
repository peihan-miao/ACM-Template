汉诺塔：
    其实算法非常简单，当盘子的个数为n时，移动的次数应等于2^n-1。只要轮流进行两步操作就可以了。首先把三根
柱子按顺序排成品字型，把所有的圆盘按从大到小的顺序放在柱子A上，根据圆盘的数量确定柱子的排放顺序：若n为偶数，
按顺时针方向依次摆放 A B C；若n为奇数，按顺时针方向依次摆放 A C B。
    ⑴按顺时针方向把圆盘1从现在的柱子移动到下一根柱子，即当n为偶数时，若圆盘1在柱子A，则把它移动到B；若圆
盘1在柱子B，则把它移动到C；若圆盘1在柱子C，则把它移动到A。
    ⑵接着，把另外两根柱子上可以移动的圆盘移动到新的柱子上。即把非空柱子上的圆盘移动到空柱子上，当两根柱子
都非空时，移动较大的圆盘。这一步没有明确规定移动哪个圆盘，你可能以为会有多种可能性，其实不然，可实施的行动是唯一的。
    ⑶反复进行⑴⑵操作，最后就能按规定完成汉诺塔的移动。
    所以结果非常简单，就是按照移动规则向一个方向移动金片：
    如3阶汉诺塔的移动：A→C,A→B,C→B,A→C,B→A,B→C,A→C

void Move(int n, char a, char b){
    printf("第%d次移动 Move %d: Move from %c to %c !\n",++cnt,n,a+'A',b+'A');
}

void Hanoi(int n,int a,int b,int c){
    if(n==1){
        Move(n,a,c);
    }else{
        Hanoi(n - 1, a, c, b);
        Move(n, a, c);
        Hanoi(n - 1, b, a, c);
    }
}


求汉诺塔具体操作数结果：
int main(){
    int ab=0,ac=1,ba=2,bc=3,ca=4,cb=5;
    scanf("%d",&n);
    ret[ac]++; dp[1][ac]=1;
    for(int i=2;i<=n;i++){
        if(i%2==0){
            dp[i][ab]+=dp[i-1][ac]+dp[i-1][cb];
            dp[i][bc]+=dp[i-1][ac]+dp[i-1][ba];
            dp[i][ca]+=dp[i-1][ba]+dp[i-1][cb];
        }else{
            dp[i][ac]+=dp[i-1][ab]+dp[i-1][bc];
            dp[i][ba]+=dp[i-1][bc]+dp[i-1][ca];
            dp[i][cb]+=dp[i-1][ab]+dp[i-1][ca];
        }
        for(int j=0;j<6;j++) ret[j]+=dp[i][j];
    }
    printf("A->B:%lld\n", ret[0]);
    printf("A->C:%lld\n", ret[1]);
    printf("B->A:%lld\n", ret[2]);
    printf("B->C:%lld\n", ret[3]);
    printf("C->A:%lld\n", ret[4]);
    printf("C->B:%lld\n", ret[5]);
    printf("SUM:%lld\n", pw(n)-1);
}