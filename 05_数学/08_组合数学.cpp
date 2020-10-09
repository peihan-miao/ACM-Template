1、打表求组合数
c[n][m],n>=m
for(int i=0;i<=n;i++){
    c[i][0]=1;
    for(int j=1;j<=i;j++){
        c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
}

2、预处理，调用C(int n, int m)
ll dp[N], fac[N], inv[N];

ll quick(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return res;
}

void init(int n) {
	fac[0] = 1, fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = fac[i - 1]*i % mod;
	}
	inv[n] = quick(fac[n], mod - 2);
	for (int i = n-1; i >= 0 ; i--)inv[i] = inv[i+1]*(i+1) % mod;
}

//n大
ll C(int n, int m) {
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
