Palindromic Tree，译名为“回文树”，是一种专门处理回文串的数据结构，类似于Manachar算法，但更为强大。是由两颗分别存储偶数回文
串树和存储奇数回文串树组成，每个节点代表母串的回文串，两树之间中用fail指针连接。

假设我们有一个串S，S下标从0开始，则回文树能做到如下几点：
1.求串S前缀0~i内本质不同回文串的个数（两个串长度不同或者长度相同且至少有一个字符不同便是本质不同）
2.求串S内每一个本质不同回文串出现的次数
3.求串S内回文串的个数（其实就是1和2结合起来）
4.求以下标i结尾的回文串的个数

应用：

1、求最长回文子串
    回文自动机中节点长点最长的即是答案

2、求字符串中本质不同回文子串的数量
    回文自动机中除了0、1节点所产生的节点数量即为本质不同回文子串数量。

3、求两个字符串有多少回文子串能配对的数量
    For example, (1, 3, 1, 3) and (1, 3, 3, 5) are both considered as a valid common palindrome substring
between “aba” and “ababa”. aba能匹配两次.
    建成两颗回文树后,只需要dfs(0,0)偶子树和dfs(1,1)奇子树,只要遍历到两个点同时存在,则数量ans += 1ll*pt1.cnt[to1]*pt2.cnt[to2];

4、求一个字符串求最长双回文子串T,即可将T分为两部分X,Y,(|X|,|Y|≥1)且X和Y都是回文串。
    只需要前后跑一次回文自动机,l[i]表示从左到i所形成的最长回文串,r[i]表示从i到右所形成的的最长回文串,遍历一遍字符串即可得到答案。
    
5、求一个字符串每个前缀中有多少个本质不同的回文串
   每个字母插入时,统计一遍现在回文自动机中所产生的节点总数即可.

6、求一个字符串(1≤T≤10, 1≤length≤1000, 1≤Q≤100000, 1≤l≤r≤length)，区间[l,r]中本质不同的回文串数
     考虑到1≤length≤1000,我们可以强行打表记录ans[i][j],表示[i,j]之间回文子串个数,而不是在Q中每次查询情况.

7、定义合法(x,y)为两个不相交的回文串,求个数.
   解释：aca，S1=T[0,0],S2=T[0,2],S3=T[1,1],S4=T[2,2],其中(S1,S3) (S1,S4) (S3,S4)为合法对
   从回文自动机的fail边可知：边是连接一个字符串与另一个字符串的最长后缀回文子串,因此可以查询一个点到0点长度即加入一个点后
所增加的回文串,再反着打一次后缀和,结果相乘即是答案。

int getsum(int from){
    int res=1,x=from;
    if(vis[x])
        return vis[x];
    if(pt.fail[from]!=0&&pt.fail[from]!=1){
        int to=pt.fail[x];
        res+=vis[to];
    }
    vis[from]=res;
    return vis[from];
}

int main() {
    while(scanf("%s",str)==1) {
        int len = strlen(str);
        pt.init();
        memset(vis,0, sizeof(int)*(len+1));
        for(int i=0;i<len;i++){
            pt.insert(str[i]-'a');
            l[i]=getsum(pt.last);
        }
        memset(vis,0, sizeof(int)*(len+1));
        pt.init();
        r[len]=0;
        for(int i=len-1;i>=1;i--){
            pt.insert(str[i]-'a');
            r[i]=r[i+1]+getsum(pt.last);
        }
        ll ans=0;
        for(int i=0;i<len-1;i++){
            ans+=l[i]*r[i+1];
        }
        printf("%lld\n",ans);
    }
    return 0;
}

8、有奇数个，并且他们手中的牌子所写的字母，从左到右和从右到左读起来一样，那么这一段女生就被称作和谐小群体。
现在想找出所有和谐小群体，并且按照女生的个数降序排序之后，前K个和谐小群体的女生个数的乘积是多少。
    显然回文自动机上节点的标记就是他们出现的时间,以及len可以记录,因此只需要dfs(1)一遍奇回文树,即可得到每个节点的
长度和该节点表示回文串出现的次数,然后排序扫一遍即可。

