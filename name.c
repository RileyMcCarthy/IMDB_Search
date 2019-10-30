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
  char nameBUFFER[256];
  char nconstBUFFER[256];
  int actorCount = 0;
  int index = 0;
  int i = 0;
  FILE *fp;
  struct name_basics *names;

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
  if(actorCount == 0) {
    return NULL;
  }
  /*now creating the array of actor/actress values*/
  names = malloc (sizeof(struct name_basics)*actorCount);
  fseek( fp, 0, SEEK_SET );
  fgets(BUFFER, 256, fp);
  while ( fgets(BUFFER, 256, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    memset(nameBUFFER,0,sizeof(nameBUFFER));
    memset(nconstBUFFER,0,sizeof(nconstBUFFER));
    get_column (BUFFER, dataBUFFER, 4);
    printf("%s\n",dataBUFFER);

    if (csvContains(dataBUFFER, "actor") == 1) {

      get_column (BUFFER, nameBUFFER, 1);
      names[index].primaryName = malloc(strlen(nameBUFFER)+1);
      strcpy(names[index].primaryName,nameBUFFER);

      get_column (BUFFER, nconstBUFFER, 0);
      names[index].nconst = malloc(strlen(nconstBUFFER)+1);
      strcpy(names[index].nconst,nconstBUFFER);
      index++;

    }else if(csvContains(dataBUFFER, "actress") == 1){

      get_column (BUFFER, nameBUFFER, 1);
      names[index].primaryName = malloc(strlen(nameBUFFER)+1);
      strcpy(names[index].primaryName,nameBUFFER);

      get_column (BUFFER, nconstBUFFER, 0);
      printf("    -%s\n",nconstBUFFER);
      names[index].nconst = malloc(strlen(nconstBUFFER)+1);
      strcpy(names[index].nconst,nconstBUFFER);
      index++;

    }
  }
  printf("PRINTING NAMES:\n");
  for (i=0;i<index;i++) {
    printf("%s . %s\n",names[i].nconst,names[i].primaryName);
  }
  printf("Number of names: %d",index);

  fclose(fp);
  free(directory);
  for (i=0;i<index;i++) {
    free(names[i].nconst);
    free(names[i].primaryName);
  }
  free(names);
  return names;
}
