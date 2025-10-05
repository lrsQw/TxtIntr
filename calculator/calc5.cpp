#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

bool compare(double a, double b) {
    return a < b;
}
double av_calc(const std::vector<double>& numbers) { // Ср. значение
    double sum = 0.0;
    for (double num : numbers) {
        sum += num;
    }
    return sum / numbers.size();
}
double med_calc(std::vector<double> numbers) { // Медиана
    std::sort(numbers.begin(), numbers.end(), compare);
    size_t count = numbers.size();
    if (count % 2 == 0) {
        return (numbers[count/2 - 1] + numbers[count/2]) / 2.0;
    } else {
        return numbers[count/2];
    }
}
bool is_number(const std::string& str) {
    std::istringstream tr(str);
    double d;
    char c;
    return (tr >> d) && !(tr >> c);
}
void print_help() { // Справка
    std::cout << "Статистический калькулятор\n";
    std::cout << "Использование: calculator -o OPERATION [OPERAND1, OPERAND2...]\n";
    std::cout << "Операции:\n";
    std::cout << "-o average  Среднее арифметическое\n";
    std::cout << "-o median   Медиана\n";
    std::cout << "Операнды:\n";
    std::cout << "От 5 до 7 чисел для вычислений\n";
    std::cout << ("Пример: calculator -o average 1 2 3 4 5\n");
    std::cout << ("        calculator -o median 1 2 3 4 5 6 7\n");
}
int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }
    std::string operation;
    std::vector<double> operands;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-o") {
            if (i + 1 < argc) {
                operation = argv[i + 1];
                i++;
            } else {
                std::cerr << "Ошибка: после -o должна следовать операция\n";
                return 1;
            }
        } else if (is_number(arg)) {
            if (operands.size() < 7) {
                operands.push_back(std::stod(arg));
            } else {
                std::cerr << "Ошибка: слишком много операндов\n";
                return 1;
            }
        } else {
            std::cerr << "Ошибка: неизвестный параметр\n";
            return 1;
        }
    }
    if (operation.empty()) {
        std::cerr << "Ошибка: не указана операция\n";
        print_help();
        return 1;
    }
    if (operands.size() < 5 || operands.size() > 7) {
        std::cerr << "Ошибка: количество операндов должно быть от 5 до 7\n";
        return 1;
    }
    double result;
    if (operation == "average") {
        result = av_calc(operands);
        std::cout << "Среднее арифметическое: " << std::fixed << std::setprecision(2) << result << std::endl;
    } else if (operation == "median") {
        result = med_calc(operands);
        std::cout << "Медиана: " << std::fixed << std::setprecision(2) << result << std::endl;
    } else {
        std::cerr << "Ошибка: неизвестная операция\n";
        print_help();
        return 1;
    }
    return 0;
}