9、three tuple (i,j,k) satisfy 1≤i≤j<k≤length(S), S[i..j] and S[j+1..k] are all palindrome strings. 
wants to know the sum of i*k of all required three tuples. The answer may be very large, please output 
the answer mod 1000000007.
    设left[i]为以i为点从右往左的sigma(j)的和,right[i]以i为点从左往右的sigma(k)的和,因此需要dfs辅助记录点数和长度
然后sigma(left[i]*right[i+1])即是答案.

void Update(int from){
    int res=1,res2=pt.len[from];
    if(vis[from])
        return;
    if(pt.fail[from]!=0&&pt.fail[from]!=1){
        int to = pt.fail[from];
        res+=vis[to];
        res2+=ls[to];
        res%=mod;
        res2%=mod;
    }
    vis[from]=res;
    ls[from]=res2;
    return;
}

9、实现可前后插入字符,查询当前有多少个本质不同回文串,已经生成回文串个数
	给你n次操作，如果为1，则在字符串后面插入一个字符，如果为2，则在字符串前面插入一个字符，如果为3，则输出当前的字符
串中的本质不同的回文串的个数，如果为4，则输出字符串的回文串的个数。

typedef pair<int, int> pii;
typedef long long ll;
const double eps = 1e-6;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll mod = 1000000007;
const int N = 2e5 + 10;
const int M = 2e5 + 10;

const double PI = acos(-1.0);

const int dif = 26;
int n, q;
int op;
char str[5];


class PalindromicTree{
public:
    int nx[N][dif],fail[N],len[N],num[N];
    int tot[2],p,last[2],s[N];
    int newnode(int l){
        memset(nx[p],0, sizeof(nx[p]));
        len[p]=l;
        num[p]=0;
        return p++;
    }
    void init(int x){
        last[0]=last[1]=p=0;
        tot[0]=x;tot[1]=x-1;
        fail[0]=fail[1]=1;
        memset(s,-1, sizeof(s));
        newnode(0);
        newnode(-1);
    }
    int getfail(int x,int tag){
        if(!tag){
            while(s[tot[tag]+len[x]+1]!=s[tot[tag]])
                x=fail[x];
        }else{
            while(s[tot[tag]-len[x]-1]!=s[tot[tag]])
                x=fail[x];
        }
        return x;
    }
    int insert(int x,int tag){
        if(!tag)
            s[--tot[0]]=x;
        else
            s[++tot[1]]=x;
        int cur = getfail(last[tag],tag);
        int now = nx[cur][x];
        if(!now){
            now = newnode(len[cur]+2);
            fail[now]=nx[getfail(fail[cur],tag)][x];
            nx[cur][x]=now;
            num[now]+=num[fail[now]]+1;
        }
        last[tag]=nx[cur][x];
        if(len[last[tag]]==tot[1]-tot[0]+1)
            last[tag^1]=last[tag];
        return num[last[tag]];
    }
}pt;


