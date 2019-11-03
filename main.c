#include "name.h"
#include "title.h"
#include "binary.h"
#include "common.h"
#include "principals.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/*int main () {
  int i = 0;
  struct tarray_info *info;
  struct title_basics *found;
  info = get_title("dataFiles");
  printf("PRINTING %d\n", info->numItems);

  build_ptindex(info);
  printf( "%s\n", (info->tree1)->key );

  printf( "%p\n", (info->tree1)->data );


  printf("%s\n", ((struct title_basics *)(info->tree1)->data)->primaryTitle );

  printf("%s\n", ((struct title_basics *)(info->tree1)->data)->tconst );

  found = (struct title_basics *)find_primary_title(info,"Star Wars: Episode V - The Empire Strikes Back");

  printf( "%p\n", (void *)found );

  printf( "%s\n", found->tconst );

  printf( "%s\n", found->primaryTitle );



  for (i=0;i<info->numItems;i++) {
    free(info->head[i].tconst);
    free(info->head[i].primaryTitle);
  }

  free(info->head);
  free(info);
  return 0;
}*/

/*int main () {
  int i = 0;
  struct narray_info *info;
  struct name_basics *found;
  info = get_name("dataFiles");
  printf("PRINTING %d\n", info->numItems);

  build_pnindex(info);
  printf( "%s\n", (info->tree1)->key );

  printf( "%p\n", (info->tree1)->data );


  printf("%s\n", ((struct name_basics *)(info->tree1)->data)->primaryName );

  printf("%s\n", ((struct name_basics *)(info->tree1)->data)->nconst );

  found = (struct name_basics *)find_primary_name(info,"Anthony Daniels");

  printf( "%p\n", (void *)found );

  printf( "%s\n", found->nconst );

  printf( "%s\n", found->primaryName );

  for (i=0;i<info->numItems;i++) {
    free((info->head[i]).nconst);
    free((info->head[i]).primaryName);
  }

  free(info->head);
  free(info);
  return 0;
}*/

/*int main () {
  int i = 0;
  struct tarray_info *info;
  struct title_basics *found;
  info = get_title("dataFiles");
  printf("PRINTING %d\n", info->numItems);

  build_tconstIndex(info);
  printf( "%s\n", (info->tree2)->key );

  printf( "%p\n", (info->tree2)->data );


  printf("%s\n", ((struct title_basics *)(info->tree2)->data)->primaryTitle );

  printf("%s\n", ((struct title_basics *)(info->tree2)->data)->tconst );

  found = (struct title_basics *)find_tconst(info,"tt0080684");

  printf( "%p\n", (void *)found );

  printf( "%s\n", found->tconst );

  printf( "%s\n", found->primaryTitle );

  free(info);
  return 0;
}*/

int main () {
  struct tarray_info *titleBasics;
  struct narray_info *nameBasics;
  struct parray_info *titlePrincipals;
  struct title_basics *title;
  struct title_principals *principals;
  struct name_basics *name;

  titleBasics = get_title("dataFiles");
  build_ptindex(titleBasics);
  build_tconstIndex(titleBasics);
  nameBasics = get_name("dataFiles");
  build_pnindex(nameBasics);
  build_nconstIndex(nameBasics);
  titlePrincipals = get_principals("dataFiles");
  build_tconstIndex_tp(titlePrincipals);
  build_nconstIndex_tp(titlePrincipals);

  name = (struct name_basics *)find_primary_name(nameBasics,"Bruce Lee");
  principals = (struct title_principals *)find_nconst_tp(titlePrincipals,name->nconst);
  title = (struct title_basics *)find_tconst(titleBasics,principals->tconst);

  printf("%s\n",title->primaryTitle);
  return 0;
}

/*int main () {
  int i = 0;
  struct parray_info *info;
  struct title_principals *found;
  info = get_principals("dataFiles");
  printf("PRINTING %d\n", info->numItems);

  build_tconstIndex_tp(info);
  printf( "%s\n", (info->tree2)->key );

  printf( "%p\n", (info->tree2)->data );


  printf("%s\n", ((struct title_principals *)(info->tree2)->data)->nconst );

  printf("%s\n", ((struct title_principals *)(info->tree2)->data)->tconst );
  printf("%s\n", ((struct title_principals *)(info->tree2)->data)->characters );

  found = (struct title_principals *)find_tconst_tp(info,"tt0080684");

  printf( "%p\n", (void *)found );

  printf( "%s\n", found->tconst );

  printf( "%s\n", found->nconst );

  printf( "%s\n", found->characters );

  free(info);
  return 0;
}*/
