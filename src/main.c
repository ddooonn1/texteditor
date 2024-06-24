#include <ncurses.h>
#include <stdlib.h>

int main() {
    WINDOW *win;
    int ch;

    // Initialize ncurses
    initscr();
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable special key input

    // Check terminal dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Create a new window
    win = newwin(height - 4, width - 4, 2, 2);  // Adjust window size and position
    box(win, 0, 0);

    // Display a message
    mvwprintw(win, 1, 1, "Welcome to the text editor");
    wrefresh(win);

    // Main loop for user input
    while ((ch = wgetch(win)) != KEY_F(1)) {
        // Process user input (example: exit on ESC key)
        if (ch == 27)  // 27 is the ASCII value for the ESC key
            break;
    }

    // Clean up and exit
    delwin(win);
    endwin();
    return 0;
}
