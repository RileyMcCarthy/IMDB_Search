#include "name.h"
#include "title.h"
#include "principals.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

int main () {
  struct title_principals *head;
  int i = 0;
  int index;
  /*index = get_name("dataFiles", &head);

  printf("PRINTING %d\n", index);
  for (i=0;i<20;i++) {
    printf("%d. %s,  %s\n",i,head[i].nconst,head[i].primaryName);
  }

  for (i=0;i<index;i++) {
    free(head[i].nconst);
    free(head[i].primaryName);
  }
  free(head);*/

  /*index = get_title("dataFiles",&head);
  printf("PRINTING %d\n", index);
  for (i=0;i<10;i++) {
    printf("%d. %s,  %s\n",i,head[i].tconst,head[i].primaryTitle);
  }

  for (i=index;i>(index-10);i--) {
    printf("%d. %s,  %s\n",i,head[i].tconst,head[i].primaryTitle);
  }

  for (i=0;i<index;i++) {
    free(head[i].tconst);
    free(head[i].primaryTitle);
  }
  free(head);*/

  index = get_principals("dataFiles",&head);
  printf("PRINTING %d\n", index);
  for (i=0;i<10;i++) {
    printf("%s. %s,  %s\n",head[i].nconst,head[i].tconst,head[i].characters);
  }

  for (i=index-1;i>(index-10);i--) {
    printf("%s. %s,  %s\n",head[i].nconst,head[i].tconst,head[i].characters);
  }


  return 0;
}
