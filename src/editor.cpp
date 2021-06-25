
#include "maze.hpp"
#include "menu.hpp"
#include <stdlib.h> 
#include <ctype.h> 

void edit(std::vector<Maze> *mazes, int index){
	clear();
	refresh();
	keypad(stdscr, TRUE);

	WINDOW *help = newwin(
		11,
		45, 
		1,
		MAZE_SIZE_WIDTH + 5);

	mvwprintw(help, 1, 2, "Use arrows to move cursor");
	mvwhline(help, 2, 1, '-', 43);
	mvwprintw(help, 3, 2, "W - Wall");
	mvwprintw(help, 4, 2, "G - Ground");
	mvwprintw(help, 5, 2, "S - Player start location");
	mvwprintw(help, 6, 2, "F - Player exit location");
	mvwhline(help, 7, 1, '-', 43);
	mvwprintw(help, 8, 2, "E - Save level and return to main menu");
	mvwprintw(help, 9, 2, "D - Delete level and return to main menu");

	wborder(help, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(help);


	WINDOW *window = newwin(
		MAZE_SIZE_HEIGHT,
		MAZE_SIZE_WIDTH,
		1,
		1);


	int x = 1;
	int y = 1;

	int start_x = 1;
	int start_y = 1;

	int exit_x = 1;
	int exit_y = 1;

	Maze *maze = &mazes->at(index);
	maze_get_start(maze, &start_x, &start_y);
	maze_get_exit(maze, &exit_x, &exit_y);

	draw_maze(window, maze);
	mvwaddch(window, y, x, PLAYER);
	wrefresh(window);

	while(1) {

		int ch = getch();

		if(ch == KEY_LEFT) {
			if(x <= 0) {
				continue;
			}

			mvwaddch(window, y, x, maze->map[y][x]);
			x--;
			mvwaddch(window, y, x, PLAYER);
		}else if(ch == KEY_RIGHT) {
			if(x >= MAZE_SIZE_WIDTH - 1) {
				continue;
			}

			mvwaddch(window, y, x, maze->map[y][x]);
			x++;
			mvwaddch(window, y, x, PLAYER);
		}else if(ch == KEY_UP) {
			if(y <= 0) {
				continue;
			}

			mvwaddch(window, y, x, maze->map[y][x]);
			y--;
			mvwaddch(window, y, x, PLAYER);
		}else if(ch == KEY_DOWN) {
			if(y >= MAZE_SIZE_HEIGHT - 1) {
				continue;
			}

			mvwaddch(window, y, x, maze->map[y][x]);
			y++;
			mvwaddch(window, y, x, PLAYER);
		}else if(toupper(ch) == 'W') {
			maze->map[y][x] = WALL;
			mvwaddch(window, y, x, WALL);
		}else if(toupper(ch) == 'G') {
			maze->map[y][x] = GROUND;
			mvwaddch(window, y, x, GROUND);
		}else if(toupper(ch) == 'S') {

			maze->map[start_y][start_x] = GROUND;
			mvwaddch(window, start_y, start_x, GROUND);

			start_x = x;
			start_y = y;

			maze->map[start_y][start_x] = START;
			mvwaddch(window, start_y, start_x, START);
		}else if(toupper(ch) == 'F') {

			maze->map[exit_y][exit_x] = GROUND;
			mvwaddch(window, exit_y, exit_x, GROUND);

			exit_x = x;
			exit_y = y;

			maze->map[exit_y][exit_x] = EXIT;
			mvwaddch(window, exit_y, exit_x, EXIT);
		}else if(toupper(ch) == 'E') {
			
			if(confirmation_message("Save level and return to main menu", "Are you sure you want to save the level and exit")){
				delwin(window);
				delwin(help);
				return;
			}

			clear();
			refresh();

			redrawwin(window);

			redrawwin(help);
			wrefresh(help);
		}else if(toupper(ch) == 'D') {
			
			if(confirmation_message("Delete level and return to main menu", "Are you sure you want to delete the level and exit")){
				mazes->erase(mazes->begin() + index);
				delwin(window);
				delwin(help);
				return;
			}

			clear();
			refresh();

			redrawwin(window);
			redrawwin(help);
			wrefresh(help);
		}

		wrefresh(window);
	}

	return;
}


int main(int argc, char *argv[])
{
	initscr();
	//start_color();
	//init_pair(1, COLOR_GREEN, COLOR_BLACK);


	curs_set(FALSE);
	refresh();


	keypad(stdscr, TRUE);
	noecho();

	std::vector<Maze> mazes;
	load_mazes(&mazes);

	while(true){

		clear();
		refresh();

		std::vector<std::string> main_menu = {
			"Exit",
			"Add level"
		};

		for (Maze maze: mazes) {
			main_menu.push_back(maze.title);
		}

		int item = menu("Welcome to maze levels editor", main_menu);

		if(item == 0){
			if(confirmation_message("Exit from editor", "Are you sure you want to exit from editor")){
				save_mazes(&mazes);
				break;
			}
		}else if(item == 1){
			clear();
			refresh();

			echo();
			curs_set(TRUE);

			addstr("Enter level name:");
			
			Maze maze = new_maze();
			getstr(maze.title);
			mazes.push_back(maze);

			noecho();
			curs_set(FALSE);
			
			edit(&mazes, mazes.size()-1);

		}else{
			edit(&mazes, item - 2);
		}
	}

	endwin();
}