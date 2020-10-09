后缀数组：
    后缀就是从字符串的某个位置i到字符串末尾的子串，我们定义以s的第i个字符为第一个元素的后缀为suff(i).把s的每个后缀按照字典序
排序，后缀数组sa[i]就表示排名为i的后缀的起始位置的下标,映射数组rk[i]就表示起始位置的下标为i的后缀的排名，sa表示排名为i的是啥，
rk表示第i个的排名是啥。
    最长公共前缀——后缀数组的辅助工具LCP：LCP(i,j)为suff(sa[i])与suff(sa[j])的最长公共前缀关于LCP的几条性质：1、LCP(i,j)=LCP(j,i) 
2、LCP(i,i)=len(sa[i])=n-sa[i]+1 3、LCP(i,k)=min(LCP(i,j),LCP(j,k)) 对于任意1<=i<=j<=k<=n  4、LCP(i,k)=min(LCP(j,j-1)) 
对于任意1<i<=j<=k<=n
    如何求LCP？
    设height[i]为LCP(i,i-1)，1<i<=n，显然height[1]=0. 由LCP Theorem可得，LCP(i,k)=min(height[j]) i+1<=j<=k
设h[i]=height[rk[i]]，同样的，height[i]=h[sa[i]];  =>  h[i]>=h[i-1]-1;

应用：
1)求两个字符串最大的公共子串
    将两个字符串连接起来，中间加一个其它字符，这样只需求出设height,只需要扫一遍height即可得到最优结果。height[i]为LCP(i,i-1)，
1<i<=n，LCP(i,j)为suff(sa[i])与suff(sa[j])的最长公共前缀.
for(int i=1;i<=n;i++){
    if(sa[i]<p&&sa[i-1]>p) res = max(res,height[i]);
    if(sa[i]>p&&sa[i-1]<p) res = max(res,height[i]);
}

2）求一个串中所有子串的种类个数
    举例多个字符串，将其后缀排序后进行枚举发现,当前字符串的贡献为与下一个字符串的非公共长度，最后一个只需要全加即可。
而height[i]=LCP(i-1,i)的最长公共前缀。
ll res=0;
for(int i=2;i<=n;i++){
    int top = height[i];
    res+=(n-sa[i-1]+1-top);
}
res+=(n-sa[n]+1);

3）求一个数组中数重复出现次数>=k的子序列(可重叠)最长长度是多少
    建立后缀数组,对于每个height[i]进行枚举,使用二分+st表查询以i为中心,[l,r]区间的最大值,其中[l,r]区间中每个值都>=height[i]
更新区间长度最大值即可.

4）查询一个数组中满足模式相似的子序列(一个子序列加上一个值也算相似)重复出现2次以上,且没有交集的最大长度
    可以先进行差分,取得差值[1,n-1],然后对于差值建立后缀数组,然后通过二分查询值进行判断是否存在可行解.
bool isOK(int n,int k){
    vector<pii>v;
    for(int i=2;i<=n;i++){
        if(height[i]+1>=k){
            int j;
            for(j=i;j<=n;j++){
                if(height[j]+1<k) break;
                int l1=sa[j-1],r1=sa[j-1]+k-1;
                int l2=sa[j],r2=sa[j]+k-1;
                if(check(l1,r1,l2,r2)) return true;
                for(int k=0;k<v.size();k++){
                    if(check(l2,r2,v[k].first,v[k].second)) return true;
                }
                v.push_back(make_pair(l1,r1));
            }
            i=j; v.clear();
        }
    }
    return false;
}

5）给定一个字符串，求重复次数最多的连续重复子串,输出最大的重复次数
    本题是一道裸的后缀数组题，"重复次数最多的连续重复子串"解法(摘自罗穗骞的国家集训队论文):先穷举长度L，然后求长度为L
