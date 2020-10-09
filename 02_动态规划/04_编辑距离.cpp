编辑距离：
    给定两个序列S和S2,通过一系列字符编辑(插入、删除、替换)等操作，将S转变成S2，完成这种转换所需要的最少的编辑操
作个数称为S和S2的编辑距离.

int main(){
    scanf("%s%s",s+1,s2+1);
    int len=strlen(s+1),len2=strlen(s2+1);
    dp[1][1]=s[1]==s2[1]?0:1;
    for(int i=2;i<=len;i++) dp[i][1]=dp[i-1][1]+1;
    for(int j=2;j<=len2;j++) dp[1][j]=dp[1][j-1]+1;
    for(int i=2;i<=len;i++){
        for(int j=2;j<=len2;j++){
            dp[i][j]=min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;
            if(s[i]==s2[j]) dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
        }
    }
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len2;j++){
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }
}