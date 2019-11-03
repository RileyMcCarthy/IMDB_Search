struct title_principals {
  char *tconst;
  char *nconst;
  char *characters;
};

struct parray_info {
  int numItems;
  struct title_principals *head;
  struct tree_basics *tree1;
  struct tree_basics *tree2;
};

struct parray_info *get_principals (char *fileDir);
void build_nconstIndex_tp (struct parray_info *info);
void build_tconstIndex_tp (struct parray_info *info);
struct title_principals *find_nconst_tp (struct parray_info *root, char *target);
struct title_principals *find_tconst_tp (struct parray_info *root, char *target);