的子串最多能连续出现几次。首先连续出现1次是肯定可以的，所以这里只考虑至少2次的情况。假设在原字符串中连续出现2次，记这个
子字符串为S，那么S肯定包括了字符r[0], r[L], r[L*2],r[L*3], ……中的某相邻的两个。所以只须看字符r[L*i]和r[L*(i+1)]往前和
往后各能匹配到多远。最后看最大值是多少。
    穷举长度L的时间是n，每次计算的时间是n/L。所以整个做法的时间复杂度是O(n/1+n/2+n/3+……+n/n)=O(nlogn)。
    要提一提的总共有两点，第一点比较显而易见 "S肯定包括了字符r[0], r[L], r[L*2],r[L*3], ……中的某相邻的两个"
由于当前S是有两个长度为L的连续重复子串拼接而成的，那意味着S[i]和S[i+L](0≤i<L)必定是一样的字符，而这两个字符位置相差L
而字符r[0],r[L],r[L*2],r[L*3],......中相邻两个的位置差均为L“只须看字符r[L*i]和r[L*(i+1)]往前和往后各能匹配到多远”，对于往
后能匹配到多远，这个直接根据最长公共前缀就能很容易得到，即上图中的后缀Suffix(6)和后缀Suffix(9)的最长公共前缀。而对于往前能匹
配到多远，我们当然可以一开始就把字符串反过来拼在后面，这样也能根据最长公共前缀来看往前能匹配到多远，但这样效率就比较低了。
    其实，当枚举的重复子串长度为i时，我们在枚举r[i*j]和r[i*(j+1)]的过程中，必然可以出现r[i*j]在第一个重复子串里，而r[i*(j+1)]
在第二个重复子串里的这种情况，如果此时r[i*j]是第一个重复子串的首字符，这样直接用公共前缀k除以i并向下取整就可以得到最后结果。但如
果r[i*j]如果不是首字符，这样算完之后结果就有可能偏小，因为r[i*j]前面可能还有少许字符也能看作是第一个重复子串里的。于是，我们不妨
先算一下，从r[i*j]开始，除匹配了k/i个重复子串，还剩余了几个字符，剩余的自然是k%i个字符。如果说r[i*j]的前面还有i-k%i个字符完成匹
配的话，这样就相当于利用多余的字符还可以再匹配出一个重复子串，于是我们只要检查一下从r[i*j-(i-k%i)]和r[i*(j+1)-(i-k%i)]开始是否
有i-k%i个字符能够完成匹配即可，也就是说去检查这两个后缀的最长公共前缀是否比i-k%i大即可。
    当然如果公共前缀不比i-k%i小，自然就不比i小，因为后面的字符都是已经匹配上的，所以为了方便编写，程序里面就直接去看是否会比i小就
可以了。

代码：

int calc(int i,int j){
    int x = rk[i];
    int y = rk[j];
    if(x>y) swap(x,y);
    return st.query_min(x+1,y);
}

int ans=1;
for(int i=1;i<n;i++){
    for(int j=1;j+i<=n;j+=i){
        int lcp = calc(j,j+i);
        int pos = j-(i-lcp%i);
        int res = lcp/i+1;
        if(pos>=1&&calc(pos,pos+i)>=i) res++;
        ans=max(ans,res);
    }
}
printf("%d\n",ans);

或者：
for(int i=1;i<=n;i++){
    for(int j=1;j+i<=n;j+=i){
        int len = st.query_min(rk[j],rk[j+i]);
        int re = i-len%i;
        if(re==i){
            ans=max((len+i)/i,ans);
        }else{
            int p=j-re;
            if(p>=1&&st.query_min(rk[p],rk[p+i])==len+re)
                ans=max(ans,(len+re+i)/i);
        }
    }
}

