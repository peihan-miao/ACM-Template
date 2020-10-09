int n;
int a[N],tot;

struct node{
    double x,y;
}p[N];

bool cmp(node a,node b){
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

bool cmp2(int i,int j){
    return p[i].y<p[j].y;
}

double dist(int i,int j){
    return sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
}

double merge(int left,int right){
    double d = 1e18;
    if(left==right) return d;
    if(left+1==right) return dist(left,right);
    int mid=(left+right)>>1;
    double d1=merge(left,mid),d2=merge(mid+1,right);
    d=min(d1,d2);
    tot=0;
    for(int i=left;i<=right;i++) if(fabs(p[mid].x-p[i].x)<d) a[++tot]=i;
    sort(a+1,a+1+tot,cmp2);
    for(int i=1;i<=tot;i++){
        for(int j=i+1;j<=tot&&p[a[j]].y-p[a[j]].y<d;j++){
            double d3=dist(a[i],a[j]);
            d=min(d,d3);
        }
    }
    return d;
}

int main() {
#ifdef ACM_LOCAL
    freopen("./std.in", "r", stdin);
#endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
    sort(p+1,p+1+n,cmp);
    printf("%.4lf\n",merge(1,n));
}
