// Author Alexander Hallard
// Purpose analysis of c source files

// Import required libaries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to countlines
int countlines(char *filename) {
  FILE *file = fopen(filename,"r");
  int lines = 0;
  char character;

  while ((character = fgetc(file)) != EOF) { // get characters from file while not end of file character
    if (character == '\n') {
      lines++;
    }
  }

  fclose(file);
  lines++; // Add one more line as the last line does not contain a \n character

  return lines;
}

int countcharacters(char *filename) {
  FILE *file = fopen(filename,"r");
  int characters = 0;
  while ((fgetc(file)) != EOF) { // get characters from file while not end of file character
    characters++;
  }
  fclose(file);
  return characters;
}

int countcodelines(char *filename) {
  int codelines = 0;
  char line[1024];

  FILE *file = fopen(filename,"r");

  while (fgets(line,1024, file)) { // get characters from file while not end of file
    if (line[0] == '/' && line[1] == '/' && line[2] == ' ') {
      continue;
    } else if (line[0] == '\n') {
      continue;
    } else if (line[0] == '\t' && line[1] == '\n'){
      continue;
    } else {
      codelines++;
    }
  }

  fclose(file);
  return codelines;
}

const char * removecomments(char *filename) {
  char line[1024];


  FILE *file = fopen(filename,"r");
  filename[strlen(filename)-1] = '\0';

  char *ofilename = strcat(filename,"o\0");
  FILE *outfile = fopen(ofilename,"w");

  while (fgets(line,1024, file)) {
    if (line[0] == '/' && line[1] == '/' && line[2] == ' ') {
      continue;
    } else {
      fprintf(outfile, "%s", line);
    }
  }

  fclose(file);
  fclose(outfile);
  return filename;
}

const char * balancebrackets(char *filename) {
  char bracketStack[1024];
  int p = 0;

  char character;
  FILE *file = fopen(filename,"r");

  while ((character = fgetc(file)) != EOF) {

    switch (character) {
    case '"':
      /* iterate till next " */
      character = fgetc(file); 
      while (character != EOF && character != '"') { 
        if (character == '\\') {
          fgetc(file);
        }
        character = fgetc(file); 
      }
      break;
    
    case '\'':
      /* iterate till next ' */
      character = fgetc(file); 
      while (character != EOF && character != '\'') { 
        if (character == '\\') {
          fgetc(file);
        }
        character = fgetc(file); 
      }
      break;

    case '\\':
      /* skip next character */
      character = fgetc(file);
      break;
    
    case '/':
      /* checks if the next character is the same, otherwise runs defaults */
      character = fgetc(file);
      if (character == '/') { // Single line comment
        while (character != EOF && character != '\n') { 
          character = fgetc(file); 
        }
        break;

      } else if (character == '*') { // Multi line commment
        while (character != EOF && (character != '*' || (character = fgetc(file)) != '/') ) {
          if (character != EOF) {
            character = fgetc(file);
          }
        }
        break;
      
      }else if (character == EOF) { // End of document
        break;
      }

    default:
      /* Bracket balencing */
      // Check for brackets
      switch (character) {
        case '(':
          bracketStack[p++] = '(';
          break;
        case '{':
          bracketStack[p++] = '{';
          break;
        case '[':
          bracketStack[p++] = '[';
          break;
        case ')':
          p--;
          if (p == -1 || bracketStack[p] != '(') { return "unbalenced"; }
          break;
        case '}':
          p--;
          if (p == -1 || bracketStack[p] != '{') { return "unbalenced"; }
          break;
        case ']':
          p--;
          if (p == -1 || bracketStack[p] != '[') { return "unbalenced"; }
          break;
        
        default:
          break;
      }
    }
  }
  fclose(file);

  if (p == 0) {
    return "balanced";
  }
  return "unbalenced";
}