若输出循环次数最多的，最小字典序子串，那么可以存一个repeat，然后保存循环次数==repeat的长度，然后结合后缀数组性质暴力枚举即可。
int main() {
    int Case=1;
    while(scanf("%s",s+1)==1){
        if(strcmp(s+1,"#")==0) break;
        printf("Case %d: ",Case++);
        n=strlen(s+1);
        DA(s,n,128);st.init(n);
        vector<int>v;
        int repeat=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j+i<=n;j+=i){
                int len = st.query_min(rk[j],rk[j+i]);
                int re=i-len%i,cnt=0;
                if(re==i) cnt=(i+len)/i;
                else{
                    int p=j-re;
                    if(p>=1&&st.query_min(rk[p],rk[p+i])>=re+len) cnt=(i+len+re)/i;
                }
                if(cnt>repeat){
                    repeat=cnt; v.clear();v.push_back(i);
                }else if(cnt==repeat) v.push_back(i);
            }
        }
        if(repeat==1){
            char c = 'z';
            for(int i=1;i<=n;i++) c=min(c,s[i]);
            printf("%c\n",c);
            continue;
        }
        int be=0,en=0;
		//枚举
        for(int i=1;i<=n&&!be;i++){
            for(int j=0;j<v.size();j++){
                int p=sa[i],p2=p+v[j];
                if(p2>n) continue;
                int len = st.query_min(rk[p],rk[p2]);
                if(len>=(repeat-1)*v[j]){
                    be=p;en=p+repeat*v[j]-1;
                    break;
                }
            }
        }
        for(;be<=en;be++) printf("%c",s[be]);
        printf("\n");
    }
}

6）两个字符串，求三元组(i,j,k),即s[i]...s[i+k-1]和s[j]...s[j+k-1]相同的个数,k>=给定l。
	计算A的某个后缀与B的某个后缀的最长公共前缀长度，如果长度L大于k，则加上L-k+1组。将两个字符串连接起来
，中间用一个没有出现的字符分开。（这是一个神奇的做法）然后通过height数组分组，某个组内的height都是大于等
于k的，也就是任意两个后缀的最长公共前缀都至少为k。扫描一遍，遇到一个B的后缀就与之前的A后缀进行统计，求出
所有的满足的组数。但是这样的做法便是n^2的。可以发现两个后缀的最长公共前缀为这一段的height值的最小值。
可以通过一个单调栈来维护一下，当前要入栈元素如果小于栈底元素，说明之后加入的B后缀与栈底的最长公共前缀是小
于等于入栈的。这样就保证了单调栈内的height值是绝对递增的，逐渐合并，均摊可以达到o(n)的复杂度。然后扫描两遍即可。

int main() {
    while(scanf("%d",&k)==1){
        if(!k) break;
        scanf("%s%s",s+1,s2+1);
        int len=strlen(s+1);
        s[0]=1;strcat(s,"#");strcat(s,s2+1);s[0]=0;
        int Len=strlen(s+1);
        DA(s,Len,128);
        ll ans=0,tot=0;
        int top=0;
        //a扫b
        for(int i=1;i<=Len;i++){
            if(height[i]<k) top=tot=0;
            else{
                ll cnt=0;
                if(sa[i-1]<=len) cnt++,tot+=height[i]-k+1;
                while(top>0&&st[top-1][0]>=height[i]){
                    top--;
                    tot-=st[top][1]*(st[top][0]-height[i]);
                    cnt+=st[top][1];
                }
                st[top][0]=height[i];st[top++][1]=cnt;
                if(sa[i]>len) ans+=tot;
            }
        }
        //b扫a
        for(int i=1;i<=Len;i++){
            if(height[i]<k) top=tot=0;
            else{
                ll cnt=0;
                if(sa[i-1]>len) cnt++,tot+=height[i]-k+1;
                while(top>0&&st[top-1][0]>=height[i]){
                    top--;
                    tot-=st[top][1]*(st[top][0]-height[i]);
                    cnt+=st[top][1];
                }
                st[top][0]=height[i];st[top++][1]=cnt;
                if(sa[i]<=len) ans+=tot;
            }
        }
        printf("%lld\n",ans);
    }
}

