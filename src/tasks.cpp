#include "tasks.h"

#include <iostream>
#include <limits>

#include "doubly_list.h"
#include "name_search.h"
#include "planets.h"
#include "singly_list.h"

namespace lab4 {

namespace {

// ---------- Задание 1: список с указателем bottom ----------
void print_bottom_list(const BottomList* list, std::string op) {
    std::cout << op << "\t";
    if (list->top == nullptr) {
        std::cout << "null\tnull\t";
    } else {
        std::cout << list->top->value << "\t" << list->bottom->value << "\t";
    }
    print_list(list->top);
    std::cout << std::endl;
}

void run_task1() {
    std::cout << "Задание 1. Список с указателем bottom" << std::endl;
    std::cout << "операция\ttop\tbottom\tсписок" << std::endl;
    BottomList list = create_bottom_list();
    print_bottom_list(&list, "пустой список");
    for (int i = 1; i <= 4; i++) {
        add_at_end_with_bottom(&list, new_cell(i));
        print_bottom_list(&list, "в конец " + std::to_string(i));
    }
    add_at_beginning_with_bottom(&list, new_cell(0));
    print_bottom_list(&list, "в начало 0");
    delete_with_bottom(&list, 2);
    print_bottom_list(&list, "удалили 2");
    delete_with_bottom(&list, 4);
    print_bottom_list(&list, "удалили 4");
    delete_with_bottom(&list, 0);
    print_bottom_list(&list, "удалили 0");
    delete_with_bottom(&list, 1);
    delete_with_bottom(&list, 3);
    print_bottom_list(&list, "удалили 1 и 3");
    add_at_end_with_bottom(&list, new_cell(7));
    print_bottom_list(&list, "в конец 7");
    destroy_bottom_list(&list);
}

// ---------- Задание 2: наибольший элемент ----------
void print_max(const Cell* list) {
    const Cell* max_cell = find_max(list);
    if (max_cell == nullptr) {
        std::cout << "нет\t\t";
    } else {
        std::cout << max_cell->value << "\t\t";
    }
    print_list(list);
    std::cout << std::endl;
}

void run_task2() {
    std::cout << "Задание 2. Наибольший элемент несортированного списка" << std::endl;
    std::cout << "наибольший\tсписок" << std::endl;
    const int a[] = {12, -5, 37, 8, 21};
    const int b[] = {-7, -3, -9};
    Cell* list_a = make_list(a, 5);
    Cell* list_b = make_list(b, 3);
    print_max(list_a);
    print_max(list_b);
    print_max(nullptr);
    destroy_list(list_a);
    destroy_list(list_b);
}

// ---------- Задания 3-6, 8: двунаправленный список ----------
void print_dlist_header() {
    std::cout << "операция\tвперёд по next | назад по prev" << std::endl;
}

void print_dlist_row(const DList* list, std::string op) {
    std::cout << op << "\t";
    print_dlist(list);
    std::cout << std::endl;
}

void run_task3() {
    std::cout << "Задание 3. Добавление в начало двунаправленного списка" << std::endl;
    print_dlist_header();
    DList list = create_dlist();
    for (int i = 1; i <= 3; i++) {
        add_at_beginning_d(&list, new_dcell(i));
        print_dlist_row(&list, "в начало " + std::to_string(i));
    }
    destroy_dlist(&list);
}

void run_task4() {
    std::cout << "Задание 4. Добавление в конец двунаправленного списка" << std::endl;
    print_dlist_header();
    DList list = create_dlist();
    for (int i = 1; i <= 3; i++) {
        add_at_end_d(&list, new_dcell(i));
        print_dlist_row(&list, "в конец " + std::to_string(i));
    }
    destroy_dlist(&list);
}

void run_task5() {
    std::cout << "Задание 5. Добавление в начало и в конец через InsertCell" << std::endl;
    print_dlist_header();
    DList list = create_dlist();
    add_at_end_via_insert(&list, new_dcell(1));
    print_dlist_row(&list, "в конец 1");
    add_at_end_via_insert(&list, new_dcell(2));
    print_dlist_row(&list, "в конец 2");
    add_at_beginning_via_insert(&list, new_dcell(0));
    print_dlist_row(&list, "в начало 0");
    add_at_end_via_insert(&list, new_dcell(3));
    print_dlist_row(&list, "в конец 3");
    destroy_dlist(&list);
}

void run_task6() {
    std::cout << "Задание 6. Удаление ячейки из двунаправленного списка" << std::endl;
    print_dlist_header();
    DList list = create_dlist();
    for (int i = 1; i <= 5; i++) {
        add_at_end_d(&list, new_dcell(i));
    }
    print_dlist_row(&list, "исходный");
    delete_cell_d(find_d(&list, 3));
    print_dlist_row(&list, "удалили 3");
    delete_cell_d(find_d(&list, 1));
    print_dlist_row(&list, "удалили 1");
    delete_cell_d(find_d(&list, 5));
    print_dlist_row(&list, "удалили 5");
    destroy_dlist(&list);
}

// ---------- Задание 7: поиск имени сверху и снизу ----------
void run_task7() {
    std::cout << "Задание 7. Поиск в сортированном списке имён сверху и снизу" << std::endl;
    const int name_count = 10;
    const std::string names[name_count] = {"Анна",  "Борис", "Вера", "Глеб", "Дарья",
                                           "Егор",  "Мария", "Олег", "Юлия", "Яна"};
    NameList list = make_name_list(names, name_count);
    std::cout << "список: ";
    for (int i = 0; i < name_count; i++) {
        std::cout << names[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "шагов сверху\tшагов снизу\tимя" << std::endl;
    const int target_count = 4;
    const std::string targets[target_count] = {"Анна", "Глеб", "Олег", "Яна"};
    for (int i = 0; i < target_count; i++) {
        std::cout << steps_from_top(&list, targets[i]) << "\t\t"
                  << steps_from_bottom(&list, targets[i]) << "\t\t" << targets[i] << std::endl;
    }
    destroy_name_list(&list);
}

void run_task8() {
    std::cout << "Задание 8. Вставка в сортированный двунаправленный список" << std::endl;
    print_dlist_header();
    DList list = create_dlist();
    const int a[] = {5, 1, 9, 3, 7, 3};
    for (int i = 0; i < 6; i++) {
        insert_sorted_d(&list, new_dcell(a[i]));
        print_dlist_row(&list, "вставили " + std::to_string(a[i]));
    }
    destroy_dlist(&list);
}

// ---------- Задание 9: проверка сортировки ----------
void print_sorted(const Cell* list) {
    if (is_sorted(list)) {
        std::cout << "да\t\t";
    } else {
        std::cout << "нет\t\t";
    }
    print_list(list);
    std::cout << std::endl;
}

void run_task9() {
    std::cout << "Задание 9. Проверка, отсортирован ли список" << std::endl;
    std::cout << "отсортирован\tсписок" << std::endl;
    const int a[] = {1, 2, 2, 5, 8};
    const int b[] = {1, 4, 2, 6};
    const int c[] = {42};
    Cell* list_a = make_list(a, 5);
    Cell* list_b = make_list(b, 4);
    Cell* list_c = make_list(c, 1);
    print_sorted(list_a);
    print_sorted(list_b);
    print_sorted(list_c);
    print_sorted(nullptr);
    destroy_list(list_a);
    destroy_list(list_b);
    destroy_list(list_c);
}

// ---------- Задание 10: многопотоковый список планет ----------
void run_task10() {
    std::cout << "Задание 10. Многопотоковый список планет" << std::endl;
    Planet* planets = create_planet_list();
    // Добавляем в алфавитном порядке, сортируют потоки
    add_planet_to_list(planets, new_planet("Венера", 0.72, 0.815, 12104));
    add_planet_to_list(planets, new_planet("Земля", 1.00, 1, 12742));
    add_planet_to_list(planets, new_planet("Марс", 1.52, 0.107, 6779));
    add_planet_to_list(planets, new_planet("Меркурий", 0.39, 0.055, 4879));
    add_planet_to_list(planets, new_planet("Нептун", 30.07, 17.1, 49244));
    add_planet_to_list(planets, new_planet("Сатурн", 9.58, 95.2, 116460));
    add_planet_to_list(planets, new_planet("Уран", 19.19, 14.5, 50724));
    add_planet_to_list(planets, new_planet("Юпитер", 5.20, 317.8, 139820));

    int thread = -1;
    while (thread != kExitChoice) {
        thread = read_number(
            "Сортировать: 1 - по расстоянию до Солнца, 2 - по массе, 3 - по диаметру, 0 - назад: ");
        if (thread == kByDistance || thread == kByMass || thread == kByDiameter) {
            print_planets(planets, thread);
        } else if (thread != kExitChoice) {
            std::cout << "Нет такого пункта" << std::endl;
        }
    }
    destroy_planet_list(planets);
}

// ---------- Задание 11: черепаха и кролик ----------
void run_task11() {
    std::cout << "Задание 11. Черепаха и кролик" << std::endl;
    const int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Cell* list = make_list(a, 10);
    // Замыкаем: 10 -> 4 (номер 3, считая с 0)
    link_last_to(list, 3);
    std::cout << "список: 1 2 3 4 5 6 7 8 9 10 -> 4 (цикл)" << std::endl;
    int start_value = 0;
    int end_value = 0;
    if (find_and_break_cycle(list, &start_value, &end_value)) {
        std::cout << "начало цикла: " << start_value << std::endl;
        std::cout << "конец цикла: " << end_value << std::endl;
        std::cout << "цикл разорван, список: ";
        print_list(list);
        std::cout << std::endl;
    }
    destroy_list(list);

    const int b[] = {1, 2, 3, 4, 5};
    list = make_list(b, 5);
    std::cout << "список: ";
    print_list(list);
    std::cout << std::endl;
    if (!find_and_break_cycle(list, nullptr, nullptr)) {
        std::cout << "цикла нет" << std::endl;
    }
    destroy_list(list);
}

}  // namespace

int read_number(std::string prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        if (std::cin.eof()) {
            return kExitChoice;
        }
        // Ввели не число: сбрасываем ошибку и пропускаем строку
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Нужно ввести число" << std::endl;
    }
}

bool run_task(int number) {
    if (number == 1) {
        run_task1();
    } else if (number == 2) {
        run_task2();
    } else if (number == 3) {
        run_task3();
    } else if (number == 4) {
        run_task4();
    } else if (number == 5) {
        run_task5();
    } else if (number == 6) {
        run_task6();
    } else if (number == 7) {
        run_task7();
    } else if (number == 8) {
        run_task8();
    } else if (number == 9) {
        run_task9();
    } else if (number == 10) {
        run_task10();
    } else if (number == 11) {
        run_task11();
    } else {
        return false;
    }
    return true;
}

}  // namespace lab4
