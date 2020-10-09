1、离散化
for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    b[i] = a[i];
}
sort(b + 1, b + 1 + n);
m = unique(b + 1, b + 1 + n) - b - 1;
for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
}
