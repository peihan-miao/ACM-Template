1、并查集模板
int find(int x){
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

2、带权并查集
int find(int x){
    if (x != parent[x]){
        int t = parent[x];
        parent[x] = find(parent[x]);
        value[x] += value[t];
    }
    return parent[x];
}

void Merge(int x,int y,int v){
    int fx = find(x);
    int fy = find(y);
    if (fx != fy){
        parent[fx] = fy;
        value[fx] = -value[x] + value[y] + v;
    }
}