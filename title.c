#include "binary.h"
#include "common.h"
#include "title.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_title (char *fileDir, struct title_basics **head) {
  char *filename = "/title.basics.tsv";
  char *directory = malloc(strlen(filename) + strlen(fileDir) +1);
  char BUFFER[1000];
  char dataBUFFER[1000];
  char titleBUFFER[1000];
  char tconstBUFFER[1000];
  int titleCount = 0;
  int index = 0;
  int i = 0;
  FILE *fp;

  strcpy(directory, fileDir);
  strcat(directory,filename);

  printf("%s\n",directory);
  fp = fopen(directory, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
  }

  fgets(BUFFER, 1000, fp);
  int count = 0;
  while ( fgets(BUFFER, 1000, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    get_column (BUFFER, dataBUFFER, 1);
    if (strcmp(dataBUFFER,"movie")==0) {
      memset(dataBUFFER,0,sizeof(dataBUFFER));
      get_column (BUFFER, dataBUFFER, 4);
      if (strcmp(dataBUFFER,"0")==0) {
        titleCount++;
      }
    }
    memset(BUFFER,0,sizeof(BUFFER));
  }

  printf("Movie count is: %d\n",titleCount);
  if(titleCount == 0) {
    return -1;
  }

  /*now creating the array of actor/actress values*/
  memset(dataBUFFER,0,sizeof(dataBUFFER)); /*TODO test to make sure adding this line didnt fuck shit up*/
  memset(BUFFER,0,sizeof(BUFFER));
  (*head) = malloc (sizeof(struct title_basics)*titleCount);
  fseek( fp, 0, SEEK_SET );
  fgets(BUFFER, 1000, fp);
  while ( fgets(BUFFER, 1000, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    memset(titleBUFFER,0,sizeof(titleBUFFER));
    memset(tconstBUFFER,0,sizeof(tconstBUFFER));
    get_column (BUFFER, dataBUFFER, 1);

    if (strcmp(dataBUFFER,"movie") == 0) {
      memset(dataBUFFER,0,sizeof(dataBUFFER));
      get_column (BUFFER, dataBUFFER, 4);
        if (strcmp(dataBUFFER,"0")==0) {

        get_column (BUFFER, titleBUFFER, 2);
        (*head)[index].primaryTitle = malloc(strlen(titleBUFFER)+1);
        strcpy((*head)[index].primaryTitle,titleBUFFER);

        get_column (BUFFER, tconstBUFFER, 0);
        (*head)[index].tconst = malloc(strlen(tconstBUFFER)+1);
        strcpy((*head)[index].tconst,tconstBUFFER);
        index++;
      }
    }
    memset(BUFFER,0,sizeof(BUFFER));
  }
  free(directory);
  fclose(fp);
  return index;

}
