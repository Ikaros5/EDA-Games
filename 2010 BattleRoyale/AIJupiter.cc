
#include "Player.hh"

using namespace std;


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Jupiter





struct PLAYER_NAME : public Player {


    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }
    

    /**
     * Attributes for your player can be defined here.
     */
    typedef vector<int> VI;
  	typedef vector<VI>  VVI;
	
	typedef vector <char>VC;
	typedef vector <VC>VVC;

	typedef vector <bool>VB;
	typedef vector <VB>VVB;

    typedef pair<int, int> PII;
    typedef pair<Dir, int> PDD;


    PDD buscar_casilla(int i, int j) {
		queue <pair<PII, PDD>> queue;  // cola de posiciones, direcciones y distancias
		queue.push(make_pair(make_pair(i, j), (make_pair(None, 0)))); // insertamos en la cola la posicion, la direccion y la distancia iniciales
		VVB visited(rows(), VB(cols(), false));    // matrix de visitados de tamaño rows * cols
		visited[i][j] = true;

		int x, y, dis;
		Dir dir;
		bool first = true;

		while (!queue.empty()) {
			dir = (queue.front().second).first;   // direccion
			dis = (queue.front().second).second;  // distancia
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			
			//Bottom
			if(first) dir = Bottom;
			if (comprobar_casilla(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
			
			//Top
			if(first) dir = Top;
			if (comprobar_casilla(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);

			//Right
			if(first) dir = Right;
			if (comprobar_casilla(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

			//Left
			if(first) dir = Left;
			if (comprobar_casilla(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);

			first = false;
		}
		return make_pair(None, 2147483647); //en caso de que no encuentre ciudad nos quedamos parados
	}
	bool comprobar_casilla(int x, int y, VVB& visited, queue<pair<PII, PDD>> &q, Dir dir, int dis) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).type == Empty and cell(x, y).owner != me()) return true;
			visited[x][y] = true;
			if (cell(x, y).type != Wall and cell(x, y).unit == -1) {
				q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
		}
		return false;
	}

	PDD buscar_enemigo(int i, int j) {
		queue <pair<PII, PDD>> queue;  // cola de posiciones, direcciones y distancias
		queue.push(make_pair(make_pair(i, j), (make_pair(None, 0)))); // insertamos en la cola la posicion, la direccion y la distancia iniciales
		VVB visited(rows(), VB(cols(), false));    // matrix de visitados de tamaño rows * cols
		visited[i][j] = true;

		int x, y, dis;
		Dir dir;
		bool first = true;

		while (!queue.empty()) {
			dir = (queue.front().second).first;   // direccion
			dis = (queue.front().second).second;  // distancia
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			
			//Bottom
			if(first) dir = Bottom;
			if (comprobar_knight(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
			
			//Top
			if(first) dir = Top;
			if (comprobar_knight(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);

			//Right
			if(first) dir = Right;
			if (comprobar_knight(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

			//Left
			if(first) dir = Left;
			if (comprobar_knight(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);

			first = false;
		}
		return make_pair(None, 2147483647); //en caso de que no encuentre ciudad nos quedamos parados
	}
	bool comprobar_knight(int x, int y, VVB& visited, queue<pair<PII, PDD>> &q, Dir dir, int dis) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).unit != -1 and unit(cell(x, y).unit).player != me()) return true;
			visited[x][y] = true;
			if (cell(x, y).type != Wall and cell(x, y).unit == -1) {
				q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
		}
		return false;
	}
    /**
     * Play method.
     * 
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */     
    virtual void play () {

		VI F = farmers(me());
        VI K = knights(me());
		
        for (int i = 0; i < sze(F); ++i) {
            int id = F[i];
			Unit u = unit(id);
			PDD dir = buscar_casilla(u.pos.i, u.pos.j);
			command(F[i], dir.first);
        }

        for (int i = 0; i < sze(K); ++i) {
            int id = K[i];
			Unit u = unit(id);
			PDD dir = buscar_enemigo(u.pos.i, u.pos.j);
			command(K[i], dir.first);
        }
    }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

