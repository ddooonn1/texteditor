#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#define MAX_FILENAME_SIZE 100 
#define MAX_TEXT_LENGTH 1000
#define MAX_FILES 10 
#define CTRL_X 24

void display_menu(){
  printf("\nBasic Text Editor\n");
  printf("----------------\n");
  printf("1. Write a new text.\n");
  printf("2. Open an existing file.\n");
  printf("\nPlease enter your option to start: ");
}

void list_text_files(){
  printf("\nExisting text files in directory:\n");
}

void write_new_text(){
  char filename[MAX_FILENAME_SIZE];
  char buffer[MAX_TEXT_LENGTH];
  int length = 0;

  printf("\nEnter your filename: \n");
  fgets(filename, sizeof(filename), stdin);
  filename[strcspn(filename, "\n")] = 0;

  if (!strstr(filename, ".txt")){
    strcat(filename, ".txt");
  }

  FILE *file = fopen(filename, "w");
  if (file == NULL){
    printf("Error creating a file.\n");
    return;
  }

  initscr();             // Initialize ncurses mode
  raw();                 // Disable line buffering
  keypad(stdscr, TRUE);  // Enable reading of function keys (e.g., arrow keys)
  noecho();              // Disable automatic echoing of typed characters

  int ch;
  int x = 0, y = 0;      // Initialize cursor position

  mvprintw(LINES - 2, 0, "Ctrl-X to save and exit");  // Print instruction at the bottom of the screen
  move(y, x);            // Move cursor to the initial position

  while ((ch = getch()) != CTRL_X) {  // Main loop to read user input until Ctrl-X is pressed
    switch (ch) {
      case KEY_BACKSPACE:
      case 127:  // Handle backspace/delete key
        if (x > 0) {
          mvdelch(y, --x);  // Decrement x, then delete character at (y, x)
          buffer[--length] = '\0';  // Decrement length and null-terminate the buffer
        }
        break;
      case '\n':  // Handle newline
        buffer[length++] = ch;  // Add newline character to buffer
        y++;     // Move cursor to the next line
        x = 0;   // Reset cursor to the beginning of the line
        move(y, x);  // Move cursor to the new position
        break;
      default:     // Handle regular characters
        buffer[length++] = ch;  // Add character to buffer
        addch(ch);  // Print character to screen
        x++;        // Move cursor to the next position
        break;
    }
  }

  buffer[length] = '\0';  // Null-terminate the buffer

  endwin();  // End ncurses mode

  fprintf(file, "%s", buffer);  // Write buffer to file
  fclose(file);  // Close the file

  printf("File '%s' saved successfully as a .txt file.\n", filename);
}

void open_text_file(){
  list_text_files();

  char *fileMap[MAX_FILES];
  int fileNumber;
  char buffer[MAX_TEXT_LENGTH];

  // Streamline reading all text files in the directory
  FILE *fp = popen("ls *.txt", "r");
  if (fp == NULL){
    perror("Error when reading files.\n");
    printf("Error listing text files\n");
  }

  // Map txt file to number
  int i=1;
  char line[MAX_FILENAME_SIZE];
  while (fgets(line, sizeof(line), fp) != NULL && i<MAX_FILES){
    line[strcspn(line, "\n")] = 0;
    fileMap[i] = strdup(line);
    printf("%d. %s\n", i, line);
    i++;
  }
  pclose(fp);

  // Get input from user
  printf("\nEnter the file number to open: ");
  scanf("%d", &fileNumber);
  getchar();
  if (fileNumber < 1 || fileNumber >= i){
    printf("Invalid file number. Please try again.\n");
    return;
  }

  // Open file from filename
  char filename[MAX_FILENAME_SIZE];
  strcpy(filename, fileMap[fileNumber]);
  FILE *file = fopen(filename, "r");
  if (file == NULL){
    printf("Error opening file.\n");
    return;
  }
 
  // Free allocated memory
  for (int j=1; j<i; j++){
    free(fileMap[j]);
  }

  int x = 0, y = 0;
  while (fgets(buffer, sizeof(buffer), file)) {  // Read file line by line
    mvprintw(y++, 0, "%s", buffer);  // Print each line to the screen
  }
  move(0, 0);  // Move cursor to the initial position

  int ch;
  while ((ch = getch()) != CTRL_X) {  // Main loop to read user input until Ctrl-X is pressed
    switch (ch) {
      case KEY_BACKSPACE:
      case 127:  // Handle backspace/delete key
        if (x > 0) {
          mvdelch(y, --x);  // Delete character from screen
        }
        break;
      case '\n':  // Handle newline
        y++;     // Move cursor to the next line
        x = 0;   // Reset cursor to the beginning of the line
        move(y, x);
        break;
      default:     // Handle regular characters
        addch(ch);  // Add character to the screen
        x++;        // Move cursor to the next position
        break;
    }
  }

  endwin();  // End ncurses mode
  fclose(file);  // Close the file
}

int main(){
  int choice;
  do {
    display_menu();
    scanf("%d", &choice);
    getchar();
    switch (choice) {
      case 1:
        write_new_text();
        break;
      case 2:
        open_text_file();
        break;
      default:
        printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 1 && choice != 2);
  return 0;
}

