#include "binary.h"
#include "common.h"
#include "principals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct parray_info *get_principals (char *fileDir) {
  char *filename = "/title.principals(1).tsv";
  char *directory = malloc(strlen(filename) + strlen(fileDir) +1);
  char BUFFER[1000];
  char dataBUFFER[1000];
  char charactersBUFFER[1000];
  char nconstBUFFER[1000];
  char tconstBUFFER[1000];
  struct parray_info *info;
  struct title_principals *head;
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
  while ( fgets(BUFFER, 1000, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    get_column (BUFFER, dataBUFFER, 3);
    if (strcmp(dataBUFFER,"actor")==0 || strcmp(dataBUFFER, "actress")==0) {
      memset(dataBUFFER,0,sizeof(dataBUFFER));
      titleCount++;
    }
    memset(BUFFER,0,sizeof(BUFFER));
  }

  printf("Movie count is: %d\n",titleCount);

  /*now creating the array of actor/actress values*/
  memset(dataBUFFER,0,sizeof(dataBUFFER)); /*TODO test to make sure adding this line didnt fuck shit up*/
  memset(BUFFER,0,sizeof(BUFFER));
  head = malloc (sizeof(struct title_principals)*titleCount);
  fseek( fp, 0, SEEK_SET );
  fgets(BUFFER, 1000, fp);
  while ( fgets(BUFFER, 1000, fp) != NULL ) {
    memset(dataBUFFER,0,sizeof(dataBUFFER));
    memset(charactersBUFFER,0,sizeof(charactersBUFFER));
    memset(nconstBUFFER,0,sizeof(nconstBUFFER));
    memset(tconstBUFFER,0,sizeof(tconstBUFFER));
    get_column (BUFFER, dataBUFFER, 3);

    if (strcmp(dataBUFFER,"actor") == 0 || strcmp(dataBUFFER, "actress")==0) {
      memset(dataBUFFER,0,sizeof(dataBUFFER));
      get_column (BUFFER, charactersBUFFER, 5);
      head[index].characters = malloc(strlen(charactersBUFFER)+1);
      strcpy(head[index].characters,charactersBUFFER);
      get_column (BUFFER, tconstBUFFER, 0);
      head[index].tconst = malloc(strlen(tconstBUFFER)+1);
      strcpy(head[index].tconst,tconstBUFFER);
      get_column (BUFFER, nconstBUFFER, 2);
      head[index].nconst = malloc(strlen(nconstBUFFER)+1);
      strcpy(head[index].nconst,nconstBUFFER);
      index++;
    }
    memset(BUFFER,0,sizeof(BUFFER));
  }
  free(directory);
  fclose(fp);

  /*setting up info struct*/
  info = malloc (sizeof(struct parray_info));
  info->numItems = index;
  info->head = head;
  return info;

}

void build_nconstIndex_tp (struct parray_info *info) {
  int i = 0;
  info->tree2 = NULL;
  char *rev;
  for (i=0;i<info->numItems;i++) {
    rev = reverse((info->head[i]).nconst);
    add_node(&(info->tree2), rev, &(info->head[i]) );
  }
}

void build_tconstIndex_tp (struct parray_info *info) {
  int i = 0;
  info->tree1 = NULL;
  char *rev;
  for (i=0;i<info->numItems;i++) {
    rev = reverse((info->head[i]).tconst);
    add_node(&(info->tree1), rev, &(info->head[i]) );
  }
}

struct title_principals *find_nconst_tp (struct parray_info *root, char *target) {
  char *rev;
  rev = reverse(target);
  return (find_node(root->tree2,rev)->data);
}

struct title_principals *find_tconst_tp (struct parray_info *root, char *target) {
  char *rev;
  rev = reverse(target);
  return (find_node(root->tree1,rev)->data);
}
