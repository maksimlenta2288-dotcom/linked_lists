#include <iostream>

#include "tasks.h"

int main() {
    int choice = -1;
    while (choice != lab4::kExitChoice) {
        std::cout << std::endl;
        choice = lab4::read_number("ЛР 4. Связные списки. Задание 1-11, 0 - выход: ");
        if (choice != lab4::kExitChoice && !lab4::run_task(choice)) {
            std::cout << "Нет такого задания" << std::endl;
        }
    }
    return 0;
}
