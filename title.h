struct title_basics {
  char *tconst;
  char *primaryTitle;
};

struct tarray_info {
  int numItems;
  struct title_basics *head;
  struct tree_basics *tree1;
  struct tree_basics *tree2;
};

struct tarray_info *get_title (char *fileDir);

void build_ptindex (struct tarray_info *info) ;

struct title_basics *find_primary_title (struct tarray_info *root, char *target);
void build_tconstIndex (struct tarray_info *info);
struct title_basics *find_tconst (struct tarray_info *root, char *target);
