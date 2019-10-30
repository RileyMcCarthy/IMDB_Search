#include "name.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name_basics *get_name (char *fileDir) {
  char *filename = "/testData.tsv";
  char *directory = malloc(strlen(filename) + strlen(fileDir) +1);
  char BUFFER[256];
  char dataBUFFER[256];
  int actorCount = 0;
  FILE *fp;
  strcpy(directory, fileDir);
  strcat(directory,filename);

  printf("%s\n",directory);
  fp = fopen(directory, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
  }

  fgets(BUFFER, 256, fp);
  while ( fgets(BUFFER, 256, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    get_column (BUFFER, dataBUFFER, 4);
    printf("%s\n",dataBUFFER);
    if (csvContains(dataBUFFER, "actor") == 1) {
      printf("found actor\n");
      actorCount++;
    }else if(csvContains(dataBUFFER, "actress") == 1){
      printf("found actress\n");
      actorCount++;
    }
  }
  printf("Actor/actress count is: %d\n",actorCount);

  fclose(fp);
  free(directory);
}
