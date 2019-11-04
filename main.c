#include "name.h"
#include "title.h"
#include "binary.h"
#include "common.h"
#include "principals.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
  char BUFFER[1000];
  char command[1000];
  char parameter[1000];
  int i = 0;
  int len;
  int cStart = 0;
  int cEnd = 0;
  int pStart = 0;
  int pEnd = 0;
  int cSize = 0;
  int pSize = 0;
  struct tarray_info *titleBasics = NULL;
  struct narray_info *nameBasics= NULL;
  struct parray_info *titlePrincipals= NULL;
  struct title_basics *title= NULL;
  struct title_principals *principals= NULL;
  struct name_basics *name= NULL;
  struct tree_basics *allnconst= NULL;

  if (argc == 1) {
    printf("error, no directory command line input was given\n");
    return -1;
  }
  printf("%s\n",argv[1]);

  titleBasics = get_title(argv[1]);
  build_ptindex(titleBasics);
  build_tconstIndex(titleBasics);
  nameBasics = get_name(argv[1]);
  build_pnindex(nameBasics);
  build_nconstIndex(nameBasics);
  titlePrincipals = get_principals(argv[1]);
  build_tconstIndex_tp(titlePrincipals);
  build_nconstIndex_tp(titlePrincipals);
  while (1==1) {
    memset(BUFFER,0,sizeof(BUFFER));
    memset(command,0,sizeof(command));
    memset(parameter,0,sizeof(parameter));
    printf(">>");
    fgets(BUFFER,1000,stdin);
    len = strlen(BUFFER);
    for (i=0;i<len;i++) {
      if (BUFFER[i] != ' ') {
        cStart = i;
        break;
      }
    }
    for (i=cStart;i<len;i++) {
      if (BUFFER[i] == ' ') {
        cEnd = i;
        break;
      }
    }
    for (i=cEnd;i<len;i++) {
      if (BUFFER[i] != ' ') {
        pStart = i;
        break;
      }
    }
    for (i=(len-2);i>0;i--) {
      if (BUFFER[i] != ' ') {
        pEnd = i;
        break;
      }
    }
    cSize = cEnd - cStart;
    strncpy(command,&BUFFER[cStart],cSize);
    command[strlen(command)] = '\0';
    pSize = pEnd - pStart+1;
    strncpy(parameter,&BUFFER[pStart],pSize);
    parameter[strlen(parameter)] = '\0';
    if (strncmp(command,"name",4) == 0) {
      printf("Searching name:%s\n",parameter);
      name = (struct name_basics *)find_primary_name(nameBasics,parameter);
      if (name == NULL) {
      } else {
        allnconst = find_nconst_tp_all(titlePrincipals,name->nconst);

        while(allnconst != NULL) {
          principals = (struct title_principals *)allnconst->data;
          if (strcmp(principals->nconst,name->nconst) == 0) {
              title = (struct title_basics *)find_tconst(titleBasics,principals->tconst);
              if (title != NULL) {
                printf("%s : ",title->primaryTitle);
                printf("%s\n",principals->characters);
              }else {
              }
          }
          allnconst = (allnconst->left);
        }
      }
    }else if (strncmp(command,"title",4) == 0) {
      title = (struct title_basics *)find_primary_title(titleBasics,parameter);
      if (title == NULL) {
      }else {
        allnconst = find_tconst_tp_all(titlePrincipals,title->tconst);
        while (allnconst != NULL) {
          principals = (struct title_principals *)allnconst->data;
          if (strcmp(principals->tconst,title->tconst) == 0) {
            name = find_nconst(nameBasics,principals->nconst);
            printf("%s : %s\n",name->primaryName,principals->characters);
          }

          allnconst = allnconst->left;
        }
      }
    }else {
    }
  }
  return 0;
}
