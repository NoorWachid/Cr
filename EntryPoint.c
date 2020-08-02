#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

const char* version = "2020.8.2";

typedef struct {
    bool printFile;
    bool printDirectory;
    bool directoryMode;
} CrOption;

void CrSee(char* path, CrOption* options);
void CrArg(char* argument, CrOption* Options);
void CrHelp();

int main(int length, char** arguments) {
    if (length == 1) {
        CrHelp();
    }

    if (length > 1) {
        CrOption options;

        for (int i = 1; i < length; ++i) {
            char* argument = arguments[i];

            if (argument[0] == '-') {
                CrArg(argument, &options);
            } else {
                CrSee(argument, &options);
            }
        }
    }

    return 0;
}

void CrSee(char* path, CrOption* option) {
    size_t i        = 0, 
           capacity = 64, 
           size     = 0,
           length   = strlen(path);
    char*  tempPath = malloc(sizeof(char) * capacity);

    while (i < length) {
        tempPath[i] = path[i];

        ++size;

        if (size > capacity - 2) {
            capacity *= 1.5;
            tempPath  = realloc(tempPath, capacity * sizeof(char));
        }

        if (path[i] == '/') {
            // Add null terminator.
            tempPath[i + 1] = '\0';
            mkdir(tempPath, 0700);
        }

        ++i;
    }

    // What ever it is just create directory out of it.
    if (option->directoryMode) {
        mkdir(tempPath, 0700);

        if (option->printDirectory) {
            printf("%s\n", path);
        }
    } else {
        if (path[i - 1] != '/') {
            // If it return 0 (file exists) do not do anything.
            // If file not exists create new file.
            if (access(path, F_OK)) {
                FILE* TmpFile = fopen(path, "w");
                fclose(TmpFile);
            }

            if (option->printFile) {
                printf("%s\n", path);
            }
        } else {
            if (option->printDirectory) {
                printf("%s\n", path);
            }
        }
    }

    free(tempPath);

}

void CrArg(char* argument, CrOption* options) {
    int i = 1,
        length = strlen(argument);

    for (; i < length; ++i) {
        switch (argument[i]) {
            case 'v':
                printf("%s\n", version);
                break;
            case 'h':
                CrHelp();
                break;
            case 'r':
                options->directoryMode = true;
                break;
            case 'n':
                options->directoryMode = false;
                break;
            case 'o':
                options->printDirectory = true;
                options->printFile = true;
                break;
            case 'd':
                options->printDirectory = true;
                options->printFile = false;
                break;
            case 'f':
                options->printDirectory = false;
                options->printFile = true;
                break;
            case 's':
                options->printDirectory = false;
                options->printFile = false;
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
        "  -r directory mode\n"
        "  -n normal mode\n"
        "  -o print output\n"
        "  -d print output directory only\n"
        "  -f print output file only\n"
        "  -s silent the output\n"
        "\n"
        "Usage:\n"
        "  cr file.txt\n"
        "  cr dir/\n"
        "  cr dir/file.txt\n"
        "\n"
        "Note: see man cr for more details.\n");
}

