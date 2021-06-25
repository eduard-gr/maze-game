#include <curses.h>
#include <vector>

#if !defined(MAZE_HPP)
#define MAZE_HPP

#define MAZE_SIZE_HEIGHT 20
#define MAZE_SIZE_WIDTH 50

#define START 0x9
#define STOP 0x10

#define PLAYER '*'
#define GROUND ' '
#define WALL '#'
#define EXIT '@'
#define START 'S'

struct Maze {
	char title[50];
	char map[MAZE_SIZE_HEIGHT][MAZE_SIZE_WIDTH];
};

Maze new_maze();

void draw_maze(WINDOW *window, Maze *maze);
void save_mazes(std::vector<Maze> *mazes);
void load_mazes(std::vector<Maze> *mazes);
bool maze_get_start(Maze *maze, int *x,int *y);
bool maze_get_exit(Maze *maze, int *x,int *y);
bool can_go_through(Maze *maze, int x,int y);
bool is_exit(Maze *maze, int x,int y);

#endif // MAZE_HPP
