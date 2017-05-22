/**
 * alien-console: a clone of the Alien: Isolation "personal terminal"
 * Copyright (c) 2017 Stephen Brennan. Released under the Revised BSD License.
 */
#include <ncurses.h>

#include "alien-console.h"

static struct splash_params params = {
	/* figlet -f slant nostromolink > splash.txt */
	.filename = "splash.txt",
	.tagline = "AN SM-LINK PRODUCT",
	.copyright = "(C) SM-LINK DATA SYSTEMS",
};

int main(int argc, char *argv[])
{
	int rv;

	(void) argc;
	(void) argv;

	/* ncurses initialization */
	initscr();            /* initialize curses */
	cbreak();             /* pass key presses to program, but not signals */
	noecho();             /* don't echo key presses to screen */
	keypad(stdscr, TRUE); /* allow arrow keys */
	timeout(0);           /* no blocking on getch() */
	curs_set(0);          /* set the cursor to invisible */

	rv = splash(&params); /* display splash screen */
	if (rv < 0) {
		mark_error();
		goto exit;
	}

	// Deinitialize NCurses
exit:
	wclear(stdscr);
	endwin();
	if (rv < 0) {
		report_error(stderr);
		return rv;
	}
	return 0;
}
