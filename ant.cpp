#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#include "ant.hpp"
#include "graph.hpp"
const int inf = 1e9 + 7;

vector<pii> graph[100100];
vector<edge> edges;
int dist[1000][1000];
double pheromone[1001][1001];
double lazy[1001][1001];
int n, m;

void print(vector<int>& v) {
	for (auto x: v) {
		printf("%d ", x);
	}
	printf("\n");
}

void singlesource(int u) {
	for (int i = 1; i <= n; i++)
		dist[u][i] = inf;
	priority_queue<pii, vector<pii>, cmp> pq;
	dist[u][u] = 0;
	pq.push(make_pair(u, 0));
	while (!pq.empty()) {
		int v = pq.top().first, d = pq.top().second;
		pq.pop();
		for (auto p: graph[v]) {
			int nxt = p.first, w = p.second;
			if (dist[u][nxt] > dist[u][v] + w) {
				dist[u][nxt] = dist[u][v] + w;
				pq.push(make_pair(nxt, dist[u][nxt]));
			}
		}
	}
}


void allpairs() {
	for (int u = 1; u <= n; u++) {
		singlesource(u);
	}
}

int getnext(int from, bool* visited) {
	// gets probability distribution of which node to visit
	// next
	vector<pair<int, double> >prob;
	double sum = 0;
	for (auto i: graph[from]) {
		int vertex = i.first;
		if (visited[vertex] == 0) {
			double v = pheromone[from][vertex] / (dist[from][vertex] * dist[from][vertex]);
			sum += v;
			prob.push_back(make_pair(vertex, sum));
		}
	}

	int cnt = 0;
	for (auto i: graph[from]) {
		if (visited[i.first] == 0) {
			prob[cnt].second /= sum;
			cnt++;
		}
	}

	if (prob.empty())
		return -1;

	double r = rand() / (double) RAND_MAX;
	int lo = 0, hi = prob.size() - 1;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (prob[mid].second <= r)
			hi = mid;
		else
			lo = mid + 1;
	}
	return prob[lo].first;
}

int tour(vector<int>& path) {
	int src = rand() % n + 1;
	bool visited[n + 1];
	memset(visited, 0, sizeof(visited));
	visited[src] = 1;
	int cnt = 1;
	int here = src;
	int len = 0; // length of tour
	while (cnt < n) {
		path.push_back(here);
		int nxt = getnext(here, visited);
		if (nxt == -1) {
			path.clear();
			return -1;
		}
		visited[nxt] = 1;
		len += dist[here][nxt];
		here = nxt;
		cnt++;
	}
	path.push_back(here);
	return len;
}

void evaporate() {
	double rho = 0.75; // decrease by factor of 0.1
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			pheromone[i][j] = rho * pheromone[i][j];
		}
	}
}

int main(void) {
	srand(time(NULL));
	memset(pheromone, 1.0, sizeof(pheromone));
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		graph[u].push_back(make_pair(v, w));
		graph[v].push_back(make_pair(u, w));
		edges.push_back(edge(u, v, w, 0));
	}
	allpairs();
	int ants = n / 2;
	int iter = 50000;
	int mn = INT_MAX;
	vector<int> final_tour;
	while (iter--) {
		vector<int> paths[ants + 1];
		int lengths[ants + 1];
		// get every ant to tour
		for (int i = 0; i < ants; i++) {
			lengths[i] = tour(paths[i]);
			if (lengths[i] == -1) // no tour found
				continue;
			if (mn > lengths[i]) {
				final_tour.clear();
				for (auto x: paths[i])
					final_tour.push_back(x);
				mn = lengths[i];
			}
		}

		evaporate(); // evaporate pheromone from each edge by factor of 0.1

		// increase pheromones according to each ant
		for (int i = 0; i < ants; i++) {
			if (lengths[i] == -1)
				continue;
			for (int j = 0; j < paths[i].size() - 1; j++) {
				int u = paths[i][j], v = paths[i][j  + 1];
				pheromone[u][v] += 1.0 / lengths[i];
			}
		}
	}

	for (auto x: final_tour)
		printf("%d ", x);
	printf("\n");
	printf("%d\n", mn);
}