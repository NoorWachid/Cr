#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char* version = "2020.3.20";
void cr_see(char* rpath);

// gnu coding style is bloated!
int main(int rcount, char** rvector) {
  if (rcount == 1) {
    printf("usage: cr [file|directory/]\n");
    printf("version: %s\n", version);
  }

  if (rcount > 1) {
    for (int i = 1; i < rcount; ++i) {
      cr_see(rvector[i]);
    }
  }

  return 0;
}

// comments are for noobs!
void cr_see(char* rpath) {
  size_t i = 0, c = 2, s = 0;
  char *spath = malloc(sizeof(char) * c);

  while (rpath[i] != '\0') {
    spath[i] = rpath[i];

    if (s == c) {
      spath = realloc(spath, c * sizeof(char));
      c *= 2;
    }

    if (rpath[i] == '/') {
      mkdir(spath, 0700);
    }

    ++i;
  }

  // figure it out your self!
  if (rpath[i - 1] != '/') {
    if (access(rpath, F_OK)) {
      FILE* pfile = fopen(rpath, "w");
      fclose(pfile);
    }
  }

  free(spath);
  spath = 0;
}
