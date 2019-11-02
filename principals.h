struct title_principals {
  char *tconst;
  char *nconst;
  char *characters;
};

int get_principals (char *fileDir, struct title_principals **head);
