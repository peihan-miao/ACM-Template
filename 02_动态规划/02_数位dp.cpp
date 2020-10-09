int gcd(int a, int b) {
	return b ? gcd(b, a%b) : a;
}

ll dfs(int pos, int tot, int lcm, bool limit) {
	if (pos == 0)
		return (tot%lcm == 0);
	if (!limit&&dp[pos][ha[lcm]][tot] != -1)
		return dp[pos][ha[lcm]][tot];
	ll res = 0;
	int top = limit ? di[pos] : 9;
	for (int i = 0; i <= top; i++) {
		res += dfs(pos - 1, (tot * 10 + i) % mod, i ? i * lcm / gcd(i, lcm) : lcm, i == di[pos] && limit);
	}
	if (!limit)
		dp[pos][ha[lcm]][tot] = res;
	return res;
}

ll solve(ll x) {
	int pos = 0;
	while (x) {
		di[++pos] = x % 10;
		x /= 10;
	}
	return dfs(pos, 0, 1, true);
}