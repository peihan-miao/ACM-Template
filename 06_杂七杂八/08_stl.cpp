1、lower_bound,upper_bound
	lower_bound()和upper_bound()都是利用二分查找的方法在一个排好序的数组中进行查找的。

	在从小到大的排序数组中:
	1、lower_bound(begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数
字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
	2、upper_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的
地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

	在从大到小的排序数组中，重载lower_bound()和upper_bound()：
	1、lower_bound( begin,end,num,greater<type>()):从数组的begin位置到end-1位置二分查找第一个小于或等于num
的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
	2、upper_bound( begin,end,num,greater<type>() ):从数组的begin位置到end-1位置二分查找第一个小于num的数字，
找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。


//数组测试
int a[N];

int main(){
    int n=10;
    //从小到大,lower_bound测试,找第一个大于或等于num的数字，超出去一律返回位置n
    for(int i=0;i<n;i++) a[i]=i;
    int i=lower_bound(a,a+n,n+n)-a;
    printf("%d %d\n",i,a[i]);
    //从小到大,upper_bound测试,第一个大于num的数字，超出去一律返回位置n
    i=upper_bound(a,a+n,100)-a;
    printf("%d %d\n",i,a[i]);
    //从大到小,lower_bound测试,找第一个小于或等于num的数字，若小于所有值，则一律返回n
    for(int i=0;i<n;i++) a[i]=n-i-1;
    i=lower_bound(a,a+n,-1,greater<int>())-a;
    printf("%d %d\n",i,a[i]);
    //从大到小,upper_bound测试,第一个小于num的数字，若小于所有值，则一律返回n
    i=upper_bound(a,a+n,-999,greater<int>())-a;
    printf("%d %d\n",i,a[i]);

    //情况上面情况一样
    vector<int>v;
    for(int i=0;i<n;i++) v.push_back(i);
    int i=lower_bound(v.begin(),v.end(),23)-v.begin();
    printf("%d %d\n",i,v[i]);
}


2、结构体中比较函数作用于数组和set
//没有t的是i，t是j,i<j，因此返回x较小，如果x一样大，返回y大的
struct node{
    int x,y;
    bool operator <(const node&t)const{
        if(x==t.x) return y>t.y;
        return x<t.x;
    }
};

int main(){
#ifdef ACM_LOCAL
    freopen("./std.in", "r", stdin);
    //freopen("./std.out","w",stdout);
#endif
    set<node>st;
    st.insert(node{1,1});
    st.insert(node{1,3});
    st.insert(node{2,2});
    node p[N];
    p[1]=node{1,1}; p[2]=node{1,3}; p[3]=node{2,2};
    sort(p+1,p+1+3);
    //(1,3)(1,1)(2,2)
}

3、优先队列的比较函数
//跟上述情况相反
struct node{
    int x,y;
    bool operator <(const node&t)const{
        if(x==t.x) return y>t.y;
        return x<t.x;
    }
};

int main(){
#ifdef ACM_LOCAL
    freopen("./std.in", "r", stdin);
    //freopen("./std.out","w",stdout);
#endif
    priority_queue<node>q;
    q.push(node{1,3});
    q.push(node{1,1});
    q.push(node{2,1});
    while(!q.empty()){
        node t=q.top(); q.pop();
        printf("%d %d\n",t.x,t.y);
    }
    //(2,1)(1,1)(1,3)
    set<int>st;
    for(int i=1;i<=5;i++) st.insert(i);
    cout<<*(--st.end())<<endl;
    //5
}
