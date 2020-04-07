#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

char* Version = "2020.4.6";

typedef struct {
    bool PrintFile;
    bool PrintDirectory;
    bool DirectoryMode;
} ROptions;

void CrSee(char* Path, ROptions* Options);
void CrArg(char* Arg, ROptions* Options);
void CrHelp();

int main(int ArgCount, char** ArgVector) {
    if (ArgCount == 1) {
        CrHelp();
    }

    if (ArgCount > 1) {
        ROptions Options;

        for (int Index = 1; Index < ArgCount; ++Index) {
            char* Arg = ArgVector[Index];

            if (Arg[0] == '-') {
                CrArg(Arg, &Options);
            } else {
                CrSee(Arg, &Options);
            }
        }
    }

    return 0;
}

void CrSee(char* Path, ROptions* Options) {
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

    // What ever it is just create directory out of it.
    if (Options->DirectoryMode) {
        mkdir(TmpPath, 0700);

        if (Options->PrintDirectory) {
            printf("%s\n", Path);
        }
    } else {
        if (Path[Index - 1] != '/') {
            // If it return 0 (file exists) do not do anything.
            // If file not exists create new file.
            if (access(Path, F_OK)) {
                FILE* TmpFile = fopen(Path, "w");
                fclose(TmpFile);
            }

            if (Options->PrintFile) {
                printf("%s\n", Path);
            }
        } else {
            if (Options->PrintDirectory) {
                printf("%s\n", Path);
            }
        }
    }

    free(TmpPath);

}

void CrArg(char* Arg, ROptions* Options) {
    int Index = 1,
        Length = strlen(Arg);

    for (; Index < Length; ++Index) {
        switch (Arg[Index]) {
            case 'v':
                printf("%s\n", Version);
                break;
            case 'h':
                CrHelp();
                break;
            case 'r':
                Options->DirectoryMode = true;
                break;
            case 'n':
                Options->DirectoryMode = false;
                break;
            case 'o':
                Options->PrintDirectory = true;
                Options->PrintFile = true;
                break;
            case 'd':
                Options->PrintDirectory = true;
                Options->PrintFile = false;
                break;
            case 'f':
                Options->PrintDirectory = false;
                Options->PrintFile = true;
                break;
            case 's':
                Options->PrintDirectory = false;
                Options->PrintFile = false;
                break;
            default:
                break;
        }
    }
}

void CrHelp() {
    printf("Flags:\n" 
            "  -v version\n"
            "  -h help\n"
            "  -o print output\n"
            "\n"
            "Usage:\n"
            "  cr file.txt\n"
            "  cr dir/\n"
            "  cr dir/file.txt\n"
            "\n"
            "Note: see man cr for more details.\n");
}

