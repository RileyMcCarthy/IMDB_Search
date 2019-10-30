#include "name.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name_basics *get_name (char *fileDir) {
  char *filename = "/testData.tsv";
  char *directory = malloc(strlen(filename) + strlen(fileDir) +1);
  char BUFFER[256];
  FILE *fp;
  strcpy(directory, fileDir);
  strcat(directory,filename);

printf("%s\n",directory);
  fp = fopen(directory, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
  }
  while ( fgets(BUFFER, 256, fp) != NULL ) {
    printf("%s",BUFFER);
  }

}
