
#include "title.h"
#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*integer is now title name, and structure stores pointer to title_basics node in array*/
void add_node( struct tree_basics **head, char *pTitle, struct title_basics *data) {
  if (*head) /* there's a node here */
  {
    if (strcmp(pTitle,(*head)->key) <= 0) /*left side is less than node*/
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
  }
}

struct tree_basics *find_node (struct tree_basics  *root, char *target) {
  int value = 0;
  if (root) {
    value = strcmp(root->key,target);
    if (value == 0) {
      return root;
    }else if (value > 0) {
      return find_node(root->left,target);
    }else {
      return find_node(root->right,target);
    }
  }else {
    return NULL;
  }
  return NULL;
}

void free_tree( struct tree_basics *root ) {
  if (root)
  {
    free_tree( root->left );
    free_tree( root->right );
    free( root );
  }
}
