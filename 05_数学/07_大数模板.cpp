0、快速幂
ll quick(ll a,ll b){
    ll ret=1;a%=mod;
    while(b){
        if(b&1) ret=ret*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

1、求phi模板
ll phi(ll m) {
    ll ans = 1;
    for (ll i = 2; i*i <= m; i++) {
        if (m%i == 0) {
            m /= i;
            ans *= i - 1;
            while (m%i == 0) {
                m /= i;
                ans *= i;
            }
        }
    }
    if (m > 1) ans *= m - 1;
    return ans;
}

2、大数取模模板
ll Mod(string a,ll b){
    ll len=a.length()-1;
    ll ans=0;
    for(int i=0;i<=len;i++)
        ans=(ans*10+(a[i]-'0')%b)%b;
    return ans;
}

3、大数相乘模板
string Mul(string s,int x){
    reverse(s.begin(),s.end());
    int cmp=0;
    for(int i=0;i<s.size();i++){
        cmp=(s[i]-'0')*x+cmp;
        s[i]=(cmp%10+'0');
        cmp/=10;
    }
    while(cmp){
        s+=(cmp%10+'0');
        cmp/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

4、大数相加模板：
string sum(string s1,string s2){
    if(s1.length()<s2.length()) swap(s1,s2);
    int i,j;
    for(i=s1.length()-1,j=s2.length()-1;i>=0;i--,j--){
        s1[i]=char(s1[i]+(j>=0?s2[j]-'0':0));   //注意细节
        if(s1[i]-'0'>=10){
            s1[i]=char((s1[i]-'0')%10+'0');
            if(i) s1[i-1]++;
            else s1='1'+s1;
        }
    }
    return s1;
}

5、__int128 2^128次使用,只能在Linux下使用
inline __int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch<'0' || ch>'9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0'&&ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

其他时候可以使用printf,cin,cout


6、快速乘
//O(1)快速乘
inline LL quick_mul(LL x,LL y,LL MOD){
    x=x%MOD,y=y%MOD;
    return ((x*y-(LL)(((long double)x*y+0.5)/MOD)*MOD)%MOD+MOD)%MOD;
}
//O(log)快速乘
inline LL quick_mul(LL a,LL n,LL m){
    LL ans=0;
    while(n){
        if(n&1) ans=(ans+a)%m;
        a=(a<<1)%m;
        n>>=1;
    }
    return ans;
}

7、高精度相加
struct BigInteger {
	static const int BASE = 10000; //高进制
	static const int WIDTH = 4; //高进制位数
	vector<int>s;
	BigInteger() {}
	BigInteger(long long num) { // 构造函数
		*this = num;
	}
	//赋值
	BigInteger operator = (long long num) {
		s.clear();
		do {
			s.push_back(num%BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}
	//+
	BigInteger operator + (BigInteger& b) {
		BigInteger c;
		c.s.resize(max(s.size(), b.s.size()) + 1);
		for (int i = 0; i < c.s.size() - 1; i++) {
			int tmp1, tmp2;
			if (i >= s.size())tmp1 = 0;
			else tmp1 = s[i];
			if (i >= b.s.size())tmp2 = 0;
			else tmp2 = b.s[i];
			c.s[i] = tmp1 + tmp2;
		}
		for (int i = 0; i < c.s.size() - 1; i++) {
			c.s[i + 1] += c.s[i] / BASE;
			c.s[i] %= BASE;
		}
		while (c.s.back() == 0 && c.s.size() > 1)c.s.pop_back();
		return c;
	}
	void operator += (BigInteger& b) {
		*this = *this + b;
	}
};

BigInteger dp[55][265];

ostream& operator << (ostream& output, const BigInteger& x) {
	output << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--) {
		char buf[20];
		sprintf(buf, "%04d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++)output << buf[j];
	}
	return output;
}