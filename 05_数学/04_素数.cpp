1、素数筛
//Mark中标记为true的为合数
int prime[N];
bool Mark[N];
int cnt=0;

void Prime(int n){
    for(int i=2;i<=n;i++){
        if(Mark[i]==0)
            prime[cnt++]=i;
        for(int j=0;j<cnt&&prime[j]*i<=n;j++){
            Mark[i*prime[j]]=1;
            if(i%prime[j]==0)
                break;
        }
    }
}

//获得[2,n]的所有最小质因子和，1不为质因子
ll res=0;
int n,cnt;
int prime[N];
bool Mark[N];

void Prime(int n){
    for(int i=2;i<=n;i++){
        if(!Mark[i])
            res+=prime[cnt++]=i;
        for(int j=0,e=n/i;j<cnt&&prime[j]<=e;j++){
            Mark[i*prime[j]]=1;
            res+=prime[j];
            if(i%prime[j]==0) break;
        }
    }
}

//求[2,n]内所有数能分解出的合数因子,复杂度nlogn
void init(int n){
    Prime(n);
    tot=0; memset(head,-1, sizeof(head));
    for(int v=2;v<=n;v++){
        if(!Mark[v]) continue; //若v为合数则可以加入答案
        for(int u=v;u<=n;u+=v){
            add_edge(u,v);
        }
    }
}

//若一个数满足n=ab,a和b不能被平方数整除，除了1，设f(n)为满足对数，比如f(4)=1,2*2,f(6)=4,1*6,6*1,2*3,3*2
//求[1,n]之间f(i)的和，其中n<=2e7
void Prime(int n){
    dp[1]=1;//必须放在第一个
    for(int i=2;i<=n;i++){
        if(Mark[i]==0) {
            prime[cnt++]=i;dp[i]=2;
        }
        for(int j=0;j<cnt&&prime[j]*i<=n;j++){
            int di=i*prime[j];
            Mark[di]=1;
            if(i%prime[j]) dp[di]=dp[i]*2;
            else{
                if((i/prime[j])%prime[j]==0) dp[di]=0;
                else dp[di]=dp[i/prime[j]];
                break;
            }
        }
    }
    for(int i=2;i<=n;i++) dp[i]+=dp[i-1];
}

2、单点判断
bool isPrime(ll num){
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    for (ll i = 5; i*i <= num; i += 6)
        if (num % i == 0 || num % (i+2) == 0)
            return false;
    return true;
}


3、一个素数为P,它之前的素数为Q,求Q!%P的值
int cnt=0;
ll p,q;

bool isPrime(ll num){
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    for (ll i = 5; i*i <= num; i += 6)
        if (num % i == 0 || num % (i+2) == 0)
            return false;
    return true;
}

void extend_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b){
        x = 1, y = 0;
        return;
    }
    else{
        extend_gcd(b, a % b, y, x);
        y -= x * (a / b);
        return;
    }
}

ll inv(ll a, ll n) {
    ll x, y;
    extend_gcd(a,n,x,y);
    x = (x % n + n) % n;
    return x;
}

int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%lld",&p);
        q=p-1;
        while(!isPrime(q))
            q--;
        ll top = p-q-1;
        if(top==0)
            top=1;
        ll res=1;
        for(ll i=1;i<=top;i++){
            res=res*i%p;
        }
        res = inv(res,p);
        printf("%lld\n",res);
    }
}

4、
LL Mult_Mod(LL a,LL b,LL m)//res=(a*b)%m
{
    a%=m;
    b%=m;
    LL res=0;
    while(b)
    {
        if(b&1)
            res=(res+a)%m;
        a=(a<<=1)%m;
        b>>=1;
    }
    return res%m;
}
LL Pow_Mod(LL a, LL b, LL m)//res=(a^b)%m
{
    LL res=1;
    LL k=a;
    while(b)
    {
        if((b&1))
            res=Mult_Mod(res,k,m)%m;

        k=Mult_Mod(k,k,m)%m;
        b>>=1;
    }
    return res%m;
}

bool Witness(LL a,LL n,LL x,LL sum)
{
    LL judge=Pow_Mod(a,x,n);
    if(judge==n-1||judge==1)
        return 1;

    while(sum--)
    {
        judge=Mult_Mod(judge,judge,n);
        if(judge==n-1)
            return 1;
    }
    return 0;
}

bool Miller_Rabin(LL n)
{
    if(n<2)
        return 0;
    if(n==2)
        return 1;
    if((n&1)==0)
        return 0;

    LL x=n-1;
    LL sum=0;
    while(x%2==0)
    {
        x>>=1;
        sum++;
    }


    int times=20;
    for(LL i=1;i<=times;i++)
    {
        LL a=rand()%(n-1)+1;//取与p互质的整数a
        if(!Witness(a,n,x,sum))//费马小定理的随机数检验
            return 0;
    }
    return 1;
}
LL GCD(LL a,LL b)
{
    return b==0?a:GCD(b,a%b);
}
LL Pollard_Rho(LL n,LL c)//寻找一个因子
{
    LL i=1,k=2;
    LL x=rand()%n;//产生随机数x0(并控制其范围在1 ~ x-1之间)
    LL y=x;
    while(1)
    {
        i++;
        x=(Mult_Mod(x,x,n)+c)%n;
        LL gcd=GCD(y-x,n);

        if(gcd<0)
            gcd=-gcd;

        if(gcd>1&&gcd<n)
            return gcd;

        if(y==x)
            return n;

        if(i==k)
        {
            y=x;
            k<<=1;
        }
    }
}

int total;//因子的个数
LL factor[N];//存储所有因子的数组，无序的
void Find_fac(LL n)//对n进行素因子分解，存入factor
{
    if(Miller_Rabin(n))//是素数就把这个素因子存起来
    {
        factor[++total]=n;
        return;
    }

    long long p=n;
    while(p>=n)//值变化，防止陷入死循环k
        p=Pollard_Rho(p,rand()%(n-1)+1);

    Find_fac(n/p);
    Find_fac(p);
}