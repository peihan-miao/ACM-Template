//m-背包容量，w-物品体积，val-物品价值，cnt-物品数量
//01背包
void OneZero(int m,int w,int val){
    for(int i=m;i>=w;i--)
        dp[i]=max(dp[i-w]+val,dp[i]);
}

//完全背包
void Com(int m,int w,int val){
    for(int i=0;i<=m-w;i++)
        dp[i+w]=max(dp[i]+val,dp[i+w]);
}

//多重背包
void Mul(int m,int w,int val,int cnt){
    if(cnt*w>=m){
        Com(m,w,val);
        return;
    }
    for(int i=1;i<=cnt;i<<=1){
        OneZero(m,w*i,val*i); cnt-=i;
    }
    if(cnt) OneZero(m,cnt*w,val*cnt);
}