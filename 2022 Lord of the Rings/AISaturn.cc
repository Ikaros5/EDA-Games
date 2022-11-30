#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Saturn


// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
    typedef pair<int, int> P;

	typedef vector<int> VI;
    typedef vector<VI>  VVI;
	
    typedef vector<bool> VB;
    typedef vector<VB> VVB;

    typedef vector<char> VC;
    typedef vector<VC> VVC;
	
	typedef vector<Dir> VD;

    typedef pair<Dir, int> PDI; 
	typedef pair<int, Dir> PID; 

	typedef pair<int, pair<Pos, Dir>> S;
	typedef vector<S> VS;

	
	PDI buscarTesoro(int sourceI, int sourceJ) { 
		VVB vis(rows(), VB(cols(), false));
		VVI dist(rows(), VI(cols(), 2147483647));
		VD direcciones = {Top, Bottom, Right, Left, RT, BR, LB, TL};
		priority_queue <S, VS, greater<S>> q;
		int x, y, dis, w;
		Dir dir;
		bool first = true;
		Pos pos;
		q.push({0, {Pos(sourceI, sourceJ), None}});
		dist[sourceI][sourceJ] = 0;
		vis[sourceI][sourceJ] = true;

		while (!q.empty()) {
			x = q.top().second.first.i;
			y = q.top().second.first.j;
			dir = q.top().second.second;
			dis = q.top().first;
			q.pop();
			
			for (int i = 0; i < 8; i++) {
				pos = Pos(x,y) + Dir(i);
				if (pos_ok(pos) and !vis[pos.i][pos.j]) {
					if(first) dir = Dir(i);
					if (cell(pos).treasure) return make_pair(dir, dis+1);
					vis[pos.i][pos.j] = true;

					if(cell(pos).type == Rock) w = dist[x][y]+cell(pos).turns+1;
					else if((cell(pos).type == Cave or cell(pos).type == Outside) and cell(pos).id == -1) w = dist[x][y]+1;
					else w = 2147483647;

					if (dist[pos.i][pos.j] > w) {
						dist[pos.i][pos.j] = w;
						q.push({w, {Pos(pos.i, pos.j), dir}});
					}
				}
			}
			first = false;
		}
		return make_pair(dir, dist[x][y]);
	}

	//BFS to search for the closest Enemy
	PDI buscarEnemigo(int i, int j) {
		queue <pair <P, PDI>> queue;
		queue.push(make_pair(make_pair(i, j), (make_pair(None, 0))));
		VVB visited(rows(), VB(cols(), false));
		visited[i][j] = true;
		int x, y, dis, xseg, yseg;
		Dir dir;
		bool first = true;

		while(!queue.empty()) {
			dir = (queue.front().second).first;
			dis = (queue.front().second).second;
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			for(int i = 0; i < 8; i++) {
				xseg = (Pos(x,y)+Dir(i)).i;
				yseg = (Pos(x,y)+Dir(i)).j;
				if(first) dir = Dir(i);
				if (pos_ok(xseg, yseg) and !visited[xseg][yseg]) {
					if (cell(xseg, yseg).id != -1 and unit(cell(xseg, yseg).id).player != me() and unit(cell(xseg, yseg).id).type != Balrog and unit(cell(xseg, yseg).id).type != Troll) return make_pair(dir, dis);
					visited[xseg][yseg] = true;
					if ((cell(xseg, yseg).type == Cave or cell(xseg, yseg).type == Outside) and cell(xseg, yseg).id == -1) {
						queue.push(make_pair(make_pair(xseg, yseg), make_pair(dir, dis+1)));
					}
				}
			}
			first = false;
		}
		return make_pair(None, 2147483647);
	}
	
	//BFS to search for the closest Dwarf
	PDI buscarDwarf(int i, int j, VI &guarded) {
		queue <pair <P, PDI>> queue;
		queue.push(make_pair(make_pair(i, j), (make_pair(None, 0))));
		VVB visited(rows(), VB(cols(), false));
		visited[i][j] = true;
		int x, y, dis, xseg, yseg;
		Dir dir;
		bool first = true;

		while(!queue.empty()) {
			dir = (queue.front().second).first;
			dis = (queue.front().second).second;
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			for(int i = 0; i < 8; i=i+2) {
				xseg = (Pos(x,y)+Dir(i)).i;
				yseg = (Pos(x,y)+Dir(i)).j;
				if(first) dir = Dir(i);
				if (pos_ok(xseg, yseg) and !visited[xseg][yseg]) {
					if (cell(xseg, yseg).id != -1 and unit(cell(xseg, yseg).id).type == Dwarf and unit(cell(xseg, yseg).id).player == me()) {
						guarded.push_back(cell(xseg, yseg).id);
						return make_pair(dir, dis);
					}
					visited[xseg][yseg] = true;
					if ((cell(xseg, yseg).type == Cave or cell(xseg, yseg).type == Outside) and cell(xseg, yseg).id == -1) {
						queue.push(make_pair(make_pair(xseg, yseg), make_pair(dir, dis+1)));
					}
				}
			}
			first = false;
		}
		return make_pair(None, 2147483647);
	}
		
    void move_dwarves(VI &guarded) {
        VI D = dwarves(me());
        int n = D.size();
        VI perm = random_permutation(n);
        for (int i = 0; i < n; ++i) {
            int id = D[perm[i]];
            Unit u = unit(id);
			PDI moveTreasure = buscarTesoro(u.pos.i, u.pos.j);
			PDI moveEnemy = buscarEnemigo(u.pos.i, u.pos.j);
			bool warrior = false;
			for(uint j = 0; j < guarded.size(); j++) if(id == guarded[j]) warrior = true;

			if(warrior or moveEnemy.second < 2) command(id, moveEnemy.first);
			else command(id, moveTreasure.first);
        }
    }

    void move_wizards(VI &guarded) {
        VI W = wizards(me());
        int n = W.size();
        VI perm = random_permutation(n);
        for (int i = 0; i < n; ++i) {
            int id = W[perm[i]];
            Unit u = unit(id);
            PDI move = buscarDwarf(u.pos.i, u.pos.j, guarded);
            command(id, move.first);
        }
    }


	/**
	 * Play method, invoked once per each round.
	 */
	void play () {
		VI guarded;
		move_wizards(guarded);
		move_dwarves(guarded);
	}
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);