
struct tree_basics {
  char *key;
  void *data;
  struct tree_basics *left;
  struct tree_basics *right;
};

struct tree_basics *find_node (struct tree_basics  *root, char *target);

void add_node( struct tree_basics **head, char *pTitle, struct title_basics *data);
