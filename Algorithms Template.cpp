#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<list>
using namespace std;
typedef vector<list<int>> graph;
typedef pair<int, int> P;
typedef vector<P> VP;
typedef vector<VP> VVP;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<bool> VB;
typedef vector<VB> VVB;

//----------------------------------------------------------------------------------------//
//------------   BFS    ------------------------------------------------------------------//
//----------------------------------------------------------------------------------------//
int BFS(VVC& mapa, int i, int j) {
    int n = mapa.size();
    int m = mapa[0].size();
    VVB visitados(n, VB(m, false));
	queue <pair<pair<int, int>, int>> q;
	q.push(make_pair(make_pair(i, j), 0));

	int x, y, d;
	while (!q.empty()) {
		x = (q.front().first).first;
		y = (q.front().first).second;
		d = q.front().second;
		q.pop();

		if (mapa[x][y] == 't') return d;
		else if (!visitados[x][y]) {
			visitados[x][y] = true;
			//using a for here will be cleaner if there are many conditions to check for
			if (x != 0 and mapa[x-1][y] != 'X') q.push(make_pair(make_pair(x-1, y), d+1));
			if (x != mapa.size()-1 and mapa[x+1][y] != 'X') q.push(make_pair(make_pair(x+1, y), d+1));
			if (y != 0 and mapa[x][y-1] != 'X') q.push(make_pair(make_pair(x, y-1), d+1));
			if (y != mapa[0].size()-1 and mapa[x][y+1] != 'X') q.push(make_pair(make_pair(x, y+1), d+1));
		}
	}
	return -1;
}

//----------------------------------------------------------------------------------------//
//------------   DFS    ------------------------------------------------------------------//
//----------------------------------------------------------------------------------------//
list<int> DFS(const graph &G) {
    int n = G.size();
    list<int> L;
    stack<int> S;
    VB visitados(n, false);
    for(int i = 0; i < n; i++) {
        S.push(i);
        while(not S.empty()) {
            int v = S.top();
            S.pop();
            if(not visitados[v]) {
                visitados[v] = true;
                L.push_back(v);
                for(int w : G[v]) S.push(w);
            }
        }
    }
    return L;
}

//----------------------------------------------------------------------------------------//
//------------   BACK   ------------------------------------------------------------------//
//----------------------------------------------------------------------------------------//
int back(VVB &tablero, VB &files, VB &columnes, VB &diagonalP, VB &diagonalB, int n, int i) {
    if(i == n) return 1;
    int res = 0;
    for(int j = 0; j < n; j++) {
        //la casilla es valida para posicionar una reina. 
        if(not files[i] and not columnes[j] and not diagonalP[i+j] and not diagonalB[i-j-1+n]) {
            tablero[i][j] = true;
            files[i] = true;
            columnes[j] = true;
            diagonalP[i+j] = true;
            diagonalB[i-j+n-1] = true;
            
            res += back(tablero, files, columnes, diagonalP, diagonalB, n, i+1);

            tablero[i][j] = false;
            files[i] = false;
            columnes[j] = false;
            diagonalP[i+j] = false;
            diagonalB[i-j+n-1] = false;
        }
    }
    return res;
}

//----------------------------------------------------------------------------------------//
//------------   PRIM   ------------------------------------------------------------------//
//----------------------------------------------------------------------------------------//
void initialize_graph(int n, int m, int v, int u, int w) {
 7   VVP matrix(n);
    for (int i = 0; i < m; ++i) {
        cin >> v >> u >> w;
        matrix[v-1].push_back(make_pair(w, u-1));
        matrix[u-1].push_back(make_pair(w, v-1));
    }
}
int MST(const VVP &g) {
	int n = g.size();
	priority_queue<P, VP, greater<P>> q;
	vector<bool> vis(n, false);
	vis[0] = true;
	P uv;
	//recorrremos todas las aristas 
	for(int i = 0; i < g[0].size(); i++) {
		uv = g[0][i];
		q.push(uv);
	} 
	int num = 1; //numero de vertices visitados
	int sum = 0; //coste del MST

	while (num < n) { //mientras no haya visitado todos los nodos
		int coste = q.top().first;
		int v = q.top().second;
		q.pop();

		if (!vis[v]) {
			vis[v] = true;
			for(int i = 0; i < g[v].size(); i++) {
				uv = g[v][i];
				if (not vis[uv.second]) q.push(uv);
			} 
			sum += coste;
			++num;
		}
	}
	return sum;
}

