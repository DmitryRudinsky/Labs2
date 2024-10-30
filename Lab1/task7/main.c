#include "options.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (!ValidateFlag(argv[1])) {
        printf("Wrong flag detected\n");
        return ERROR_FLAG;
    }

    char flag = argv[1][1];
    if (!ValidateArgCount(argc, flag)) {
        printf("Wrong number of arguments\n");
        return ERROR_ARG_COUNT;
    }

    FILE *file1, *file2, *file3;

    if (flag == 'r' && (strcmp(argv[2], argv[3]) == 0 || strcmp(argv[2], argv[4]) == 0 || strcmp(argv[3], argv[4]) == 0)) {
        printf("Error: Same file names detected in 'task4' mode\n");
        return ERROR_FILE;
    }

    if (flag == 'a' && strcmp(argv[2], argv[3]) == 0) {
        printf("Error: Same file names detected in 'a' mode\n");
        return ERROR_FILE;
    }

    switch (flag) {
        case 'r':
            file1 = fopen(argv[2], "task4");
            if (file1 == NULL) {
                printf("Error opening the first file\n");
                return ERROR_FILE;
            }

            file2 = fopen(argv[3], "task4");
            if (file2 == NULL) {
                printf("Error opening the second file\n");
                fclose(file1);
                return ERROR_FILE;
            }

            file3 = fopen(argv[4], "w");
            if (file3 == NULL) {
                printf("Error opening the third file\n");
                fclose(file1);
                fclose(file2);
                return ERROR_FILE;
            }

            ProcessRMode(file1, file2, file3);
            fclose(file1);
            fclose(file2);
            fclose(file3);
            break;

        case 'a':
            file1 = fopen(argv[2], "task4");
            if (file1 == NULL) {
                printf("Error opening the first file\n");
                return ERROR_FILE;
            }

            file2 = fopen(argv[3], "w");
            if (file2 == NULL) {
                printf("Error opening the second file\n");
                fclose(file1);
                return ERROR_FILE;
            }

            ProcessAMode(file1, file2);
            fclose(file1);
            fclose(file2);
            break;
    }

    return SUCCESS;
}
