1、gcd
ll gcd(ll a,ll b){
    return b>0?gcd(b,a%b):a;
}

 斐波那契数列的最大公约数定理：gcd(F(m),F(n))=F(gcd(m,n))
 F[0]=0,F[1]=1...

2、ex-gcd
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