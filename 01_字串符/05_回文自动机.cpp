裸模板
1.len[i]表示编号为i的节点表示的回文串的长度（一个节点表示一个回文串）
2.next[i][c]表示编号为i的节点表示的回文串在两边添加字符c以后变成的回文串的编号（和字典树类似）。
3.fail[i]表示节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串（和AC自动机类似）。
4.cnt[i]表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
5.num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数。
6.last指向新添加一个字母后所形成的最长回文串表示的节点,便于下次insert。
7.s[i]表示第i次添加的字符（一开始设s[0] = -1（可以是任意一个在串s中不会出现的字符））。
8.p表示添加的节点个数。
9.tot表示添加的字符个数。
10.偶子树根节点为0，奇子树根节点为1，fail[0]指向1,len[0]=0,len[1]=-1,now的上一个节点为cur
class PalindromicTree{
public:
    int nx[N][dif],fail[N],len[N],cnt[N],num[N];
    int tot,p,last,s[N];
    int newnode(int l){
        memset(nx[p],0, sizeof(nx[p]));
        len[p]=l;
        cnt[p]=num[p]=0;
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
            num[now]=num[fail[now]]+1;
        }
        last=nx[cur][x];
        cnt[last]++;
    }
    void makecnt(){
        for(int i=p-1;i>=2;i--)
            cnt[fail[i]]+=cnt[i];
    }
}pt;

可以双向增加,查询本质不同回文串个数,已经生成回文串个数
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
        memset(s,-1, sizeof(s));
        last[0]=last[1]=p=0;
        tot[0]=x;tot[1]=x-1;
        fail[0]=fail[1]=1;
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

3、使用vector优化内存
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