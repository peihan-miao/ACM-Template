1、st表
struct ST {
    int k2[21], st[21][N], Log[N];
    void init_st(int n) {
        k2[0] = 1;
        for (int i = 1; i <= 20; i++) k2[i] = 2 * k2[i - 1];
        Log[0] = -1; for (int i = 1; i < N; i++) Log[i] = Log[i / 2] + 1;
        for (int i = 1; i <= n; i++) st[0][i] = height[i];
        for (int i = 1; i <= Log[n]; i++) {
            for (int j = 1; j + k2[i] - 1 <= n; j++) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + k2[i - 1]]);
            }
        }
    }
    int query_min(int x, int y) {
        int len = log2(y - x + 1);
        return min(st[len][x], st[len][y - k2[len] + 1]);
    }
}st;

精简版
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++)
    scanf("%d",&st[0][i]);
int top = log2(n);
for(int i=1;i<=top;i++){
    for(int j=1;j+(1<<i)-1<=n;j++){
        st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
    }
}
int x=1,y=m;
while(y<=n){
     int len = log2(y-x+1);
     printf("%d\n",min(st[len][x],st[len][y-(1<<len)+1]));
     x++;y++;
}