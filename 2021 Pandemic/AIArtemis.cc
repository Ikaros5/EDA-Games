#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Artemis


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
  
//--------------------------------------------------------------------------------------------------------------------------------------------------//
	//Valores a modificar
	int ciutats_cluster_size = 4;
	int percentage = 0.25;
	int rondas = 200;
//--------------------------------------------------------------------------------------------------------------------------------------------------//

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
			
            if(rondas % 2 == 0) {
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
			
            if(rondas % 2 == 0) {
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
			
            if(rondas % 2 == 0) {
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
	pair<Dir, int> direction_to(int i, int j, int di, int dj, int max_depth) {
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
			if(dis < max_depth) {
				if(rondas % 2 == 0) {
					//bottom
					if(first) dir = BOTTOM;
					if (mover_to(x+1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);
					
					//top
					if(first) dir = TOP;
					if (mover_to(x-1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);

					//right
					if(first) dir = RIGHT;
					if (mover_to(x, y+1, visited, queue, dir, dis, di , dj, first)) return make_pair(dir, dis);

					//left
					if(first) dir = LEFT;
					if (mover_to(x, y-1, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);
				}
				else {
					//right
					if(first) dir = RIGHT;
					if (mover_to(x, y+1, visited, queue, dir, dis, di , dj, first)) return make_pair(dir, dis);

					//left
					if(first) dir = LEFT;
					if (mover_to(x, y-1, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);

					if(first) dir = BOTTOM;
					if (mover_to(x+1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);
					
					//top
					if(first) dir = TOP;
					if (mover_to(x-1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);

				}
			}
			first = false;
		}
		return make_pair(NONE, 2147483647);
	}
	bool mover_to(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis, int di, int dj, bool first) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (x == di and y == dj) return true;
			visited[x][y] = true;
			if(first) {
				if (cell(x, y).type != WALL and cell(x, y).unit_id == -1) q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
			else {
				if (cell(x, y).type != WALL) q.push(make_pair(make_pair(x, y), make_pair(dir, dis+1)));
			}
		}
		return false;
	}

	VI calculate_cuadrant_score(int i, int j) {
		//cuadrante 1
		VI score(5, 0);
		for(int i = 0; i < rows()/2; i++) {
			for(int j = 0; j< cols()/2; j++) {
				if(cell(i,j).type == CITY or cell(i,j).type == PATH) score[1]++;
			}
		}
		//cuadrante 2
		for(int i = 0; i < rows()/2; i++) {
			for(int j = cols()/2; j< cols(); j++) {
				if(cell(i,j).type == CITY or cell(i,j).type == PATH) score[2]++;
			}
		}
		//cuadrante 3
		for(int i = rows()/2; i < rows(); i++) {
			for(int j = cols()/2; j< cols(); j++) {
				if(cell(i,j).type == CITY or cell(i,j).type == PATH) score[3]++;
			}
		}
		//cuadrante 4
		for(int i = rows()/2; i < rows(); i++) {
			for(int j =  0; j< cols()/2; j++) {
				if(cell(i,j).type == CITY or cell(i,j).type == PATH) score[4]++;
			}
		}
		//cuadrante 0
		int x = cols() / 4;
		int y = (rows()*3) / 4;
		for(int i = x; i < y; i++) {
			for(int j =  x; j< y; j++) {
				if(cell(i,j).type == CITY or cell(i,j).type == PATH) score[0]++;
			}
		}
		return score;
	}
	
	pair<Dir, int> move_to_cuadrant(int i, int j, int cuadrant) {
		if(cuadrant == 0) return direction_to(i, j, 35, 35, 1000);
		else if(cuadrant == 1) return direction_to(i, j, 17, 17, 1000);
		else if(cuadrant == 2) return direction_to(i, j, 17, 52, 1000);
		else if(cuadrant == 3) return direction_to(i, j, 52, 17, 1000);
		else return direction_to(i, j, 52, 52, 1000);
	}

	// int calculate_true_score(int i, int j, VI &cuadrant_score) {
	// 	VI true_score(5);
	// 	int cuadrant = 0;
	// 	pair<Dir, int> a = direction_to(i, j, 35, 35, 10000);
	// 	pair<Dir, int> b = direction_to(i, j, 17, 17, 10000);
	// 	pair<Dir, int> c = direction_to(i, j, 17, 52, 10000);
	// 	pair<Dir, int> d = direction_to(i, j, 52, 17, 10000);
	// 	pair<Dir, int> e = direction_to(i, j, 52, 52, 10000);		
	// 	for(int k = 0; k < 5; k++) {
	// 		if(a.second != 0) true_score[k] = cuadrant_score[k] / a.second;
	// 		else true_score[k] = cuadrant_score[k];
	// 	}
	// 	int max = true_score[0];
	// 	for(int k = 1; k < 5; k++) {
	// 		if(max < true_score[k]) {
	// 			max = true_score[k];
	// 			cuadrant = k;
	// 		}
	// 	}
	// 	return cuadrant;
	// }

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
//------------------------------------------------------------------------------------------------------------------------------//
			VI cuadrant_score = calculate_cuadrant_score(u.pos.i, u.pos.j);
			// int cuadrant = calculate_true_score(u.pos.i, u.pos.j, cuadrant_score);

			pair<Dir, int> move_city = buscar_ciudad(u.pos.i, u.pos.j);
			Dir dir_city = move_city.first;
			int dis_city = move_city.second;

			pair<Dir, int> move_path = buscar_camino(u.pos.i, u.pos.j);
			Dir dir_path = move_path.first;
			int dis_path = move_path.second;

			pair<pair<Dir, int>, Unit> move_player = buscar_jugador(u.pos.i, u.pos.j);
			Dir dir_player = move_player.first.first;
			int dis_player = move_player.first.second;

			if(dis_player <= 2) move(id, dir_player);
			else if(dis_city <= dis_path and dis_city < 25) move(id, dir_city);
			else if(dis_path < dis_city and dis_city < 25) move(id, dir_path);
			else {
				int max = cuadrant_score[0];
				int max2 = -1;
				for(int k = 0; k < 4; k++) {
					if(max < cuadrant_score[k]) max = cuadrant_score[k];
				}
				for(int k = 0; k < 3; k++) {
					if(max2 < cuadrant_score[k] and max2 != max) max2 = cuadrant_score[k];
				}
				pair<Dir, int> move_cuadrant1 = move_to_cuadrant(u.pos.i, u.pos.j, max);
				Dir dir_cuadrant1 = move_cuadrant1.first;
				int dis_cuadrant1 = move_cuadrant1.second;

				pair<Dir, int> move_cuadrant2 = move_to_cuadrant(u.pos.i, u.pos.j, max2);
				Dir dir_cuadrant2 = move_cuadrant2.first;
				int dis_cuadrant2 = move_cuadrant2.second;

				if(dis_cuadrant1 <= dis_cuadrant2) move(id, dir_cuadrant1);
				else move(id, dir_cuadrant2);
			}
//------------------------------------------------------------------------------------------------------------------------------//
			//If nearly out of time, do nothing.
			double st = status(me());
			if (st >= 0.9) return;
		}
 	}	
};

			
/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);