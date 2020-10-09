1、
friend bool operator< (node a,node b){
		return a.step>b.step;
}
优先队列将步数较小的放在前面

2、
do {
    if (check()) {
	......
    }
} while (next_permutation(a + 1, a + 1 + n));
全排列函数，注意最初需要将a从小到大进行排序。


矩阵模板：
mat Mul(mat a, mat b) {
	mat c;
	for (int i = 0; i < ac.tot; i++) {
		for (int j = 0; j < ac.tot; j++) {
			ull sum = 0;
			for (int k = 0; k < ac.tot; k++)
				sum = sum + a.arr[i][k] * b.arr[k][j];
			c.arr[i][j] = sum;
		}
	}
	return c;
}

mat quick(mat a, int b) {
	mat res = ones;
	while (b) {
		if (b & 1)
			res = Mul(res, a);
		b >>= 1;
		a = Mul(a, a);
	}
	return res;
}

mat add(mat a, mat b) {
	mat c;
	for (int i = 0; i < ac.tot; i++) {
		for (int j = 0; j < ac.tot; j++) {
			c.arr[i][j] = a.arr[i][j] + b.arr[i][j];
		}
	}
	return c;
}

求：A^1+A^2+A^3+A^4...+A^K
mat getsum(int k) {
	if (k == 1)
		return A;
	mat t = getsum(k / 2);
	if (k & 1) {
		mat reminder = quick(A, k);
		mat cur = quick(A, (k - 1) / 2);
		t = add(t, Mul(cur, t));
		t = add(reminder, t);
	}
	else {
		mat cur = quick(A, k / 2);
		t = add(t, Mul(cur, t));
	}
	return t;
}