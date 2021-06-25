#include "maze.hpp" 
#include <cstring>
#include <fstream>



bool is_exit(Maze *maze, int x,int y){
	if(maze->map[y][x] == EXIT){
		return true;
	}

	return false;
}

bool can_go_through(Maze *maze, int x,int y){
	if(maze->map[y][x] == WALL){
		return false;
	}

	return true;
}

bool maze_get_start(Maze *maze, int *x,int *y){
	for(int iy = 0; iy < MAZE_SIZE_HEIGHT;iy++){
		for(int ix = 0; ix < MAZE_SIZE_WIDTH; ix++){
			if(maze->map[iy][ix] == START){
				*x = ix;
				*y = iy;
				return true;
			}
		}
	}

	return false;
}

bool maze_get_exit(Maze *maze, int *x,int *y){
	for(int iy = 0; iy < MAZE_SIZE_HEIGHT;iy++){
		for(int ix = 0; ix < MAZE_SIZE_WIDTH; ix++){
			if(maze->map[iy][ix] == EXIT){
				*x = ix;
				*y = iy;
				return true;
			}
		}
	}

	return false;
}


Maze new_maze(){

	Maze maze;
	strncpy(maze.title, "New level", sizeof(maze.title));

	for(int y = 0; y < MAZE_SIZE_HEIGHT;y++){
		for(int x = 0; x < MAZE_SIZE_WIDTH; x++){
			maze.map[y][x] = GROUND;
		}
	}

	for(int y = 0; y < MAZE_SIZE_HEIGHT;y++){
		maze.map[y][0] = WALL;
		maze.map[y][MAZE_SIZE_WIDTH - 1] = WALL;
	}

	for(int x = 0; x < MAZE_SIZE_WIDTH; x++){
		maze.map[0][x] = WALL;
		maze.map[MAZE_SIZE_HEIGHT - 1][x] = WALL;
	}

	maze.map[1][1] = START;
	maze.map[MAZE_SIZE_HEIGHT - 2][MAZE_SIZE_WIDTH - 2] = EXIT;

	return maze;
}

void draw_maze(WINDOW *window, Maze *maze){

	for(int y = 0; y < MAZE_SIZE_HEIGHT;y++){
		for(int x = 0; x < MAZE_SIZE_WIDTH; x++){
			mvwaddch(window, y, x, maze->map[y][x]);
		}
	}

}

void save_mazes(std::vector<Maze> *mazes){
	std::ofstream fs("game.bin", std::ios::out | std::ios::binary | std::ofstream::trunc);

	for (int i = 0; i < mazes->size(); i++) {
		Maze maze = mazes->at(i);
		fs.write((char*) &maze, sizeof(Maze));
	}

	fs.close();
}

void load_mazes(std::vector<Maze> *mazes){
	std::fstream fs("game.bin", std::fstream::in | std::fstream::binary);
	if (fs.is_open() == false){
		return;
	}

	while (true){
		Maze maze;
		fs.read((char*)&maze, sizeof(Maze));

		if(fs.eof()){
			break;
		}

		mazes->push_back(maze);
	}

	fs.close();
	
}