7）有n个串，求最长子串，它的子串或者反串都在n个字符串中出现过
	只需要将正串和反串都加入后缀数组，然后计算即可。
	int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        int left=1,right=100,len=1,sp=120;
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            int l=strlen(str);
            right=min(right,l);
            for(int j=0;j<l;j++) {
                mark[len] =2*i-1; s[len++] = str[j]-'0'+1;
            }
            s[len++]=sp++;
            for(int j=l-1;j>=0;j--) {
                mark[len] =2*i; s[len++] = str[j]-'0'+1;
            }
            s[len++]=sp++;
        }
        len--;
        DA(s,len,sp++);
        while(left<=right){
            int mid=(left+right)>>1;
            if(isOK(mid,len,sp)) left=mid+1;
            else right=mid-1;
        }
        printf("%d\n",right);
    }


后缀自动机：
    一个子串，它在原串中可能出现在若干的位置。而一个子串p出现的这些位置的右端点标号组成的集合，我们称之为 endpos(p)
  1.如果两个子串的endpos相同，则其中子串一个必然为另一个的后缀
  2.对于任意两个子串t和p(len_t<=len_p)，要么endpos(p)∈endpos(t),要么endpos(t) ∩ endpos(p)= ∅
  3.对于endpos相同的子串，我们将它们归为一个endpos等价类。对于任意一个endpos等价类，将包含在其中的所有子串依长度从大
到小排序，则每一个子串的长度均为上一个子串的长度减 1，且为上一个子串的后缀（简单来说，一个endpos等价类内的串的长度连续）
  4.endpos等价类个数的级别为O(n)
  5.一个类a中，有最长的子串，也有最短的子串，我们称最长子串的长度为len(a)，最短子串长度为minlen(a)。对于存在父子关系的两个类，
设fa(a)表示类a的父亲（也是一个类）。则：len(fa(a))+1=minlen(a)
  6.后缀自动机的边数为O(n)

后缀自动机的性质：
  1.有一个源点，边代表在当前字符串后增加一个字符。
  2.每个点代表一个endpos等价类，到达一个点的路径形成的子串必须属于此点的类。
  3.点之间有父子关系，到达点i的所有字符串的长度都必然大于到达fa(i)的所有字符串的长度，且到达 fa(i)的任意一字符串必为到达i的任
意一字符串的后缀。
  4.每个节点都代表不同的endpos等价类,longest[i]-minlen[i]+1表示其中的字符串个数,每个节点所包含的字符串都不相同,且有满足
len(fa(a))+1=minlen(a),因此每个节点只需要记录最长的len[i]即可,最小值只需要找父节点来确定。
  5.数组要开两倍

学习文章：hihocoder里面关于后缀自动机讲解

应用：

1、求一个字符串中子串*子串个数的最大值,其中个数要大于1
代码：
void solve(){
    ll ans=0;
    for(int i=1;i<=tot;i++) c[len[i]]++;
    for(int i=1;i<=tot;i++) c[i]+=c[i-1];
    for(int i=1;i<=tot;i++) rk[c[len[i]]--]=i;
    for(int i=tot;i>=1;i--){
        int p = rk[i];
        sz[fa[p]]+=sz[p];
        if(sz[p]>1)
            ans=max(ans,(ll)sz[p]*len[p]);
    }
    printf("%lld\n",ans);
}

2、求一个字符串中长度大于等于m的个数总和
void solve(){
    ll ans=0;
    for(int i=tot;i>=1;i--){
        if(len[i]<m)
            continue;
        else{
            ans+=(len[i]-max(m,len[fa[i]]+1)+1);
        }
    }
    printf("%lld\n",ans);
}

3、求两个字符串的最长公共子串
方法1:建立两个后缀自动机,然后dfs(1,1,0),第一个参数表示sam1的节点,第二个参数是sam2的节点,第三个参数是公共长度
方法2:建立一个后缀自动机,然后将另外一个字符串进行沿点搜索
void query(char *s){
    int ret=0,p=1,nowlen=0;
    int n=strlen(s);
    for(int i=0;i<n;i++){
        int ch=s[i]-'a';
        if(nx[p][ch]){p=nx[p][ch];ret=max(ret,++nowlen);continue;}
        //如果没有匹配成功则p=fa[p],保证endpos一样，有满足min{p}=max{fa[p]}+1
        //因为p节点都是fa[p]前面加一个字母而来的,所以回去父节点保证了以i为点的匹配最长
        while(p&&!nx[p][ch]) p=fa[p];
        if(!p) nowlen=0,p=1;
        else{
			//注意不可以p=nx[p][c]; nowlen=len[fa[p]]+1; 因为fa和nx数组并不是相互映射的关系 
            ret=max(ret,nowlen=len[p]+1); p=nx[p][ch];
        }
    }
        printf("%d\n",ret);
}

