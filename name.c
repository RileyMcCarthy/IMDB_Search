#include "binary.h"
#include "name.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct narray_info *get_name (char *fileDir) {
  char *filename = "/name.basics.tsv";
  char *directory = malloc(strlen(filename) + strlen(fileDir) +1);
  char BUFFER[1000];
  struct narray_info *info;
  struct name_basics *head;
  char dataBUFFER[1000];
  char nameBUFFER[1000];
  char nconstBUFFER[1000];
  int actorCount = 0;
  int index = 0;
  FILE *fp;

  strcpy(directory, fileDir);
  strcat(directory,filename);

  printf("%s\n",directory);
  fp = fopen(directory, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
  }

  fgets(BUFFER, 1000, fp);
  while ( fgets(BUFFER, 1000, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    get_column (BUFFER, dataBUFFER, 4);
    if (csvContains(dataBUFFER, "actor") == 1) {
      actorCount++;
    }else if(csvContains(dataBUFFER, "actress") == 1){
      actorCount++;
    }
    memset(BUFFER,0,sizeof(BUFFER));
  }

  printf("Actor/actress count is: %d\n",actorCount);

  /*now creating the array of actor/actress values*/
  memset(dataBUFFER,0,sizeof(dataBUFFER));
  head = malloc (sizeof(struct name_basics)*actorCount);
  fseek( fp, 0, SEEK_SET );
  fgets(BUFFER, 1000, fp);
  while ( fgets(BUFFER, 1000, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    memset(nameBUFFER,0,sizeof(nameBUFFER));
    memset(nconstBUFFER,0,sizeof(nconstBUFFER));
    get_column (BUFFER, dataBUFFER, 4);

    if (csvContains(dataBUFFER, "actor") == 1) {

      get_column (BUFFER, nameBUFFER, 1);
      head[index].primaryName = malloc(strlen(nameBUFFER)+1);
      strcpy(head[index].primaryName,nameBUFFER);

      get_column (BUFFER, nconstBUFFER, 0);
      head[index].nconst = malloc(strlen(nconstBUFFER)+1);
      strcpy(head[index].nconst,nconstBUFFER);
      index++;

    }else if(csvContains(dataBUFFER, "actress") == 1){

      get_column (BUFFER, nameBUFFER, 1);
      head[index].primaryName = malloc(strlen(nameBUFFER)+1);
      strcpy(head[index].primaryName,nameBUFFER);

      get_column (BUFFER, nconstBUFFER, 0);
      head[index].nconst = malloc(strlen(nconstBUFFER)+1);
      strcpy(head[index].nconst,nconstBUFFER);
      index++;

    }
    memset(BUFFER,0,sizeof(BUFFER));
  }
  free(directory);
  fclose(fp);

  /*setting up info struct*/
  info = malloc (sizeof(struct narray_info));
  info->numItems = index;
  info->head = head;
  return info;
}

void build_pnindex (struct narray_info *info) {
  int i = 0;
  info->tree1 = NULL;
  for (i=0;i<info->numItems;i++) {
    add_node(&(info->tree1), (info->head[i]).primaryName, &(info->head[i]) );
  }
}

void build_nconstIndex (struct narray_info *info) {
  int i = 0;
  info->tree2 = NULL;
  char *rev;
  for (i=0;i<info->numItems;i++) {
    rev = reverse((info->head[i]).nconst);
    add_node(&(info->tree2), rev, &(info->head[i]) );
  }
}

struct name_basics *find_nconst (struct narray_info *root, char *target) {
  char *rev;
  rev = reverse(target);
  return (find_node(root->tree2,rev)->data);
}

struct name_basics *find_primary_name (struct narray_info *root, char *target) {

  return (find_node(root->tree1,target)->data);
}
