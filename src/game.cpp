#include <iostream>
#include <stdio.h>

#include "maze.hpp"
#include "menu.hpp"
#include "logo.hpp"


void play(std::vector<Maze> *mazes){
	clear();
	refresh();

	WINDOW *help = newwin(
		5,
		30, 
		1,
		MAZE_SIZE_WIDTH + 5);

	mvwprintw(help, 1, 2, "Use arrows to move player");
	mvwhline(help, 2, 1, '-', 43);
	mvwprintw(help, 3, 2, "E - Exit from game");

	wborder(help, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(help);

	WINDOW *window = newwin(
		MAZE_SIZE_HEIGHT,
		MAZE_SIZE_WIDTH,
		1,
		1);


	for(int i=0;i<mazes->size();i++){
		Maze maze = mazes->at(i);

		int x = 1;
		int y = 1;
		maze_get_start(&maze, &x, &y);
		draw_maze(window, &maze);

		mvwaddch(window, y, x, PLAYER);
		wrefresh(window);

		redrawwin(help);
		wrefresh(help);

		while(1) {

			int ch = getch();
			char tail = maze.map[y][x];
			if(tail == START){
				tail = GROUND;
			}

			if(ch == KEY_LEFT) {
				if(x <= 0) {
					continue;
				}

				if(can_go_through(&maze, x-1,y) == false){
					continue;
				}

				
				mvwaddch(window, y, x, tail);
				x--;
				mvwaddch(window, y, x, PLAYER);
			}else if(ch == KEY_RIGHT) {
				if(x >= MAZE_SIZE_WIDTH - 1) {
					continue;
				}

				if(can_go_through(&maze, x+1,y) == false){
					continue;
				}

				mvwaddch(window, y, x, tail);
				x++;
				mvwaddch(window, y, x, PLAYER);
			}else if(ch == KEY_UP) {
				if(y <= 0) {
					continue;
				}

				if(can_go_through(&maze, x,y-1) == false){
					continue;
				}

				mvwaddch(window, y, x, tail);
				y--;
				mvwaddch(window, y, x, PLAYER);
			}else if(ch == KEY_DOWN) {
				if(y >= MAZE_SIZE_HEIGHT - 1) {
					continue;
				}

				if(can_go_through(&maze, x,y+1) == false){
					continue;
				}

				mvwaddch(window, y, x, tail);
				y++;
				mvwaddch(window, y, x, PLAYER);
			}else if(toupper(ch) == 'E') {
				
				if(confirmation_message("Exit game", "Are you sure you want to exit")){
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
			
			if(is_exit(&maze, x, y)){
				if(confirmation_message("Victory", "Go to the next level")){
					break;
				}else{
					delwin(window);
					delwin(help);
					return;
				}
			}

			wrefresh(window);
		}

	}
}

int main(int argc, char *argv[])
{

	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);



	for(int y=0;y<11;y++){
		for(int x=0;x<117;x++){
			mvaddch(y, x, logo[y][x]);
		}
	}

	mvprintw(12, 0, "Press any key...");
	refresh();

	std::cin.get();

	std::vector<Maze> mazes;
	load_mazes(&mazes);

	std::vector<std::string> main_menu = {
		"Start game",
		"Exit"
	};

	while(true){

		clear();
		refresh();

		int item = menu("Game menu", main_menu);
		if(item == 1){
			if(confirmation_message("Exit from game", "Are you sure you want to exit from game")){
				break;
			}
		}else if(item == 0){
			play(&mazes);
		}
	}

	endwin();
}