int main() {
    while(scanf("%d",&q)==1){
        pt.init(q);
        ll ans=0;
        while(q--){
            scanf("%d",&op);
            if(op==1){
                scanf("%s",str);
                ans+=pt.insert(str[0]-'a',0);
            }else if(op==2){
                scanf("%s",str);
                ans+=pt.insert(str[0]-'a',1);
            }else if(op==3){
                printf("%d\n",pt.p-2);
            }else{
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}

10、两个相交的回文串为一对,求一个字符串中有多少对。
    直接求相交非常麻烦,且非常难处理,可以换一个思路,先求总和,以及不会相交的，那么相减即可得到结果。但是内存有限定,因此可以使用
vector进行优化。
class PalindromicTree{
public:
    vector<pii>nx[N];
    int fail[N],len[N],num[N];
    int tot,p,last,s[N];
    int newnode(int l){
        nx[p].clear();
        len[p]=l;
        num[p]=0;
        return p++;
    }
    void init(){
        tot=p=last=0;
        s[0]=-1,fail[0]=1;
        newnode(0);
        newnode(-1);
    }
    int getfail(int x){
        while(s[tot-len[x]-1]!=s[tot])
            x=fail[x];
        return x;
    }

    int is_exist(int p,int c){
        for(auto t:nx[p]){
            if(t.first==c)
                return t.second;
        }
        return 0;
    }

    void insert(int x){
        s[++tot]=x;
        int cur = getfail(last);
        int now = is_exist(cur,x);
        if(!now){
            now = newnode(len[cur]+2);
            fail[now]=is_exist(getfail(fail[cur]),x);
            nx[cur].push_back(make_pair(x,now));
            num[now]=num[fail[now]]+1;
        }
        last=now;
    }
}pt;

11、求一个字符串中有多少子串满足,1.r-l+1==i 2.子串为回文串 3.[l,(l+r)/2]也为回文串
    有可能为答案的是回文自动机上的节点,只需要节点判断是否满足即可,关键在于判断[l,(l+r)/2]也为回文串，可以发现若满足条件三
则前半段和后半段是一样的,因此可以用hash判断前半段和后半段是否相同即可，如果相同则进入计数。
const ull hash1 = 201326611;
const ull hash2 = 50331653;
ull ha[N],pp[N];

ull getha(int l,int r){
    if(l==0)
        return ha[r];
    return ha[r]-ha[l-1]*pp[r-l+1];
}

bool check(int l,int r){
    int len = r-l+1;
    int mid = (l+r)>>1;
    if(len&1)
        return getha(l,mid)==getha(mid,r);
    else
        return getha(l,mid)==getha(mid+1,r);
}

class PalindromicTree{
public:
    int nx[N][dif],fail[N],len[N],cnt[N];
    int tot,p,last,s[N],id[N];
    int newnode(int l){
        memset(nx[p],0, sizeof(nx[p]));
        len[p]=l;
        cnt[p]=0;
        return p++;
    }
    void init(){
        tot=p=last=0;
        s[0]=-1,fail[0]=1;
        newnode(0);
        newnode(-1);
    }
    int getfail(int x){
        while(s[tot-len[x]-1]!=s[tot])
            x=fail[x];
        return x;
    }
    void insert(int x){
        s[++tot]=x;
        int cur = getfail(last);
        int now = nx[cur][x];
        if(!now){
            now = newnode(len[cur]+2);
            fail[now]=nx[getfail(fail[cur])][x];
            nx[cur][x]=now;
        }
        last=nx[cur][x];
        cnt[last]++;
        id[last]=tot;
    }
    void makecnt(){
        for(int i=p-1;i>=2;i--)
            cnt[fail[i]]+=cnt[i];
        for(int i=2;i<p;i++){
            if(check(id[i]-len[i],id[i]-1)){
                ans[len[i]]+=cnt[i];
            }
        }
    }
}pt;

int main(){
    pp[0]=1;
    for(int i=1;i<N;i++)
        pp[i]=hash1*pp[i-1];
    while(scanf("%s",str)==1){
        int len = strlen(str);
        memset(ans,0, sizeof(int)*(len+2));
        pt.init();
        ha[0]=str[0];
        for(int i=0;i<len;i++)
            pt.insert(str[i]-'a');
        for(int i=1;i<len;i++)
            ha[i]=ha[i-1]*hash1+str[i];
        pt.makecnt();
        printf("%d",ans[1]);
        for(int i=2;i<=len;i++)
            printf(" %d",ans[i]);
        printf("\n");
    }
}

12、求一个字符串中所有回文串中,若一个回文串包含另一个回文串,则为为一对,求所有满足情况的对
    先建立回文树,显然每个节点代表一种回文串,我们可以通过dfs进行求取.
void dfs(int x,ll res){
    vector<int>v;
    for(int i=x;i>1;i=fail[i]){
        if(!vis[i]){
            v.push_back(i);
            vis[i]=1;
            res++;
        }else break;
    }
    ans+=res;
    for(int i=0;i<26;i++) if(nx[x][i]) dfs(nx[x][i],res);
    for(auto t:v) vis[t]=0;
}

void solve(){
    ans=2-p;
    dfs(0,0);
    dfs(1,0);
    printf("%lld\n",ans);
}