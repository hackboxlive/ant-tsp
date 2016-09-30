struct edge {
	int u, v, w;
	double pheromone;
	double lazy;
	edge(int a, int b, int c, double d) {
		u = a, v = b, w = c;
		pheromone = d;
		lazy = 0;
	}
};

struct cmp {
	bool operator() (const pii& a, const pii& b) {
		return a.second > b.second;
	}
};
