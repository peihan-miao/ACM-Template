问题1：
    现在想修路，连接两个城市，城市标号分别为x,y。想要路不交叉，求最多能修多少条路
    注意直接求LIS可以得到最优解的个数，但是st里面存储的不是最优解

int main(){
    int Case=1;
    while(scanf("%d",&n)==1){
        for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
        sort(a+1,a+1+n); //x<t.x
        set<int>st;
        st.insert(a[1].y);
        for(int i=2;i<=n;i++){
            auto it=st.lower_bound(a[i].y);
            if(it==st.end()){
                st.insert(a[i].y);
            }else{
                st.erase(it);
                st.insert(a[i].y);
            }
        }
        printf("Case %d:\n",Case++);
        if(st.size()==1){
            printf("My king, at most %d road can be built.\n\n",st.size());
        }else{
            printf("My king, at most %d roads can be built.\n\n",st.size());
        }
    }
    return 0;
}

问题2：
    现在你有N块矩形木板，第i块木板的尺寸是Xi*Yi，第i块木板能放在第j块木板上方当且仅当Xi<Xj且Yi<Yj，于是你很可能没法
把所有的木板按照一定的次序叠放起来。你想把这些木板分为尽可能少的组，使得每组内的木板都能按照一定的次序叠放。你需要给出任
意一种合理的分组方案。

    根据Dilworth定理，最小组数等于Zi的最长下降子序列长度。因此可以求最长下降子序列，获得结果，并可以得到分组情况

int n;
struct node{
    int x,y,id;
}p[N];

bool cmp(node s,node t){
    if(s.x==t.x) return s.y>t.y;
    return s.x>t.x;
}

int bcc[N];
set<pii>st;

int main(){
#ifdef ACM_LOCAL
    freopen("./std.in", "r", stdin);
    //freopen("./std.out","w",stdout);
#endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p[i].x,&p[i].y);
        p[i].id=i;
    }
    sort(p+1,p+1+n,cmp);
    int tot=1;
    for(int i=1;i<=n;i++){
        auto it=st.lower_bound(make_pair(p[i].y,0));
        if(it==st.end()){
            bcc[p[i].id]=tot;
            st.insert(make_pair(p[i].y,tot));
            tot++;
        }else{
            bcc[p[i].id]=(*it).second;
            st.erase(it);
            st.insert(make_pair(p[i].y,bcc[p[i].id]));
        }
    }
    printf("%d\n",st.size()); //有多少组解
    for(int i=1;i<=n;i++) printf("%d%c",bcc[i],i==n?'\n':' ');
}