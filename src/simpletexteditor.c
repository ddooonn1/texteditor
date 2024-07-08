#include <stdio.h>
#include <string.h>
#define MAX_TEXT_LENGTH 1000

void saveFile(char *filename, char *content){
  char newFilename[100];
  sprintf(newFilename, "%s.txt", filename); // Append .txt extension to the filename
  FILE *file = fopen(newFilename, "w");
  if (file == NULL) {
    printf("Error saving file,\n");
    return;
  }
  fprintf(file, "%s", content);
  fclose(file);
}

void openFile(char *filename){
   
}

int main() {
  char text[MAX_TEXT_LENGTH] = "";  // Initialize text buffer
  char input[MAX_TEXT_LENGTH];      // Input buffer
  printf("Simple Text Editor\n");
  printf("-------------------\n");
  printf("Press any key to continue...\n");
  getchar();  // Wait for user to press a key
  printf("Enter text (type 'exit' to quit):\n");
  while (1) {
    fgets(input, MAX_TEXT_LENGTH, stdin);  // Read user input
    if (strcmp(input, "exit\n") == 0) {
      break;  // Exit loop if user types 'exit'
    }
    strcat(text, input);  // Append input to text buffer
  }
  printf("\nText entered:\n%s\n", text);  // Display the entered text
  printf("Do you want to save the file? (y/n)");
  char response[2];
  scanf("%1s", response);
  if (strcmp(response, "y") == 0){
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);
    saveFile(filename, text);
    printf("File saved successfully!\n");
  }
    return 0;
}


