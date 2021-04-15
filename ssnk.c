/* See LICENSE file for copyright and license details. */

#define _POSIX_C_SOURCE 199309L

#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"

enum dir {
	LEFT, DOWN, UP, RIGHT
};

/* global variables */
int width;
int height;
struct node *snk;
int len;
enum dir dir;
int food_x;
int food_y;
bool gameover;

/* clean up on exit */
void cleanup(void)
{
	endwin();
	free_nodes(snk);
}

/* initial setup */
void setup(void)
{
	setlocale(LC_ALL, "");
	initscr(); cbreak(); noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	timeout(0);
	curs_set(0);

	getmaxyx(stdscr, height, width);
	width = (width + 1) / 2;

	snk = new_node(width / 2, 0, NULL);
	if (!snk) {
		cleanup();
		exit(EXIT_FAILURE);
	}

	len = 1;
	dir = DOWN;

	srand(time(0));

	do {
		food_x = rand() % width;
		food_y = rand() % height;
	} while (snk->x == food_x && snk->y == food_y);
	
	gameover = false;
}

/* listen for key press */
void input(void)
{
	char c = getch();
	if (c == 'h' && (dir != RIGHT || len == 1))
		dir = LEFT;
	else if (c == 'j' && (dir != UP || len == 1))
		dir = DOWN;
	else if (c == 'k' && (dir != DOWN || len == 1))
		dir = UP;
	else if (c == 'l' && (dir != LEFT || len == 1))
		dir = RIGHT;
	else if (c == 'q')
		gameover = true;
}

/* move snake, check for collision, handle food */
void logic(void)
{
	switch (dir) {
	case LEFT:
		snk = new_node(snk->x - 1, snk->y, snk);
		break;
	case DOWN:
		snk = new_node(snk->x, snk->y + 1, snk);
		break;
	case UP:
		snk = new_node(snk->x, snk->y - 1, snk);
		break;
	case RIGHT:
		snk = new_node(snk->x + 1, snk->y, snk);
		break;
	default:
		break;
	}

	if (!snk) {
		cleanup();
		exit(EXIT_FAILURE);
	}

	if (snk->x < 0)
		snk->x = width - 1;
	else if (snk->x >= width)
		snk->x = 0;
	else if (snk->y < 0)
		snk->y = height - 1;
	else if (snk->y >= height)
		snk->y = 0;

	if (node_exists(snk->next, snk->x, snk->y))
		gameover = true;

	if (snk->x == food_x && snk->y == food_y) {
		do {
			food_x = rand() % width;
			food_y = rand() % height;
		} while (node_exists(snk, food_x, food_y));
		++len;
	} else {
		delete_last(snk);
	}
}

/* draw snake and food */
void draw(void)
{
	clear();
	struct node *cursor = snk;
	while (cursor) {
		mvprintw(cursor->y, cursor->x * 2, "o");
		cursor = cursor->next;
	}
	mvprintw(food_y, food_x * 2, "+");
	refresh();
}

int main(void)
{
	setup();

	while (!gameover) {
		input();
		logic();
		draw();

		struct timespec ts;
		ts.tv_sec = 0;
		ts.tv_nsec = 100000000;
		nanosleep(&ts, &ts);
	}

	cleanup();
	return EXIT_SUCCESS;
}
