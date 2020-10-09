struct Linear_Basis{
    ll d[61],p[61];
    int cnt;
    bool zero;
    //初始化
    Linear_Basis(){
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
        cnt=0; zero=0;
    }
    //插入
    bool insert(ll val){
        for (int i=60;i>=0;i--)
            if (val&(1LL<<i)){
                if (!d[i]){
                    d[i]=val;
                    break;
                }
                val^=d[i];
            }
        return val>0;
    }
    //查询线性基所能表示最大值
    ll query_max(){
        ll ret=0;
        for (int i=60;i>=0;i--)
            if ((ret^d[i])>ret)
                ret^=d[i];
        return ret;
    }
    //查询线性基所能表示最小值
    ll query_min(){
        for (int i=0;i<=60;i++)
            if (d[i])
                return d[i];
        return 0;
    }
    //重构,消除多余的1
    void rebuild(){
        for (int i=60;i>=0;i--)
            for (int j=i-1;j>=0;j--)
                if (d[i]&(1LL<<j))
                    d[i]^=d[j];
        for (int i=0;i<=60;i++)
            if (d[i])
                p[cnt++]=d[i];
    }
    //求第k小数,注意特判0
    ll kthquery(ll k){
        ll ret=0;
        if (k>=(1LL<<cnt))
            return -1;
        for (int i=60;i>=0;i--)
            if (k&(1LL<<i))
                ret^=p[i];
        return ret;
    }
    //查询是否存在x->y的变化
    bool query_exist(ll x,ll y){
        for(int i=60;i>=0;i--){
            if((1ll<<i)&y){
                if((1ll<<i)&x)
                    continue;
                else
                    x^=d[i];
            }else if((1ll<<i)&x){
                x^=d[i];
            }
        }
        return x==y;
    }
};

//线性基合并
Linear_Basis merge(const Linear_Basis &n1,const Linear_Basis &n2){
    Linear_Basis ret=n1;
    for (int i=60;i>=0;i--)
        if (n2.d[i])
            ret.insert(n1.d[i]);
    return ret;
}