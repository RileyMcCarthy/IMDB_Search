#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void get_column (char *line, char *target, int colNumber) {
  int i = 0;
  int tabCount = 0;
  int firstTab = 0;
  int secondTab = 0;
  int size = 0;

  for (i=0;i<strlen(line);i++) {
    if (tabCount == (colNumber-1)) {
      firstTab = i;
    }
    if (tabCount == (colNumber)) {
      secondTab = i;
    }
    if (line[i] == '\t' || line[i] == '\n') {
      tabCount++;
    }
  }
  if (colNumber == 0) {
    firstTab = 0;
  }else {
    firstTab++;
  }
  size = secondTab - firstTab;
  strncpy(target,&line[firstTab],size);
  target[strlen(target)] = '\0';
}

int csvContains (char *line, char *target) {
  int i = 0;
  char BUFFER[256] = "\0";
  for (i=0;i<strlen(line);i++) {
    if (line[i] != ',') {
      BUFFER[strlen(BUFFER)] = line[i];
    }else {
      BUFFER[strlen(BUFFER)] = '\0';
      if (strcmp(BUFFER,target) == 0) {
        return 1;
      }
      memset(BUFFER,0,sizeof(BUFFER));
    }
  }
  BUFFER[strlen(BUFFER)] = '\0';
  if (strcmp(BUFFER,target) == 0) {
    return 1;
  }
  return 0;
}
