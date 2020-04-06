#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

char* version = "2020.3.20";
void CrSee(char* Path);

int main(int rcount, char** rvector) {
  if (rcount == 1) {
    printf("usage: cr [file|directory/]\n");
    printf("version: %s\n", version);
  }

  if (rcount > 1) {
    for (int Index = 1; Index < rcount; ++Index) {
      CrSee(rvector[Index]);
    }
  }

  return 0;
}

void CrSee(char* Path) {
  size_t Index    = 0, 
         Capasity = 64, 
         Size     = 0,
         Length   = strlen(Path);
  char *TmpPath   = malloc(sizeof(char) * Capasity);

  while (Path[Index] != '\0') {
    TmpPath[Index] = Path[Index];

    ++Size;

    if (Size == Capasity) {
      TmpPath = realloc(TmpPath, Capasity * sizeof(char));
      Capasity *= 1.5;
    }

    if (Path[Index] == '/') {
      mkdir(TmpPath, 0700);
    }

    ++Index;
  }

  if (Path[Index - 1] != '/') {
    // If it return 0 (file exists) do not do anything.
    // If file not exists create new file.
    if (access(Path, F_OK)) {
      FILE* TmpFile = fopen(Path, "w");
      fclose(TmpFile);
    }
  }

  free(TmpPath);
  TmpPath = 0;
}
