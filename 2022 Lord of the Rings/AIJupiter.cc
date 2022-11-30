#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Jupiter


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
  	struct S {
		Pos pos;
		Dir dir;
	};
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

	typedef pair<int, S> DS;
	typedef vector<DS> VDS;

	//BFS to search for the closest Treasure
	PDI buscarTesoro(int i, int j) {
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
					if (cell(xseg, yseg).treasure) return make_pair(dir, dis);
					visited[xseg][yseg] = true;
					if (cell(xseg, yseg).type == Cave and cell(xseg, yseg).id == -1) {
						queue.push(make_pair(make_pair(xseg, yseg), make_pair(dir, dis+1)));
					}
					if (cell(xseg, yseg).type == Rock and cell(xseg, yseg).id == -1) {
						queue.push(make_pair(make_pair(xseg, yseg), make_pair(dir, dis+1+cell(xseg, yseg).turns)));
					}
				}
			}
			first = false;
		}
		return make_pair(None, 2147483647);
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
	PDI buscarDwarf(int i, int j) {
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
					if (cell(xseg, yseg).id != -1 and unit(cell(xseg, yseg).id).type == Dwarf and unit(cell(xseg, yseg).id).player == me()) return make_pair(dir, dis);
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

    void move_dwarves() {
		VI D = dwarves(me());
		int n = D.size();
		VI perm = random_permutation(n);
		for (int i = 0; i < n; ++i) {
			int id = D[perm[i]];
			Unit u = unit(id);
			PDI moveTreasure = buscarTesoro(u.pos.i, u.pos.j);
			PDI moveEnemy = buscarEnemigo(u.pos.i, u.pos.j);

			if(moveEnemy.second < 2) command(id, moveEnemy.first);
			else command(id, moveTreasure.first);
        }
    }

    void move_wizards() {
        VI W = wizards(me());
        int n = W.size();
        VI perm = random_permutation(n);
        for (int i = 0; i < n; ++i) {
            int id = W[perm[i]];
            Unit u = unit(id);
            PDI move = buscarDwarf(u.pos.i, u.pos.j);
            command(id, move.first);
        }
    }


	/**
	 * Play method, invoked once per each round.
	 */
	void play () {
		move_dwarves();
		move_wizards();
	}
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