//----------------------------------------------------------------------------------------//
//------------   DIJK   ------------------------------------------------------------------//
//----------------------------------------------------------------------------------------//
int DIJK(VVP &G, int source, int dest) { //return distance from source to dest
	int n = G.size();                    //remove comments and make void for printing the
    VB vis(n, false);                    //cost and # of ways to go with that cost
	VI dist(n, 2147483647);
	//VI ways(n, 0);
	priority_queue <P, VP, greater<P>> q;

	q.push(make_pair(0, source));
	dist[source] = 0;
    //ways[source] = 1;

	while (!q.empty()) {
		int v = q.top().second;
		q.pop();

		if (!vis[v]) {
			vis[v] = true;
			for (P aux : G[v]) {
				int w = (dist[v]+aux.first);
				if (dist[aux.second] > w) {
					// ways[aux.second] = ways[v];
					dist[aux.second] = w;
					q.push(make_pair(dist[aux.second], aux.second));
				}
				// else if (dist[aux.second] == w) ways[aux.second] += ways[v];
			}
		}
	}

    // if (dist[dest] == 2147483647) {
	// 	cout << "no path from " << source << " to " << dest << endl;
	// 	return;
	// }
	// cout << "cost " << dist[dest] << ", " << ways[dest] << " way(s)" << endl;


    /* ADD THIS TO WRITE THE SHORTEST PATH + REMOVE THE LAST RETURN + MAKE VOID
	vector <int> whereFrom(n, -1);
	stack <int>result;
    if (q.empty()) {
    cout << "no path from " << source << " to " << dest << endl;
    return;
	}
	while (whereFrom[dest] != -1) {
		result.push(dest);
		dest = whereFrom[dest];
	}

	result.push(dest);
	cout << result.top();
	result.pop();
	while (!result.empty()) {
		cout << " " << result.top();
		result.pop();
	}
	cout << endl;
    */

	return dist[dest];
}
int main() {
	int n, m;
	while (cin >> n >> m) {
		int u, v, w;
		VVP matrix(n);
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> w;
			matrix[u].push_back(make_pair(w, v));
		}

		int x, y;
		cin >> x >> y;
		int res = DIJK(matrix, x, y);
		if (res != 2147483647) cout << res << endl;
		else cout << "no path from " << x << " to " << y << endl;
	}
}

//----------------------------------------------------------------------------------------//
//------------   TOPO   ------------------------------------------------------------------//
//----------------------------------------------------------------------------------------//
void initialize_graph(int n, int m) {
    int x, y;
    vector<int> ge(n, 0);
    VVI adj(n);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        adj[x].push_back(y);
        ++ge[y];
    }
}
list<int> ordenacio_topologica(VVI &G, vector<int> &ge) {
	int n = G.size();
	VI ge(n, 0);
	stack<int> s;
	list<int> L;
	//llenamos la tabla de grados de entrada
	for(int u = 0; u < n; u++) {
		for(int v : G[u]) ++ge[v];
	}
	//añadimos a la cola las tareas iniciales en orden
	for(int u = 0; u < n; u++) {
		if(ge[u] == 0) s.push(u);
	}
	while (!s.empty()) {
		int u = s.top();
		s.pop();
		L.push_back(u);
		for (int v: G[u]) if (--ge[v] == 0) s.push(v);
	}
	return L;
}