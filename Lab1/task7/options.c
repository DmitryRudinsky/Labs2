#include "options.h"

int ConvertToBase(char symbol, int base) {
    if (symbol >= 'A' && symbol <= 'Z') {
        symbol = tolower(symbol);
    }

    int ascii = symbol;
    int result = 0;
    int multiplier = 1;

    while (ascii != 0) {
        result += (ascii % base) * multiplier;
        multiplier *= 10;
        ascii /= base;
    }
    return result;
}

// Обрабатывает режим 'r' и объединяет содержимое двух файлов
void ProcessRMode(FILE *file1, FILE *file2, FILE *file3) {
    char a1 = fgetc(file1);
    char a2 = fgetc(file2);

    while (a1 != EOF || a2 != EOF) {
        if (a1 != EOF) {
            while (a1 != EOF && a1 != '\n' && a1 != ' ') {
                fputc(a1, file3);
                a1 = fgetc(file1);
            }
            while (a1 == '\n' || a1 == ' ') {
                a1 = fgetc(file1);
            }
            fputc(' ', file3);
        }
        if (a2 != EOF) {
            while (a2 != EOF && a2 != '\n' && a2 != ' ') {
                fputc(a2, file3);
                a2 = fgetc(file2);
            }
            while (a2 == '\n' || a2 == ' ') {
                a2 = fgetc(file2);
            }
            fputc(' ', file3);
        }
    }
}

// Обрабатывает режим 'a' с преобразованием лексем
void ProcessAMode(FILE *file1, FILE *file2) {
    int lexeme_number = 1;
    char a = fgetc(file1);

    while (a != EOF) {
        if (lexeme_number % 10 == 0) {
            while (a != EOF && a != ' ' && a != '\n') {
                int symbol = ConvertToBase(a, 4);
                fprintf(file2, "%d", symbol);
                a = fgetc(file1);
            }
            fputc(' ', file2);
        } else if (lexeme_number % 5 == 0) {
            while (a != EOF && a != ' ' && a != '\n') {
                int symbol = ConvertToBase(a, 8);
                fprintf(file2, "%d", symbol);
                a = fgetc(file1);
            }
            fputc(' ', file2);
        } else if (lexeme_number % 2 == 0) {
            while (a != EOF && a != ' ' && a != '\n') {
                fputc(tolower(a), file2);
                a = fgetc(file1);
            }
            fputc(' ', file2);
        } else {
            while (a != EOF && a != ' ' && a != '\n') {
                fputc(a, file2);
                a = fgetc(file1);
            }
            fputc(' ', file2);
        }
        while (a == ' ' || a == '\n') {
            a = fgetc(file1);
        }
        lexeme_number++;
    }
}

int ValidateFlag(char *flag) {
    return (flag[0] == '-' || flag[0] == '/') && (flag[1] == 'r' || flag[1] == 'a') && flag[2] == 0;
}

int ValidateArgCount(int argc, char flag) {
    if (flag == 'a' && argc != 4) {
        return 0;
    }
    if (flag == 'r' && argc != 5) {
        return 0;
    }
    return 1;
}