#include "options.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Input error! Too many or too few arguments.\n");
        InputError();
        return 0;
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Input error! Input and output files cannot be the same.\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "task4");
    if (!input) {
        perror("Ошибка открытия входного файла");
        return 1;
    }
    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Ошибка открытия выходного файла");
        fclose(input);
        return 1;
    }
    ProcessFile(input, output);
    fclose(input);
    fclose(output);
    printf("Success\n");
    return 0;
}
