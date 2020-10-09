1、01矩阵求第二大全是1矩阵，单调栈
int main() {
    int hi, li, top;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) h[i][j] = (s[i][j] == '1') ? h[i - 1][j] + 1 : 0;
        h[i][m + 1] = 0; st[top = 0] = 0;
        for (int j = 1; j <= m + 1; j++) {
            if (h[i][j] == h[i][st[top]]) st[top] = j;
            else if (h[i][j] > h[i][st[top]]) st[++top] = j;
            else {
                int t = st[top];
                do {
                    hi = h[i][st[top]]; li = (t - st[--top]); //求长度和高度
                    ans.push_back(hi * li); //计算面积
                    ans.push_back(max((hi - 1) * li, hi * (li - 1)));
                } while (h[i][j] < h[i][st[top]]);
                if (h[i][j] > h[i][st[top]]) top++;
                st[top] = j;
            }
        }
        sort(ans.begin(), ans.end(), greater<int>());
        ans.resize(2);
    }
    printf("%d\n", ans[1]);
}

2、01矩阵求最大全是1矩阵，如需求第二大子矩阵则需要将int a=i,b=r[i][j],R=r[i][j]-l[i][j]+1,H=h[i][j]; 四点进行去重即可
void solve(){
    int maxl,maxr;
    for(int i=1;i<=m;i++) r[0][i]=m;
    for(int i=1;i<=n;i++){
        maxl=1; maxr=m;
        for(int j=1;j<=m;j++){
            if(s[i][j]=='0'){
                maxl=j+1;
                h[i][j]=l[i][j]=0;
            }else{
                h[i][j]=h[i-1][j]+1;
                l[i][j]=max(maxl,l[i-1][j]);
            }
        }
        for(int j=m;j>=1;j--){
            if(s[i][j]=='0'){
                maxr=j-1;
                r[i][j]=m;
            }else{
                r[i][j]=min(maxr,r[i-1][j]);
                int R=r[i][j]-l[i][j]+1,H=h[i][j];
                ans=max(ans,R*H);
            }
        }
    }
    printf("%d\n",ans);
}

//简单悬线法
for (int i = 1; i <= n; i++)
  for (int j = 1; j <= m; j++)
    scanf(" %c", s[i] + j), lft[i][j] = rgt[i][j] = j, up[i][j] = 1;
for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= m; j++)
    if (s[i][j] == '0' && s[i][j - 1] == '0') lft[i][j] = lft[i][j - 1];
  for (int j = m; j >= 1; j--)
    if (s[i][j] == '0' && s[i][j + 1] == '0') rgt[i][j] = rgt[i][j + 1];
}
for (int i = 1; i <= n; i++)
  for (int j = 1; j <= m; j++) {
    if (i > 1 && s[i][j] == '0' && s[i - 1][j] == '0') {
      lft[i][j] = max(lft[i][j], lft[i - 1][j]);
      rgt[i][j] = min(rgt[i][j], rgt[i - 1][j]);
      up[i][j] = up[i - 1][j] + 1;
    }
    ans = max(ans, (rgt[i][j] - lft[i][j] + 1) * up[i][j]);
}

3、优先队列+并查集求第二大1矩阵
int find(int x){
    if (par[x] == x)return x;
    return par[x] = find(par[x]);
}

void merge(int x,int y){
    int fx=find(x),fy=find(y);
    par[fy]=fx;
    len[fx]+=len[fy];
    return;
}

int main() {
    scanf("%d%d",&n,&m);
    int ans=0,ans2=0;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++){
            if(s[j]=='0') h[j]=0;
            else{
                h[j]++;
                q.push(node(j,h[j]));
            }
            len[j]=1;par[j]=j;vis[j]=0;
        }
        while(!q.empty()){
            node t=q.top(); q.pop();
            int pos=t.pos,hi=t.height;
            vis[pos]=1;
            if(vis[pos-1]) merge(pos-1,pos);
            if(vis[pos+1]) merge(pos+1,pos);
            int f=find(pos);
            if(len[f]*hi>=ans) ans2=ans,ans=len[f]*hi;
            else ans2=max(ans2,len[f]*hi);
            ans2=max(ans2,max((len[f]-1)*hi,len[f]*(hi-1)));
        }
    }
    printf("%d\n",ans2);
}

4、给定一个矩阵n*m(1<=n,m<=500),求其中最大子矩阵满足矩阵中|最大值-最小值|<=K的大小
void solve(){
    int ans=0,ans2=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) { mx[j]=-inf; mn[j]=inf;}
        for(int j=i;j<=n;j++){
            for(int k=1;k<=m;k++) mx[k]=max(mx[k],a[j][k]);
            for(int k=1;k<=m;k++) mn[k]=min(mn[k],a[j][k]);
            int l=1,head=1,tail=0,head2=1,tail2=0;
            for(int r=1;r<=m;r++){
                while(head<=tail&&mx[r]>=mx[q[0][tail]]) tail--;
                while(head2<=tail2&&mn[r]<=mn[q[1][tail2]]) tail2--;
                q[0][++tail]=r;
                q[1][++tail2]=r;
                while(l<=r&&mx[q[0][head]]-mn[q[1][head2]]>k){
                    l++;
                    if(q[0][head]<l) head++;
                    if(q[1][head2]<l) head2++;
                }
                ans=max(ans,(j-i+1)*(r-l+1)); //求最大子矩阵
                ans+=r-l+1; //求所有满足条件的子矩阵
            }
        }
    }
    printf("%d\n",ans);
}