4、给定两个字符串，求出在两个字符串中各取出一个子串使得这两个子串相同的方案数。两个方案不同当且仅当这两个子串中有一个位置不同。
方法一：先建立对一串建立后缀自动机,然后操作如下：
inline void topsort(){
    for(int i=1;i<=tot;i++) c[len[i]]++;
    for(int i=1;i<=tot;i++) c[i]+=c[i-1];
    for(int i=1;i<=tot;i++) rk[c[len[i]]--]=i;
    for(int i=tot;i>=1;i--){int p=rk[i]; sz[fa[p]]+=sz[p];}
	//表示状态转移到p节点时，dp[p]能新增多少答案
    for(int i=1;i<=tot;i++){
        int p=rk[i];dp[p]=dp[fa[p]]+sz[p]*(len[p]-len[fa[p]]);
    }
}

inline void solve(char *s){
    ll ret=0;
    int p=1,nowlen=0;
    int n=strlen(s);
    for(int i=0;i<n;i++){
        int c=s[i]-'a';
        if(nx[p][c]){
            p=nx[p][c]; nowlen++; ret+=dp[fa[p]]+sz[p]*(nowlen-len[fa[p]]);
            continue;
        }
        for(;p&&!nx[p][c];p=fa[p]);
        if(!p) p=1,nowlen=0;
        else{
            nowlen=len[p]+1;
            p=nx[p][c];
            ret+=dp[fa[p]]+sz[p]*(nowlen-len[fa[p]]);
        }
    }
    printf("%lld\n",ret);
}

5、给定一个字符串,现在想要构造此字符串,增加任意一个字符串,需要花费p元,从之前任意已经生成子串中增加为q,求最小花费
    对于i从小到大处理，维护使得s[j:i]∈s[1:j−1]的最小的j，那么记f[i]为输出前i个字符的最小代价，则f[i]=min{f[i−1]+p,f[j−1]+q}。 
用SAM维护s[1:j−1]，若s[1:j−1]中包含s[j:i+1]，即加入第 i + 1 个字符仍然能复制，就不需要做任何处理。否则，重复地将第 j 个字符加入
后缀自动机并j=j+1，相应维护s[j:i+1]在后缀自动机上新的匹配位置，直到s[j,i + 1]∈s[1,j −1]。
class SuffixAutoMaton{
public:
    int last,tot,p;
    int nx[N<<1][dif],fa[N<<1],len[N<<1];
    void init(){
        last=tot=1; p=1;
        fa[1]=len[1]=0;
        memset(nx[1],0, sizeof(nx[1]));
    }

    inline int match(char ch){
        return nx[p][ch-'a'];
    }

    inline void withdraw(int l){
        while(p!=0&&len[fa[p]]>=l) p=fa[p];
        if(p==0) p=1;
    }

    void transfer(int l,int ch){
        p=nx[p][ch];
        if(p==0) p=1;
        withdraw(l);
    }

    inline void insert(int c){
        int p=last,np=++tot;
        memset(nx[tot],0, sizeof(nx[tot]));
        last=np; len[np]=len[p]+1;
        for(;p&&!nx[p][c];p=fa[p]) nx[p][c]=np;
        if(!p) fa[np]=1;
        else{
            int q=nx[p][c];
            if(len[p]+1==len[q]) fa[np]=q;
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                memcpy(nx[nq],nx[q], sizeof(nx[q]));
                fa[nq]=fa[q]; fa[q]=fa[np]=nq;
                for(;nx[p][c]==q;p=fa[p])
                    nx[p][c]=nq;
            }
        }
    }

}SAM;


