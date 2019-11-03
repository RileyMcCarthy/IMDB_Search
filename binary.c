
#include "title.h"
#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*integer is now title name, and structure stores pointer to title_basics node in array*/
void add_node( struct tree_basics **head, char *pTitle, struct title_basics *data) {
  if (*head) /* there's a node here */
  {
    if (strcmp(pTitle,(*head)->key) < 0) /*left side is less than node*/
    {
      add_node( &((*head)->left), pTitle, data );
    }
    else
    {
      add_node( &((*head)->right), pTitle, data );
    }
  }
  else /* no node here */
  {
    (*head) = malloc( sizeof( struct tree_basics ) );
    (*head)->key = pTitle;
    (*head)->data = data;
    (*head)->left=NULL;
    (*head)->right=NULL;
    /*printf("adding node key: %s, data: %s\n",(*head)->key, ((struct title_basics *)(*head)->data)->primaryTitle  );*/
  }
}

struct tree_basics *find_node (struct tree_basics  *root, char *target) {
  int value = 0;
  if (root) {
    value = strcmp(root->key,target);
    printf("value: %d",value);
    if (value == 0) {
      printf("returning root\n");
      return root;
    }else if (value > 0) {
      return find_node(root->left,target);
    }else {
      return find_node(root->right,target);
    }
  }else {
    printf("returning null\n");
    return NULL;
  }
  printf("returning nullbad\n");
  return NULL;
}
