#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare(const void *a, const void *b) { // Сравнение чисел
    double da = *(const double*)a;
    double db = *(const double*)b;
    return (da > db) - (da < db);
}
double av_calc(double numbers[], int count) { // Ср. значение
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return sum/count;
}
double med_calc(double numbers[], int count) { // Медиана
    double *sorted = malloc(count * sizeof(double));
    if (sorted == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    memcpy(sorted, numbers, count * sizeof(double));
    qsort(sorted, count, sizeof(double), compare);
    double median;
    if (count % 2 == 0) {
        median = (sorted[count/2 - 1] + sorted[count/2]) / 2.0;
    } else {
        median = sorted[count/2];
    }
    free(sorted);
    return median;
}
int is_number(const char *str) {
    char *endptr;
    strtod(str, &endptr);
    return *endptr == '\0';
}
void print_help() { // Справка
    printf("Статистический калькулятор\n");
    printf("Использование: calculator -o OPERATION [OPERANDS...]\n");
    printf("Операции:\n");
    printf("  -o average   Среднее арифметическое\n");
    printf("  -o median    Медиана\n");
    printf("Операнды:\n");
    printf("От 5 до 7 чисел для вычислений\n");
    printf("Пример: calculator -o average 1 2 3 4 5\n");
    printf("        calculator -o median 1 2 3 4 5 6 7\n");
}
int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }
    char *operation = NULL;
    double operands[7];
    int operand_count = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                operation = argv[i + 1];
                i++; // Пропускаем следующий аргумент
            } else {
                fprintf(stderr, "Ошибка: после -o должна следовать операция\n");
                return 1;
            }
        } else if (is_number(argv[i])) {
            if (operand_count < 7) {
                operands[operand_count++] = atof(argv[i]);
            } else {
                fprintf(stderr, "Ошибка: слишком много операндов\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Ошибка: неизвестный параметр '%s'\n", argv[i]);
            return 1;
        }
    }
    if (operation == NULL) {
        fprintf(stderr, "Ошибка: не указана операция\n");
        print_help();
        return 1;
    }
    if (operand_count < 5 || operand_count > 7) {
        fprintf(stderr, "Ошибка: количество операндов должно быть от 5 до 7\n");
        return 1;
    }
    double result;
    if (strcmp(operation, "average") == 0) {
        result = av_calc(operands, operand_count);
        printf("Среднее арифметическое: %.2f\n", result);
    } else if (strcmp(operation, "median") == 0) {
        result = med_calc(operands, operand_count);
        printf("Медиана: %.2f\n", result);
    } else {
        fprintf(stderr, "Ошибка: неизвестная операция\n");
        print_help();
        return 1;
    }
    return 0;
}
