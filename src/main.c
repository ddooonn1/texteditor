#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILENAME_SIZE 100 
#define MAX_TEXT_LENGTH 1000
#define MAX_FILES 10 

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
  char content[MAX_TEXT_LENGTH];

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

  printf("\nPlease write the content to the file below: (end with a single dot on a new line)\n");
  printf("[type 'exit' on a new line to quit]\n");
  while (1){
    fgets(content, MAX_TEXT_LENGTH, stdin);
    if (strcmp(content, "exit\n") == 0) {
      break;  // Exit loop if user types 'exit'
    }
    fprintf(file, "%s", content);
  }

  fclose(file);
  printf("File '%s' saved successfully as a .txt file.\n", filename);
}

void open_text_file(){
  list_text_files();

  char *fileMap[MAX_FILES];
  int fileNumber;

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

  printf("\n%s's content\n", filename);
  printf("----------------\n");
  // Print content from txt file
  char content[MAX_TEXT_LENGTH];
  while (fgets(content, MAX_TEXT_LENGTH, file) != NULL){
    printf("%s", content);
  }
  fclose(file);

  // Free allocated memory
  for (int j=1; j<i; j++){
    free(fileMap[j]);
  }
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