void solve(){
    SAM.init();
    SAM.insert(s[0]-'a');
    dp[0]=p;
    int l=1,r=0;
    for(int i=1;i<n;i++){
        ++r;
        dp[i]=dp[i-1]+p;
        while( ( !SAM.match(s[i]) || r-l+1>(i+1)/2 ) && l<=r ){
            SAM.insert(s[l++]-'a');
            SAM.withdraw(r-l);
        }
        SAM.transfer(r-l+1,s[i]-'a');
        if(l<=r){
            dp[i]=min(dp[i],dp[i-(r-l+1)]+q);
        }
    }
    printf("%lld\n",dp[n-1]);
}

6、小Hi发现旋律可以循环，每次把一段旋律里面最前面一个音换到最后面就成为了原旋律的“循环相似旋律”，还可以对“循环相似旋律”进
行相同的变换能继续得到原串的“循环相似旋律”。小Hi对此产生了浓厚的兴趣，他有若干段旋律，和一部音乐作品。对于每一段旋律，他想
知道有多少在音乐作品中的子串（重复便多次计）和该旋律是“循环相似旋律”。

输入：
第一行，一个由小写字母构成的字符串S，表示一部音乐作品。字符串S长度不超过100000。第二行，一个整数N，表示有N段旋律。接下来N行，
每行包含一个由小写字母构成的字符串str，表示一段旋律。所有旋律的长度和不超过100000。

abac
3
a
ab
ca

输出：
输出共N行，每行一个整数，表示答案。
2
2
1

//将字符串s->s+s,然后进入处理
void query(char *s){
    int n=strlen(s),p=1,nowlen=0,limit=n/2;
    memset(vis,0, sizeof(bool)*(tot+1));
    ll ret=0;
    for(int i=0;i<n-1;i++){
        int c=s[i]-'a';
        if(nowlen==limit&&nx[p][c]){
            nowlen++;p=nx[p][c];
            if(nowlen>len[fa[p]]+1) nowlen--;
            else{
				nowlen--; p=fa[p];
            }
        }else{
            if(nx[p][c]){
                nowlen++;p=nx[p][c];
            }else {
                while (p && !nx[p][c]) p = fa[p];
                if (!p) {
                    p = 1;nowlen = 0;
                } else {
                    nowlen = len[p] + 1;p = nx[p][c];
                }
            }
        }
        if(nowlen==limit&&!vis[p]){
            ret+=sz[p];vis[p]=1;
        }
    }
    printf("%lld\n",ret);
 }
 
7、对于一个给定长度为N的字符串，求它的第K小子串是什么。
两个整数T和K，T为0则表示不同位置的相同子串算作一个。T=1则表示不同位置的相同子串算作多个。

思路：
	建立后缀自动机，然后进行记忆化搜索，用dp[i]表示以i为节点的子树所包含的子串个数。

代码：
//先记忆化搜索，得到以u为根节点的子树所包含的子串数
void dfs(int u){
    dp[u]=sz[u];
    for(int i=0;i<26;i++){
        int v=nx[u][i];
        if(!v) continue;
        if(!dp[v]) dfs(v);
        dp[u]+=dp[v];
    }
}

//对答案进行计算
void DFS(int u,ll k){
    if(sz[u]>=k) return;
    k-=sz[u];
    for(int i=0;i<26;i++){
        int v=nx[u][i];
        if(!v) continue;
        if(dp[v]>=k){
            printf("%c",i+'a');
            DFS(v,k); return;
        }else k-=dp[v];
    }
}

void query(int t,ll k){
    topu(t); sz[1]=0; dfs(1);
    if(dp[1]<k){
        printf("-1\n");return;
    }
    DFS(1,k);
    printf("\n");
}

