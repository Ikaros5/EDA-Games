#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
typedef pair <int, int> P;
typedef vector<pair <int, int>> VP;
typedef vector<VP> VVP;
typedef vector<bool> VB;
typedef vector<int> VI;


int DIJK(VVP &G, int source, int dest) { //return distance from source to dest
	int n = G.size();                    //remove comments and make void for printing the
    VB vis(n, false);                    //cost and # of ways to go with that cost
	VI dist(n, 2147483647);
    vector <int> whereFrom(n, -1);
	priority_queue <P, VP, greater<P>> q;
    int v; 

	q.push(make_pair(0, source));
	dist[source] = 0;
	while (!q.empty()) { 
		v = q.top().second;
		q.pop();

		if (!vis[v]) {
			vis[v] = true;
			for (P aux : G[v]) {
				int w = (dist[v]+aux.first);
				if (dist[aux.second] > w) {
					dist[aux.second] = w;
					q.push(make_pair(dist[aux.second], aux.second));
				}
			}
		}
	}
	return dist[dest];
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		int a, b, d;
		VVP adj(n);

		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(d, b));
		}

		int x, y;
		cin >> x >> y;
       
		int res =  DIJK(adj, x, y);
		if (res != 2147483647) cout << res << endl;
		else cout << "no path from " << x << " to " << y << endl;
	}
}