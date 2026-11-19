// Проверочные сценарии: типичные, граничные (nullptr, пустой список) и некорректный ввод
#include <iostream>
#include <sstream>
#include <string>

#include "doubly_list.h"
#include "name_search.h"
#include "planets.h"
#include "singly_list.h"
#include "tasks.h"

namespace {

int failed = 0;

void check(bool ok, std::string name) {
    if (ok) {
        std::cout << "OK    " << name << std::endl;
    } else {
        std::cout << "FAIL  " << name << std::endl;
        failed++;
    }
}

// Список строкой "1 2 3"
std::string to_text(const lab4::Cell* top) {
    std::string text;
    while (top != nullptr) {
        text += std::to_string(top->value) + " ";
        top = top->next;
    }
    return text;
}

// Двунаправленный список строкой "1 2 3 | 3 2 1"
std::string to_text(const lab4::DList* list) {
    std::string text;
    const lab4::DCell* cell = list->top->next;
    while (cell != list->bottom) {
        text += std::to_string(cell->value) + " ";
        cell = cell->next;
    }
    text += "| ";
    cell = list->bottom->prev;
    while (cell != list->top) {
        text += std::to_string(cell->value) + " ";
        cell = cell->prev;
    }
    return text;
}

void test_bottom_list() {
    lab4::BottomList list = lab4::create_bottom_list();
    check(!lab4::delete_with_bottom(&list, 1), "задание 1: удаление из пустого списка");
    lab4::add_at_end_with_bottom(&list, lab4::new_cell(1));
    lab4::add_at_end_with_bottom(&list, lab4::new_cell(2));
    lab4::add_at_end_with_bottom(&list, lab4::new_cell(3));
    check(list.top->value == 1 && list.bottom->value == 3, "задание 1: добавление в конец");
    lab4::delete_with_bottom(&list, 3);
    check(list.bottom->value == 2 && to_text(list.top) == "1 2 ",
          "задание 1: удаление последнего переносит bottom");
    check(!lab4::delete_with_bottom(&list, 7), "задание 1: удаление отсутствующего значения");
    lab4::delete_with_bottom(&list, 1);
    lab4::delete_with_bottom(&list, 2);
    check(list.top == nullptr && list.bottom == nullptr,
          "задание 1: после удаления всех top и bottom = null");
    lab4::add_at_beginning_with_bottom(&list, lab4::new_cell(5));
    check(list.bottom != nullptr && list.bottom->value == 5,
          "задание 1: добавление в начало пустого списка ставит bottom");
    check(!lab4::add_at_end_with_bottom(nullptr, nullptr), "задание 1: nullptr");
    lab4::destroy_bottom_list(&list);
}

void test_singly() {
    const int a[] = {12, -5, 37, 8, 21};
    const int b[] = {-7, -3, -9};
    const int sorted[] = {1, 2, 2, 5};
    check(lab4::make_list(nullptr, 3) == nullptr && lab4::make_list(a, 0) == nullptr,
          "make_list: nullptr и нулевой размер");
    lab4::Cell* list_a = lab4::make_list(a, 5);
    lab4::Cell* list_b = lab4::make_list(b, 3);
    lab4::Cell* list_s = lab4::make_list(sorted, 4);
    check(lab4::find_max(list_a)->value == 37, "задание 2: наибольший элемент");
    check(lab4::find_max(list_b)->value == -3, "задание 2: только отрицательные числа");
    check(lab4::find_max(nullptr) == nullptr, "задание 2: пустой список");
    check(lab4::is_sorted(list_s) && !lab4::is_sorted(list_a), "задание 9: сортирован / нет");
    check(lab4::is_sorted(nullptr), "задание 9: пустой список отсортирован");
    lab4::destroy_list(list_a);
    lab4::destroy_list(list_b);
    lab4::destroy_list(list_s);
}

void test_cycle() {
    const int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    lab4::Cell* list = lab4::make_list(a, 10);
    check(!lab4::link_last_to(list, 10), "задание 11: номер вне списка");
    lab4::link_last_to(list, 3);
    int start_value = 0;
    int end_value = 0;
    bool found = lab4::find_and_break_cycle(list, &start_value, &end_value);
    check(found && start_value == 4 && end_value == 10, "задание 11: цикл 10 -> 4");
    check(!lab4::find_and_break_cycle(list, nullptr, nullptr), "задание 11: после разрыва цикла нет");
    lab4::link_last_to(list, 0);
    found = lab4::find_and_break_cycle(list, &start_value, &end_value);
    check(found && start_value == 1 && end_value == 10, "задание 11: цикл через весь список");
    lab4::destroy_list(list);
    check(!lab4::find_and_break_cycle(nullptr, nullptr, nullptr), "задание 11: пустой список");
}

void test_doubly() {
    lab4::DList list = lab4::create_dlist();
    lab4::add_at_beginning_d(&list, lab4::new_dcell(2));
    lab4::add_at_beginning_d(&list, lab4::new_dcell(1));
    lab4::add_at_end_d(&list, lab4::new_dcell(3));
    check(to_text(&list) == "1 2 3 | 3 2 1 ", "задания 3, 4: добавление в начало и конец");
    lab4::add_at_beginning_via_insert(&list, lab4::new_dcell(0));
    lab4::add_at_end_via_insert(&list, lab4::new_dcell(4));
    check(to_text(&list) == "0 1 2 3 4 | 4 3 2 1 0 ", "задание 5: через InsertCell");
    lab4::delete_cell_d(lab4::find_d(&list, 0));
    lab4::delete_cell_d(lab4::find_d(&list, 4));
    lab4::delete_cell_d(lab4::find_d(&list, 2));
    check(to_text(&list) == "1 3 | 3 1 ", "задание 6: удаление первой, последней, средней");
    check(!lab4::delete_cell_d(list.top) && !lab4::delete_cell_d(nullptr),
          "задание 6: ограничитель и nullptr не удаляются");
    check(lab4::find_d(&list, 7) == nullptr, "поиск отсутствующего значения");
    check(!lab4::add_at_end_d(nullptr, nullptr) && !lab4::insert_cell_d(list.bottom, nullptr),
          "двунаправленный список: nullptr");
    lab4::destroy_dlist(&list);

    list = lab4::create_dlist();
    const int a[] = {5, 1, 9, 3, 7, 3};
    for (int i = 0; i < 6; i++) {
        lab4::insert_sorted_d(&list, lab4::new_dcell(a[i]));
    }
    check(to_text(&list) == "1 3 3 5 7 9 | 9 7 5 3 3 1 ", "задание 8: вставка в сортированный");
    lab4::destroy_dlist(&list);
}

void test_names() {
    const std::string names[] = {"Анна", "Глеб", "Олег", "Яна"};
    lab4::NameList list = lab4::make_name_list(names, 4);
    check(lab4::steps_from_top(&list, "Анна") == 1 && lab4::steps_from_bottom(&list, "Анна") == 4,
          "задание 7: имя в начале");
    check(lab4::steps_from_top(&list, "Яна") == 4 && lab4::steps_from_bottom(&list, "Яна") == 1,
          "задание 7: имя в конце");
    check(lab4::steps_from_top(nullptr, "Анна") == -1, "задание 7: nullptr");
    lab4::destroy_name_list(&list);
    list = lab4::make_name_list(nullptr, 0);
    check(lab4::steps_from_top(&list, "Анна") == 0, "задание 7: пустой список");
    lab4::destroy_name_list(&list);
}

void test_planets() {
    lab4::Planet* list = lab4::create_planet_list();
    lab4::add_planet_to_list(list, lab4::new_planet("Земля", 1.00, 1, 12742));
    lab4::add_planet_to_list(list, lab4::new_planet("Марс", 1.52, 0.107, 6779));
    lab4::add_planet_to_list(list, lab4::new_planet("Юпитер", 5.20, 317.8, 139820));
    lab4::add_planet_to_list(list, lab4::new_planet("Венера", 0.72, 0.815, 12104));
    std::string order;
    const lab4::Planet* p = lab4::next_in_thread(list, lab4::kByMass);
    while (p != nullptr) {
        order += p->name + " ";
        p = lab4::next_in_thread(p, lab4::kByMass);
    }
    check(order == "Марс Венера Земля Юпитер ", "задание 10: поток по массе");
    check(lab4::next_in_thread(list, lab4::kByDistance)->name == "Венера",
          "задание 10: первая по расстоянию");
    check(lab4::next_in_thread(list, 5) == nullptr, "задание 10: неверный номер потока");
    check(!lab4::add_planet_to_list(nullptr, nullptr), "задание 10: nullptr");
    lab4::destroy_planet_list(list);
}

void test_input() {
    std::istringstream input("abc\n5\n");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    std::cout.setstate(std::ios::failbit);  // прячем подсказки ввода
    int value = lab4::read_number("> ");
    int at_end = lab4::read_number("> ");
    std::cout.clear();
    std::cin.rdbuf(old);
    std::cin.clear();
    check(value == 5, "ввод: буквы вместо числа пропускаются");
    check(at_end == lab4::kExitChoice, "ввод: конец ввода = выход");
    check(!lab4::run_task(12) && !lab4::run_task(-1), "меню: нет такого задания");
}

}  // namespace

int main() {
    test_bottom_list();
    test_singly();
    test_cycle();
    test_doubly();
    test_names();
    test_planets();
    test_input();
    std::cout << (failed == 0 ? "Все проверки пройдены" : "Есть ошибки") << std::endl;
    return failed == 0 ? 0 : 1;
}
