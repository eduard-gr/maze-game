#include "menu.hpp"
#include <curses.h>
#include <string.h> //strlen
#include <algorithm> //max

int menu(const char *title, std::vector<std::string> items){
	refresh();

	int first = 3;
	int selected = first;
	int last = first + items.size() - 1;

	WINDOW *window = newwin(
		last + 2,
		50,
		1,
		1);

	wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(window, 1, 1, title);
	mvwhline(window, 2, 1, '-', 48);

	for (int i = 0; i < items.size(); i++){
		mvwprintw(window, first + i, 4, items[i].c_str());
	};

	mvwprintw(window, selected, 1, "->");

	wrefresh(window);

	while(1) {
		int ch = getch();

		if(ch == KEY_UP) {
			if(selected <= first) {
				continue;
			}

			mvwprintw(window, selected, 1, "  ");
			selected--;
			mvwprintw(window, selected, 1, "->");
		}else if(ch == KEY_DOWN) {
			
			if(selected >= last) {
				continue;
			}

			mvwprintw(window, selected, 1, "  ");
			selected++;
			mvwprintw(window, selected, 1, "->");
		}else if(ch == KEY_ENTER || ch == 10) {
			delwin(window);
			return selected - first;
		}

		wrefresh(window);
	}

}


bool confirmation_message(const char *title, const char *question){

	int width = std::max(strlen(title), strlen(question)) + 4;

	WINDOW *window = newwin(
		8,
		width,
		5,
		10);

	wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(window, 1, 2, title);
	mvwhline(window, 2, 1, '-', width - 2);
	mvwprintw(window, 3, 2, question);

	mvwprintw(window, 5, 4, "Yes");
	mvwprintw(window, 6, 4, "No");

	int offset = 5;
	int selected = 0;

	mvwprintw(window, offset + selected, 1, "->");

	wrefresh(window);

	while(1) {
		int ch = getch();

		if(ch == KEY_UP) {
			if(selected <= 0) {
				continue;
			}

			mvwprintw(window, offset + selected, 1, "  ");
			selected--;
			mvwprintw(window, offset + selected, 1, "->");
		}else if(ch == KEY_DOWN) {
			
			if(selected >= 1) {
				continue;
			}

			mvwprintw(window, offset + selected, 1, "  ");
			selected++;
			mvwprintw(window, offset + selected, 1, "->");
		}else if(ch == KEY_ENTER || ch == 10) {
			werase(window);
			delwin(window);
			return !selected;
		}

		wrefresh(window);
	}
}