int functioncount (char *filename) {
  int functions = 0;
  int counter = 0;
  char line[1024];
  char *words[1024];
  char *word;

  FILE *file = fopen(filename,"r");

  while (fgets(line,1024, file)) {
    word = strtok (line, " "); //Inital word split at space

    while (word != NULL) {
      words[counter++] = word;
      word = strtok(NULL, " ");

    }

    if (strcmp(words[0], "int") == 0 || strcmp(words[0],"double") == 0 || strcmp(words[0],"void") == 0 && strcmp(words[2],"(") == 0) {
      functions++;
    }
  }
  return functions;
}

void help () {
  printf("\
\n░█████╗░░█████╗░███╗░░██╗░█████╗░██╗░░░░░██╗░░░██╗░██████╗███████╗\
\n██╔══██╗██╔══██╗████╗░██║██╔══██╗██║░░░░░╚██╗░██╔╝██╔════╝██╔════╝\
\n██║░░╚═╝███████║██╔██╗██║███████║██║░░░░░░╚████╔╝░╚█████╗░█████╗░░\
\n██║░░██╗██╔══██║██║╚████║██╔══██║██║░░░░░░░╚██╔╝░░░╚═══██╗██╔══╝░░\
\n╚█████╔╝██║░░██║██║░╚███║██║░░██║███████╗░░░██║░░░██████╔╝███████╗\
\n░╚════╝░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚══════╝░░░╚═╝░░░╚═════╝░╚══════╝\n");

  printf("Canalyse v1\n");
  printf("Usage: canalyse [options] file\n\n");
  printf("Canalyse is a commandline c source files analysis tool\n");
  printf("\nOptions: [--countlines] count all lines including comments and whitespace");
  printf("\n         [--countcharacters] count all characters");
  printf("\n         [--countcodelines] count all lines of code");
  printf("\n         [--removecomments] remove all comments and out a .o file with the same name");
  printf("\n         [--balancebrackets] check that all brackets are balanced");
  printf("\n         [--functioncount] count the number of functions");
  printf("\n         [--all] run all checks");
  printf("\n         [--help] display this message\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error no arguments provided\n");
    return 1;

  } else if (strcmp(argv[1], "--help" ) == 0) { //If first argument matches
    help();

  } else if (strcmp(argv[1], "--countlines") == 0) {
    printf("Counting lines of file %s\n", argv[2]);
    printf("Lines: %d\n", countlines(argv[2]));

  } else if (strcmp(argv[1], "--countcharacters") == 0) {
    printf("Counting characters of file %s\n", argv[2]);
    printf("Characters: %d\n", countcharacters(argv[2]));

  } else if (strcmp(argv[1], "--countcodelines") == 0) {
    printf("Counting code lines of file %s\n", argv[2]);
    printf("Code lines: %d\n", countcodelines(argv[2]));

  } else if (strcmp(argv[1], "--removecomments") == 0) {
    printf("Removing comments of file %s\n", argv[2]);
    printf("No comment file saved as: %s\n",removecomments(argv[2]));

  } else if (strcmp(argv[1], "--balancebrackets") == 0) {
    printf("Checking if brackets are balanced of file %s\n", argv[2]);
    printf("Brackets are %s\n", balancebrackets(argv[2]));

  } else if (strcmp(argv[1], "--functioncount") == 0) {
    printf("Counting functions in file %s\n", argv[2]);
    printf("There are %d functions\n", functioncount(argv[2]));

  } else if (strcmp(argv[1], "--all") == 0) {
    printf("Running all checks on file %s\n", argv[2]);
    printf("There are %d functions\n", functioncount(argv[2]));
    printf("Lines: %d\n", countlines(argv[2]));
    printf("Characters: %d\n", countcharacters(argv[2]));
    printf("Code lines: %d\n", countcodelines(argv[2]));
    printf("No comment file saved as: %s\n",removecomments(argv[2]));
    printf("Brackets are %s\n", balancebrackets(argv[2]));


  } else {
    printf("Error %s is not a valid argument\n", argv[1]);
  }
  return 0;
}
