1、dinic
struct Edge {
	int e, nxt;
	ll v;

	Edge() = default;

	Edge(int a, ll b, int c = 0) : e(a), v(b), nxt(c) {}

	bool operator<(const Edge& a) const {
		return (a.v == v ? e < a.e : v < a.v);
	}

	bool operator>(const Edge& a) const {
		return (a.v == v ? e > a.e : v > a.v);
	}
};

struct Graph {
	Edge eg[M];
	int head[N];
	int cnt;

	void init(int n) {
		memset(head, -1, sizeof(int) * ++n);
		cnt = 0;
	}

	inline void addEdge(int x, int y, ll v) {
		eg[cnt] = Edge(y, v, head[x]);
		head[x] = cnt++;
	}
} gh;


struct Dinic {
	Graph gh;
	// 点的范围[0, n)
	int n;
	// 弧优化
	int cur[N], dis[N];

	Dinic() {};

	// 设置N
	void init(int _n) {
		n = _n + 1;
		gh.init(n);
	}

	// 加流量
	void addFlow(int x, int y, ll f) {
		gh.addEdge(x, y, f);
		gh.addEdge(y, x, 0);
	}

	bool bfs(int s, int e) {
		memset(dis, -1, sizeof(int) * n);
		int q[N];
		int l, r;
		l = r = 0;
		dis[s] = 0;
		q[r++] = s;
		while (l < r) {
			int f = q[l++];
			for (int i = gh.head[f]; ~i; i = gh.eg[i].nxt) {
				if (gh.eg[i].v > 0 && dis[gh.eg[i].e] == -1) {
					dis[gh.eg[i].e] = dis[f] + 1;
					q[r++] = gh.eg[i].e;
				}
			}
		}
		return dis[e] > 0;
	}

	ll dfs(int s, int e, ll mx) {
		if (s == e || mx == 0) {
			return mx;
		}
		ll flow = 0;
		for (int& k = cur[s]; ~k; k = gh.eg[k].nxt) {
			auto& eg = gh.eg[k];
			ll a;
			if (eg.v > 0 && dis[eg.e] == dis[s] + 1 && (a = dfs(eg.e, e, min(eg.v, mx)))) {
				eg.v -= a;
				gh.eg[k ^ 1].v += a;
				flow += a;
				mx -= a;
				if (mx <= 0) break;
			}
		}
		return flow;
	}

	ll max_flow(int s, int e) {
		ll ans = 0;
		while (bfs(s, e)) {
			memcpy(cur, gh.head, sizeof(int) * n);
			ans += dfs(s, e, INF);
		}
		return ans;
	}
} dinic;