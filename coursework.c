#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countlines(char *filename) {
  FILE *file = fopen(filename,"r");
  int lines = 0;
  char character;
  while ((character = fgetc(file)) != EOF) {
    if (character == '\n') {
      lines++;
    }
  }
  fclose(file);
  return lines;
}

int countcharacters(char *filename) {
  FILE *file = fopen(filename,"r");
  int characters = 0;
  while ((fgetc(file)) != EOF) {
    characters++;
  }
  fclose(file);
  return characters;
}

int countcodelines(char *filename) {
  FILE *file = fopen(filename,"r");
  int codelines = 0;
  char line[1024];
  while (fgets(line,1024, file)) {
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
  FILE *file = fopen(filename,"r");
  char line[1024];
  filename[strlen(filename)-1] = '\0';
  filename = strcat(filename,"o\0");
  FILE *outfile = fopen(filename,"w");
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
  FILE *file = fopen(filename,"r");
  int brackets = 0;
  int bracketscurl = 0;
  int bracketssquare = 0;
  char character;
  while ((character = fgetc(file)) != EOF) {
    if (character == '{') {
      bracketscurl++;
    } else if (character == '[') {
      bracketssquare++;
    } else if (character == '(') {
      brackets++;
    } else if (character == ')') {
      brackets--;
    } else if (character == ']') {
      bracketssquare--;
    } else if (character == '}') {
      bracketscurl--;
    }
  }
  fclose(file);
  //printf("%d %d %d", brackets, bracketscurl, bracketssquare);
  if (brackets == 0 && bracketscurl == 0 && bracketssquare == 0) {
    return "balanced";
  } else {
    return "unbalanced";
  }
}
int functioncount (char *filename) {
  FILE *file = fopen(filename,"r");
  int functions = 0;
  int counter = 0;
  char line[1024];
  char *words[1024];
  char *word;

  while (fgets(line,1024, file)) {

    word = strtok (line, " ");
    while (word != NULL) {
      words[counter++] = word;
      word = strtok(NULL, " ");

    }
    if (strcmp(words[0], "int") == 0 || strcmp(words[0],"double") == 0|| strcmp(words[0],"void") == 0 && strcmp(words[2],"(") == 0) {
      functions++;
    }
  }
  return functions;
}

int help () {
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
  } else if (strcmp(argv[1], "--help" ) == 0) {
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
    printf("Lines: %d\n", countlines(argv[2]));
    printf("Characters: %d\n", countcharacters(argv[2]));
    printf("Code lines: %d\n", countcodelines(argv[2]));
    printf("No comment file saved as: %s\n",removecomments(argv[2]));
    printf("Brackets are %s\n", balancebrackets(argv[2]));
    printf("There are %d functions\n", functioncount(argv[2]));
  } else {
    printf("Error %s is not a valid argument\n", argv[1]);
  }
  return 0;
}
