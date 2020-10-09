求hash值
   hash的特征就是不同的key (就是目标位置)对应的数据不同，所以将字符串转化为数字应该注意一对应， 避免哈希冲突(比如不同字符
串对应了同一个值，但是你的程序还是会判断它们是同一个字符串一般的字符串hash值求法(终于到正题了)给一个字符串从左到右枚举字符
串的每一位，每一个字母直接对应它的ASCII码(就变成int了)，对应好子就把每位加起来， 就输快的冲突子直接相加会冲突，例如ab和ba
,第二串后来的那个a和第一串的前面的a虽然一 个更老一个更年轻，但是它们的作用居然是一样的，这是不符合常识的(我是在说实话)
所以，为了使资质更老的a更显眼，可以在处理之后的那些后代的时候给它乘上一个数base显示它的不同。 如果考虑到每一个字符后面都有
后代的话，那么每处理一个后面的字符， 前面的祖宗们就都会乘上一一个数。容易看出，每个位置都比它后面那个位置多乘了-一次， 这样
就可以显示出各个位置的等级差距了，再结合之前的直接相加，就可以表示出来每一个不同的字符串 了，即:
    val ["abc"] = 'a'*base^2+'b'*base^1+'c'*base^0
    那么对于一个母串，怎么提取它[l, r ]中的hash值呢。我们已经知道了这个串从1到每个位置这一部分的hash值 ，这类似于前缀和，
即hash[r ]-hash[l-1],但是由于对于r位置的hash[r],它前面一部分(即被它包含在内的hash[ 1]部分)被多乘了许多次base，减的时候
应该给hash[ I ]他乘上(换个说法:求出hash[l-1 ]之后，继续向后面走，每走一步都会hash[L-1 ]乘上base,直求到hash[ r ]时已经
乘了(r-I+1)个base了， 实际上hash[r]=hash[l,r]+hash[1-1]*base^(r-l+1)所以答案应该是(多乘了的次数[l,r]区间长度)
val[i,r]=hash[r]-hash[ 1-1 ]*base^(r-l+1)最后，因为乘的base-般很大，所以乘多了容易爆，要取模，为了避免麻烦，一般使用
unsigned long long
Qhash如何支持单点修改?
A可以用线段树维护
要用线段树维护要资瓷区间台并>
hash=左子树hash*(base^右子树size)+右子树hash

struct HASH{
    ull hash1;
    ull p[N],ha[N];
    void init(int n){
        hash1=201326611;//233,50331653
        p[0]=1; ha[0]=0;
        for(int i=1;i<=n;i++)
            p[i]=p[i-1]*hash1;
    }
    //传指针要从s开始，不用s+1
    void build(char *s,int x,int n){
        for(int i=x;i<=n;i++) ha[i]=ha[i-1]*hash1+s[i];
    }
    ull getha(int l,int r){
        return ha[r]-ha[l-1]*p[r-l+1];
    }
    int query(int x,int y){
        int right=n-max(x,y)+1,left=1;
        while(left<=right){
            int mid=(left+right)>>1;
            if(getha(x,x+mid-1)==getha(y,y+mid-1)) left=mid+1;
            else right=mid-1;
        }
        return right;
    }
}hs;

//将可以通过此类方法将二维、三维等压缩到一维ha数组中
int ha[10000007];
ll seed=309989,mod = 9989783;

inline int gethash(ll x,ll y){
    int t=(x*seed+y)%mod;
    return t;
}
