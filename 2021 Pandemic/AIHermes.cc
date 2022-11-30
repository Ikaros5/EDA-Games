#include "Player.hh"
#include <queue>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Hermes


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

  	typedef vector<int> VI;
  	typedef vector<VI>  VVI;
	
	typedef vector <char>VC;
	typedef vector <VC>VVC;

	typedef vector <bool>VB;
	typedef vector <VB>VVB;
  
	//dir 0 = bottom
	//dir 1 = right
	//dir 2 = top
	//dir 3 = left
	//dir 4 = none

	// BFS to search for the closest city
	pair<Dir, int> buscar_ciudad(int i, int j) {
		queue <pair < pair<int, int>, pair<Dir, int>>> queue; // cola de posiciones, direcciones y distancias
		queue.push(make_pair(make_pair(i, j), (make_pair(NONE, 0)))); // insertamos en la cola la posicion, la direccion y la distancia iniciales
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
			
            if(nb_rounds() % 2 == 0) {
                //bottom
                if(first) dir = BOTTOM;
                if (mover_ciudad(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //top
                if(first) dir = TOP;
                if (mover_ciudad(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);

                //right
                if(first) dir = RIGHT;
                if (mover_ciudad(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

                //left
                if(first) dir = LEFT;
                if (mover_ciudad(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);
            }
            else {
                //right
                if(first) dir = RIGHT;
                if (mover_ciudad(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

                //left
                if(first) dir = LEFT;
                if (mover_ciudad(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //bottom
                if(first) dir = BOTTOM;
                if (mover_ciudad(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //top
                if(first) dir = TOP;
                if (mover_ciudad(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
            }
			first = false;
		}
		return make_pair(NONE, 2147483647); //en caso de que no encuentre ciudad nos quedamos parados
	}
	bool mover_ciudad(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).type == CITY and city_owner(cell(x, y).city_id) != me()) return true;
			visited[x][y] = true;
			if (cell(x, y).type != WALL and cell(x, y).unit_id == -1) {
				q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
		}
		return false;
	}

	// BFS to search for the closest path
	pair<Dir, int> buscar_camino(int i, int j) {
		queue <pair < pair<int, int>, pair<Dir, int>>> queue; // cola de posiciones, direcciones y distancias
		queue.push(make_pair(make_pair(i, j), (make_pair(NONE, 0)))); // insertamos en la cola la posicion, la direccion y la distancia iniciales
		VVB visited(rows(), VB(cols(), false));    // matrix de visitados de tamaño rows * cols
		visited[i][j] = true;

		int x, y, dis;
		Dir dir;
		bool first = true;

		while (!queue.empty()) {
			dir = (queue.front().second).first;   //direccion
			dis = (queue.front().second).second; //distancia
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			
            if(nb_rounds() % 2 == 0) {
                //bottom
                if(first) dir = BOTTOM;
                if (mover_camino(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //top
                if(first) dir = TOP;
                if (mover_camino(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);

                //right
                if(first) dir = RIGHT;
                if (mover_camino(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

                //left
                if(first) dir = LEFT;
                if (mover_camino(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);
            }
            else {
                //right
                if(first) dir = RIGHT;
                if (mover_camino(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

                //left
                if(first) dir = LEFT;
                if (mover_camino(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //bottom
                if(first) dir = BOTTOM;
                if (mover_camino(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //top
                if(first) dir = TOP;
                if (mover_camino(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
            }

			first = false;
		}
		return make_pair(NONE, 2147483647); //en caso de que no encuentre ciudad nos quedamos parados
	}
	bool mover_camino(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).type == PATH and path_owner(cell(x, y).path_id) != me()) return true;
			visited[x][y] = true;
			if (cell(x, y).type != WALL and cell(x, y).unit_id == -1) {
				q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
		}
		return false;
	}

	// BFS to search for the closest player
	pair<pair<Dir, int>, Unit> buscar_jugador(int i, int j) {
        Unit u;
		queue <pair < pair<int, int>, pair<pair<Dir, int>, Unit>>> queue; // cola de posiciones, direcciones y distancias
		queue.push(make_pair(make_pair(i, j), make_pair(make_pair(NONE, 0), u))); // insertamos en la cola la posicion, la direccion y la distancia iniciales
		VVB visited(rows(), VB(cols(), false));    // matrix de visitados de tamaño rows * cols
		visited[i][j] = true;

		int x, y, dis;
		Dir dir;
		bool first = true;

		while (!queue.empty()) {
            Unit u = (queue.front().second).second;
			dir = (queue.front().second).first.first;  //direccion
			dis = (queue.front().second).first.second; //distancia
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			
            if(nb_rounds() % 2 == 0) {
                //bottom
                if(first) dir = BOTTOM;
                if (mover_jugador(x+1, y, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);
                
                //top
                if(first) dir = TOP;
                if (mover_jugador(x-1, y, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);

                //right
                if(first) dir = RIGHT;
                if (mover_jugador(x, y+1, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);

                //left
                if(first) dir = LEFT;
                if (mover_jugador(x, y-1, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);
            }
            else {
                //right
                if(first) dir = RIGHT;
                if (mover_jugador(x, y+1, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);

                //left
                if(first) dir = LEFT;
                if (mover_jugador(x, y-1, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);
                
                //bottom
                if(first) dir = BOTTOM;
                if (mover_jugador(x+1, y, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);
                
                //top
                if(first) dir = TOP;
                if (mover_jugador(x-1, y, visited, queue, dir, dis, u)) return make_pair(make_pair(dir, dis), u);
            }

			first = false;
		}
		return make_pair(make_pair(NONE, 2147483647), u); //en caso de que no encuentre ciudad nos quedamos parados
	}
	bool mover_jugador(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<pair<Dir, int>, Unit>>> &q, Dir dir, int dis, Unit u) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).unit_id != -1 and unit(cell(x, y).unit_id).player != me()) return true;
			visited[x][y] = true;
			if (cell(x, y).type != WALL and cell(x, y).unit_id == -1) {
				q.push(make_pair(make_pair(x, y), make_pair(make_pair(dir, dis+1), u)));
			}
		}
		return false;
	}

	// BFS to search for the shortest path to pos(di, dj)
	pair<Dir, int> direction_to(int i, int j, int di, int dj) {
		queue <pair < pair<int, int>, pair<Dir, int>>> queue; // cola de posiciones, direcciones y distancias
		queue.push(make_pair(make_pair(i, j), (make_pair(NONE, 0)))); // insertamos en la cola la posicion, la direccion y la distancia iniciales
		VVB visited(rows(), VB(cols(), false));    // matrix de visitados de tamaño rows * cols
		visited[i][j] = true;

		int x, y, dis;
		Dir dir;
		bool first = true;

        if(!pos_ok(di, dj)) return make_pair(NONE, 2147483647);
		
        while (!queue.empty()) {
			dir = (queue.front().second).first;   // direccion
			dis = (queue.front().second).second;  // distancia
			x = (queue.front().first).first;
			y = (queue.front().first).second;
			queue.pop();
			
			//bottom
			if(first) dir = BOTTOM;
			if (mover_to(x+1, y, visited, queue, dir, dis, di, dj)) return make_pair(dir, dis);
			
			//top
			if(first) dir = TOP;
			if (mover_to(x-1, y, visited, queue, dir, dis, di, dj)) return make_pair(dir, dis);

			//right
			if(first) dir = RIGHT;
			if (mover_to(x, y+1, visited, queue, dir, dis, di , dj)) return make_pair(dir, dis);

			//left
			if(first) dir = LEFT;
			if (mover_to(x, y-1, visited, queue, dir, dis, di, dj)) return make_pair(dir, dis);

			first = false;
		}
		return make_pair(NONE, 2147483647); //en caso de que no encuentre la ciudad nos quedamos parados
	}
	bool mover_to(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis, int di, int dj) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (x == di and y == dj) return true;
			visited[x][y] = true;
			if (cell(x, y).type != WALL and cell(x, y).unit_id == -1) {
				q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
		}
		return false;
	}

	//returns true if the score difference with the winning player is more than n
	bool big_score_diff(int n) {
		for (int i = 0; i < nb_players(); i++) {
			if(i != me() and total_score(i)-total_score(me()) > n) return true;
		}
		return false;
	}
	
	//returns true if I have control of more than PERCENTAGE of the total units
	bool control(double percentage) {
		double num_unidades_mias = my_units(me()).size(); 
		if (num_unidades_mias < (total_units()*percentage)) return false;
		else return true;
	}
	
	//returns if there is a path longer than n
	int long_path(int n) {
		for(int i = 0; i < nb_paths(); i++) {
			int x = path(i).second.size();
			if(x > n) return i;
		}
		return -1;
	}

	//returns if there is a weak enemy nearby
    bool weak_enemy(Unit enemy, int dis, int weak_enemy_health, int dis_weak_enemy) {
        if(enemy.health < weak_enemy_health and dis < dis_weak_enemy) {
            return true;
        }
        else return false;
    }
	
	//

	
  	/**
   	* Play method, invoked once per each round.
  	*/
  	virtual void play () {
		VI U = my_units(me()); // Get the id's of my units.
	  	int n = U.size();
	  	VI perm = random_permutation(n);
	  	for (int i = 0; i < n; ++i) {
			// We process the units in random order.
		 	int id = U[perm[i]];
		  	Unit u = unit(id);
		  	
			//Valores a modificar
            double percentage = 0.25;
            int scorediff = 5000;
			int lpath = 40;
			int dis_to_path = 30;
            int dis_to_attack = 2;
            int weak_enemy_health = 40;
            int very_weak_enemy_health = 20;
            int dis_weak_enemy = 5;
            int dis_very_weak_enemy = 8;

			pair<Dir, int> mov1 = buscar_ciudad(u.pos.i, u.pos.j);
            pair<Dir, int> mov2 = buscar_camino(u.pos.i, u.pos.j);
			pair<pair<Dir, int>, Unit> mov3 = buscar_jugador(u.pos.i, u.pos.j);
			
			Dir dir1 = mov1.first;
			Dir dir2 = mov2.first;
			Dir dir3 = mov3.first.first;
			
			int dis1 = mov1.second;
			int dis2 = mov2.second;
			int dis3 = mov3.first.second;

            Unit enemy = mov3.second;;

			// int lpath_id = long_path(lpath);
			// if(lpath_id > 0 and path_owner(lpath_id) != me()) {
			// 	if(dis3 <= 2) move(id, dir3);
			// 	else {	
			// 		int length = path(lpath_id).second.size();
					
			// 		pair<Dir, int> mov4 = direction_to(u.pos.i, u.pos.j, path(lpath_id).second[0].i, path(lpath_id).second[0].j);
			// 		pair<Dir, int> mov5 = direction_to(u.pos.i, u.pos.j, path(lpath_id).second[length-1].i, path(lpath_id).second[length-1].j);
			// 		pair<Dir, int> mov6 = direction_to(u.pos.i, u.pos.j, path(lpath_id).second[length/2].i, path(lpath_id).second[length/2].j);
					
			// 		if(mov4.second < dis_to_path and mov4.second < mov5.second and mov4.second < mov6.second) move(id, mov4.first);
			// 		if(mov5.second < dis_to_path and mov5.second < mov4.second and mov5.second < mov6.second) move(id, mov5.first);
			// 		if(mov6.second < dis_to_path and mov6.second < mov5.second and mov6.second < mov4.second) move(id, mov6.first);
			// 	}
			// }
            // else { 



			if(dis3 <= dis_to_attack) move(id, dir3);
			else {
				if(!control(percentage)) {
					move(id, dir3);
				}
				else {
                    if(weak_enemy(enemy, dis3, very_weak_enemy_health, dis_very_weak_enemy) and u.health > enemy.health+20) move(id, dir3);
                    else if(weak_enemy(enemy, dis3, weak_enemy_health, dis_weak_enemy) and u.health > enemy.health+20) move(id, dir3);
					else if (dis1 <= dis2) move(id, dir1);
					else move(id, dir2);
					// if(cell(u.pos.i, u.pos.j).type == CITY) {
					// 	for(int i = 0; i < nb_paths(); i++)(); i++) {
                    //         if(path(i).first.first == cell(u.pos.i, u.pos.j).city_id or path(i).first.second == cell(u.pos.i, u.pos.j).city_id) {
                                
                    //             move(id, dir2);
                    //         }
                    //     }
					// }
					// else {
					// }
				}
			}
			
			//If nearly out of time, do nothing.
			double st = status(me());
			if (st >= 0.95) return;
		}
 	}	
};

			
/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

