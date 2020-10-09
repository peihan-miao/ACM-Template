struct SegTree{
    ll sum[N<<2];

    static inline int lson(int k) {return k<<1;}

    static inline int rson(int k) {return k<<1|1;}

    void up(int k){
        sum[k]=sum[lson(k)]+sum[rson(k)];
    }

    void build(int k,int l,int r){
        if(l==r){
            scanf("%lld",&sum[k]);
            return;
        }
        int mid=(l+r)>>1;
        build(lson(k),l,mid);
        build(rson(k),mid+1,r);
        up(k);
    }

    void update(int k,int l,int r,int pos,int val){
        if(l==r){
            sum[k]=max(0ll,sum[k]+val);
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) update(lson(k),l,mid,pos,val);
        else update(rson(k),mid+1,r,pos,val);
        up(k);
    }

    ll query(int k,int l,int r,int x,int y){
        if(l==x&&r==y){
            return sum[k];
        }
        int mid = (l+r)>>1;
        if(y<=mid) return query(lson(k),l,mid,x,y);
        else if(x>mid) return query(rson(k),mid+1,r,x,y);
        else return query(lson(k),l,mid,x,mid)+query(rson(k),mid+1,r,mid+1,y);
    }
}st;