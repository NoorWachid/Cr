#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

char* Version = "2020.3.20";
void CrSee(char* Path);

int main(int ArgCount, char** ArgVector) {
    if (ArgCount == 1) {
        printf("usage: cr [file|directory/]\n");
        printf("version: %s\n", Version);
    }

    if (ArgCount > 1) {
        for (int Index = 1; Index < ArgCount; ++Index) {
            CrSee(ArgVector[Index]);
        }
    }

    return 0;
}

void CrSee(char* Path) {
    size_t Index    = 0, 
           Capasity = 64, 
           Size     = 0,
           Length   = strlen(Path);
    char* TmpPath   = malloc(sizeof(char) * Capasity);

    while (Index < Length) {
        TmpPath[Index] = Path[Index];

        ++Size;

        if (Size > Capasity - 2) {
            Capasity *= 1.5;
            TmpPath   = realloc(TmpPath, Capasity * sizeof(char));
        }

        if (Path[Index] == '/') {
            // Add null terminator.
            TmpPath[Index + 1] = '\0';
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
