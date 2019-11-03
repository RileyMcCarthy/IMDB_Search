
struct name_basics {
  char *nconst;
  char *primaryName;
};

struct narray_info {
  int numItems;
  struct name_basics *head;
  struct tree_basics *tree1;
  struct tree_basics *tree2;
};

struct narray_info *get_name (char *fileDir);
void build_pnindex (struct narray_info *info);
struct name_basics *find_primary_name (struct narray_info *root, char *target);
void build_nconstIndex (struct narray_info *info);
struct name_basics *find_nconst (struct narray_info *root, char *target);