8、给出n个串，求这个n个串的最长公共子串，1≤n≤10,|s|≤1e5
对第一个串建立一个后缀自动机，然后用剩余n-1个串进行匹配，设mlen[i]表示i节点，n-1个串匹配长度的最大值中的最小值
那么最后答案就是遍历所有节点的mlen,最大值即为答案。其中需要注意的是如果i节点匹配成功，那么其父节点的最大值为其父节点长度

代码：
bool Update(){
    if(scanf("%s",s)!=1) return 0;
    memset(clen,0, sizeof(int)*(tot+1));
    int n=strlen(s),nowlen=0,p=1;
	//进行节点匹配，clen[i]表示当前节点匹配的最大值
    for(int i=0;i<n;i++){
        int c=s[i]-'a';
        if(nx[p][c]){
            p=nx[p][c];nowlen++;
        }else{
            while(p&&!nx[p][c]) p=fa[p];
            if(!p){
                p=1;nowlen=0;
            }else{
                nowlen=len[p]+1;p=nx[p][c];
            }
        }
        clen[p]=max(clen[p],nowlen);
    }
	//更新mlen[i],并更新父节点的clen
    for(int i=tot;i>=1;i--){
        int p=rk[i];
        mlen[p]=min(mlen[p],clen[p]);
        if(clen[p]&&fa[p]) clen[fa[p]]=len[fa[p]];
    }
    return 1;
}

9、给定一个长度为n的字符串s，令Ti表示它从第i个字符开始的后缀，求sigma(1<=i<j<=n)len[i]+len[j]-2*lcp(Ti,Tj)的和
其中,len[i]表示字符串i的长度,lcp(a,b)表示字符串a和字符串b的最长公共前缀

思路：
首先把字符串反过来，前缀变后缀，然后建立后缀自动机。我们发现parent树即后缀树，它是不断在前面加字符串而导致endpos集
分裂，假设一个跟节点为z，两个子节点为x,y，那么两者lca的节点表示的长度是他们的最长匹配子串,因此我们只需要对每个节点进行
计算即可。

代码：
void query(ll n){
    ll ret=(n-1)*n*(n+1)/2;
    for(int i=1;i<=tot;i++) c[len[i]]++;
    for(int i=1;i<=tot;i++) c[i]+=c[i-1];
    for(int i=1;i<=tot;i++) rk[c[len[i]]--]=i;
    for(int i=tot;i>=1;i--){
        int p=rk[i]; sz[fa[p]]+=sz[p];
        ret-=(len[p]-len[fa[p]])*sz[p]*(sz[p]-1);
    }
    printf("%lld\n",ret);
}

广义后缀自动机：

1、神奇的是小Hi发现了一部名字叫《十进制进行曲大全》的作品集，顾名思义，这部作品集里有许多作品，但是所有的作品有一个共同特征：
只用了十个音符，所有的音符都表示成0-9的数字。现在小Hi想知道这部作品中所有不同的旋律的“和”（也就是把串看成数字，在十进制下的求和，
允许有前导0）。答案有可能很大，我们需要对（10^9 + 7)取模。

输入：
2
101
09

输出：
131

思路：
	建立广义后缀自动机，然后进行拓扑排序，累计答案即可。

ll dp[N<<1],cnt[N<<1];
int rk[N<<1],c[N<<1];

void query(){
    for(int i=1;i<=tot;i++) c[len[i]]++;
    for(int i=1;i<=tot;i++) c[i]+=c[i-1];
    for(int i=1;i<=tot;i++) rk[c[len[i]]--]=i;
    cnt[1]=1;
	//正向扫可以得到以1节点拓扑排序
    for(int i=1;i<=tot;i++){
        int u=rk[i];
        for(int j=0;j<10;j++){
            int v=nx[u][j];
            if(!v) continue;
            cnt[v]=(cnt[v]+cnt[u])%mod;
            dp[v]=(dp[v]+10*dp[u]%mod+cnt[u]*j%mod)%mod;
        }
    }
    ll ret=0;
    for(int i=2;i<=tot;i++) ret=(ret+dp[i])%mod;
    printf("%lld\n",ret);
}


