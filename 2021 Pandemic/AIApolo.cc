#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Apolo


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
	int rondas = round();
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

	// BFS to search for the closest city
	pair<Dir, int> buscar_ciudad2(int i, int j) {
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
            
			//bottom
			if(first) dir = BOTTOM;
			if (mover_ciudad2(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
			
			//top
			if(first) dir = TOP;
			if (mover_ciudad2(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);

			//right
			if(first) dir = RIGHT;
			if (mover_ciudad2(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

			//left
			if(first) dir = LEFT;
			if (mover_ciudad2(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);
           
			first = false;
		}
		return make_pair(NONE, 2147483647); //en caso de que no encuentre ciudad nos quedamos parados
	}
	bool mover_ciudad2(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).type == CITY) return true;
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

	// BFS to search for the closest city
	pair<Dir, int> buscar_camino_desde_ciudad(int i, int j) {
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
                if (mover_camino_desde_ciudad(x+1, y, visited, queue, dir, dis)) return make_pair(dir, dis);
                
                //top
                if(first) dir = TOP;
                if (mover_camino_desde_ciudad(x-1, y, visited, queue, dir, dis)) return make_pair(dir, dis);

                //right
                if(first) dir = RIGHT;
                if (mover_camino_desde_ciudad(x, y+1, visited, queue, dir, dis)) return make_pair(dir, dis);

                //left
                if(first) dir = LEFT;
                if (mover_camino_desde_ciudad(x, y-1, visited, queue, dir, dis)) return make_pair(dir, dis);
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
	bool mover_camino_desde_ciudad(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (cell(x, y).type == PATH and path_owner(cell(x, y).path_id) != me()) return true;
			visited[x][y] = true;
			if (cell(x, y).type == CITY and cell(x, y).unit_id == -1) {
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

		// BFS to search for the shortest path to pos(di, dj)
	pair<Dir, int> direction_to2(int i, int j, int di, int dj, int max_depth) {
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
					if (mover_to2(x+1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);
					
					//top
					if(first) dir = TOP;
					if (mover_to2(x-1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);

					//right
					if(first) dir = RIGHT;
					if (mover_to2(x, y+1, visited, queue, dir, dis, di , dj, first)) return make_pair(dir, dis);

					//left
					if(first) dir = LEFT;
					if (mover_to2(x, y-1, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);
				}
				else {
					//right
					if(first) dir = RIGHT;
					if (mover_to2(x, y+1, visited, queue, dir, dis, di , dj, first)) return make_pair(dir, dis);

					//left
					if(first) dir = LEFT;
					if (mover_to2(x, y-1, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);

					if(first) dir = BOTTOM;
					if (mover_to2(x+1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);
					
					//top
					if(first) dir = TOP;
					if (mover_to2(x-1, y, visited, queue, dir, dis, di, dj, first)) return make_pair(dir, dis);

				}
			}
			first = false;
		}
		return make_pair(NONE, 2147483647);
	}
	bool mover_to2(int x, int y, VVB& visited, queue <pair < pair<int, int>, pair<Dir, int>>> &q, Dir dir, int dis, int di, int dj, bool first) {
		if (pos_ok(x, y) and !visited[x][y]) {
			if (x == di and y == dj and city_owner(cell(di, dj).city_id) != me()) return true;
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

	bool control(double percentage) {
		double num_unidades_mias = my_units(me()).size(); 
		if (num_unidades_mias < (total_units()*percentage)) return false;
		else return true;
	}

	//retorna un vector formado por vectores con cada una de las componentes conexas (IDs de las ciudades que las forman)
	VVI graph() {
		int x, y;
		VVI g;
		VVI matrix(nb_cities(), VI(nb_cities(), 0));
		for (int i = 0; i < nb_paths(); i++) {
			x = path(i).first.first; //city 1
			y = path(i).first.second; //city 2
			matrix[x][y] = 1;
			matrix[y][x] = 1;
		}
		VB visited(nb_cities(), false);
		for (int i = 0; i < nb_cities(); i++) {
			if(!visited[i]) {
				VI connected_cities;
				connected_cities.push_back(i);
				DFS(i, matrix, visited, connected_cities);
				g.push_back(connected_cities);
			}
		}
		return g;
	}

	//DFS
	void DFS(int i, VVI &matrix, VB &visited, VI &connected_cities) {
		visited[i] = true;
		for (int j = 0; j < nb_cities(); j++) {
			if (matrix[i][j] == 1 and !visited[j]) {
				connected_cities.push_back(j);
				DFS(j, matrix, visited,  connected_cities);
			}
		}
	}

	//retorna les ciutats que formen la component conexa mes gran del graf CIUDADES-CAMINOS
	VI largest_cluster(VVI &componentes_conexas, uint size) {
		uint max = 0;
		VI ciutats_cluster;
		//max = largest city cluster
		for(uint i = 0; i < componentes_conexas.size(); i++) {
			if(componentes_conexas[i].size() > max) {
				max = componentes_conexas[i].size();
				ciutats_cluster = componentes_conexas[i];
			}
		}
		if(max > size) return ciutats_cluster;
		VI ciutats_cluster2(0);
		return ciutats_cluster2;
	}
	
	//retorna els camins que conecten les ciutats del cluster
	VI calculate_camins_cluster(VI &ciutats_cluster) {
		VI path_con;
		for(int i = 0; i < nb_paths(); i++) {
			bool acabat = false;
			for(uint j = 0; j < ciutats_cluster.size() and !acabat; j++) {
				if(path(i).first.first == ciutats_cluster[j] or path(i).first.second == ciutats_cluster[j]) {
					path_con.push_back(i);
					acabat = true;
				}
			}
		}
		return path_con;
	}

	//defiende la ciudad en la que se encuentra
	Dir defend(int i, int j, vector<pair<Pos, Pos>> &city_pos) {
		pair<Dir, int> move_city = buscar_ciudad2(i, j);
		return move_city.first;
	}

	//retorna la direccio cap al cluster mes proper, o si esta massa lluny es queda defensant la ciutat actual
	pair<Dir, int> go_to_closest_cluster(int i, int j, VI &ciutats_cluster, VI &path_contections, vector<pair<Pos, Pos>> &city_pos) {
		int mincity = 10000000, mincity2 = 10000000, minpath, aux;
		Pos p;
		Dir dircity = NONE;
		Dir dirpath = NONE;
		for(uint k = 0; k < ciutats_cluster.size(); k++) {
			if(city_owner(ciutats_cluster[k]) != me()) {
				int x = city_pos[ciutats_cluster[k]].first.i;
				int y = city_pos[ciutats_cluster[k]].first.j;
				int x1 = city_pos[ciutats_cluster[k]].second.i;
				int y1 = city_pos[ciutats_cluster[k]].second.j;
				for(int a = x; a < x1+1; a++) {
					for(int b = y; b < y1+1; b++) {
						aux = abs(a - i) + abs(b -j);
						if(aux < mincity2) {
							mincity2 = aux;
							p.i = a;
							p.j = b;
						}
					}
				}
				pair<Dir, int> search_city = direction_to(i, j, p.i, p.j, mincity+1);
				if (mincity > search_city.second) {
					mincity = search_city.second;
					dircity = search_city.first;
				}
			}
		}

		pair<Dir, int> search_path = buscar_camino_desde_ciudad(i, j);
		minpath = search_path.second;
		dirpath = search_path.first;
		Pos w(i,j);
		// cerr << "                            I m at " << w << "Minimim distance to city is: " << mincity << " at pos " << p << endl;
		// cerr << "                            Minimim distance to path is: " << minpath << " at pos" << endl;
		if(mincity <= minpath) return make_pair(dircity, mincity);
		else return make_pair(dirpath, minpath);
	}
	
	//true if all the cluster is conquered
	bool conquered(VI &ciutats_cluster, VI &camins_cluster) {
		for(uint i = 0; i < ciutats_cluster.size(); i++)  {
			if(city_owner(ciutats_cluster[i]) != me()) return false;
		}
		// for(uint i = 0; i < camins_cluster.size(); i++)  {
		// 	if(path_owner(camins_cluster[i]) != me()) return false;
		// }
		return true;
	}

	//true if all the cities and paths of the map are conquered by me
	bool i_have_control_of_the_world() {
		for(int i = 0; i < nb_cities(); i++) {
			if(city_owner(i) != me()) return false;
		}
		for(int i = 0; i < nb_paths(); i++) {
			if(path_owner(i) != me()) return false;
		}
		return true;
	}

	vector<pair<Pos, Pos>> calculate_city_pos() {
		vector<pair<Pos, Pos>> city_pos(nb_cities());
		VB visited(nb_cities(), false);
		for(int i = 0; i < rows(); i++) {
			for(int j = 0; j < cols(); j++) {
				if(cell(i,j).type == CITY) {
					Pos p(i,j);
					if(!visited[cell(i,j).city_id]) {
						city_pos[cell(i,j).city_id].first = p;
						visited[cell(i,j).city_id] = true;
					}
					city_pos[cell(i,j).city_id].second = p;
				}
			}
		}
		return city_pos;
	}

	int city_size(int id, vector<pair<Pos, Pos>> &city_pos) {
		int x = city_pos[id].first.i;
		int y = city_pos[id].first.j;
		int x1 = city_pos[id].second.i;
		int y1 = city_pos[id].second.j;

		int a = abs(x - x1) + 1;
		int b = abs(y - y1) + 1;

		return a*b;
	}

	VB calculate_empty_cities() {
		VB empty_cities(nb_cities(), true);
		for(int m = 0; m < rows(); m++) {
			for(int n = 0; n < cols(); n++) {
				if(cell(m,n).type == CITY and (cell(m,n).unit_id != -1 or city_owner(cell(m,n).city_id) == me())) empty_cities[cell(m,n).city_id] = false;
			}
		}
		return empty_cities;
	}

	pair<Dir, int> go_to_empty_city(int i, int j, VB &empty_cities, vector<pair<Pos, Pos>> &city_pos) {
		int mincity = 10000000, mincity2 = 10000000, aux;
		Pos p;
		Dir dircity = NONE;
		for(uint k = 0; k < empty_cities.size(); k++) {
			if(empty_cities[k]) {
				int x = city_pos[k].first.i;
				int y = city_pos[k].first.j;
				int x1 = city_pos[k].second.i;
				int y1 = city_pos[k].second.j;
				for(int a = x; a < x1+1; a++) {
					for(int b = y; b < y1+1; b++) {
						aux = abs(a - i) + abs(b -j);
						if(aux < mincity2) {
							mincity2 = aux;
							p.i = a;
							p.j = b;
						}
					}
				}
				pair<Dir, int> search_city = direction_to2(i, j, p.i, p.j, mincity+1);
				if (mincity > search_city.second) {
					mincity = search_city.second;
					dircity = search_city.first;
				}
			}
		}
		return make_pair(dircity, mincity);	
	}

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
		
			pair<pair<Dir, int>, Unit> move_player = buscar_jugador(u.pos.i, u.pos.j);
			Dir dir_player = move_player.first.first;
			int dis_player = move_player.first.second;

			vector<pair<Pos, Pos>> city_pos = calculate_city_pos();
			VVI componentes_conexas = graph();
			VI ciutats_cluster = largest_cluster(componentes_conexas, ciutats_cluster_size);
			VI camins_cluster = calculate_camins_cluster(ciutats_cluster);

//------------------------------------------------------------------------------------------------------------------------------//	
			if(dis_player <= 2) move(id, dir_player);
			else {
				VB empty_cities = calculate_empty_cities();
				pair<Dir, int> move_empty = go_to_empty_city(u.pos.i, u.pos.j, empty_cities, city_pos);
				if(((round() > 40 and round() < 80) or (round() > 120 and round() < 150)) and move_empty.second < 35) move(id, move_empty.first);
				else {
					if(u.damage > 0) {
						move(id, dir_player);
					}
					else {
						//su hay un cluster de tamaño aceptable vamos a por él
						pair<Dir, int> move_cluster = go_to_closest_cluster(u.pos.i, u.pos.j, ciutats_cluster, camins_cluster, city_pos);
						Dir dir = move_cluster.first;
						int dis = move_cluster.second;

						if(ciutats_cluster.size() > 0 and !conquered(ciutats_cluster, camins_cluster) and dis < 8) {
							move(id, dir);
						}
						//si no hay un cluster capturamos ciudades i caminos normales
						else{
							pair<Dir, int> move_city = buscar_ciudad(u.pos.i, u.pos.j);
							Dir dir_city = move_city.first;
							int dis_city = move_city.second;

							pair<Dir, int> move_path = buscar_camino(u.pos.i, u.pos.j);
							Dir dir_path = move_path.first;
							int dis_path = move_path.second;
							if (dis_city <= dis_path) move(id, dir_city);
							else move(id, dir_path);
							
						}
					}
				}
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