#include "name_search.h"

namespace lab4 {

NameList make_name_list(const std::string* names, int count) {
    NameList list;
    list.top = new NameCell;
    list.bottom = new NameCell;
    list.top->next = list.bottom;
    list.top->prev = nullptr;
    list.bottom->next = nullptr;
    list.bottom->prev = list.top;
    if (names == nullptr) {
        return list;
    }
    for (int i = 0; i < count; i++) {
        NameCell* cell = new NameCell;
        cell->name = names[i];
        cell->next = list.bottom;
        cell->prev = list.bottom->prev;
        list.bottom->prev->next = cell;
        list.bottom->prev = cell;
    }
    return list;
}

void destroy_name_list(NameList* list) {
    if (list == nullptr) {
        return;
    }
    NameCell* cell = list->top;
    while (cell != nullptr) {
        NameCell* next_cell = cell->next;
        delete cell;
        cell = next_cell;
    }
    list->top = nullptr;
    list->bottom = nullptr;
}

int steps_from_top(const NameList* list, std::string target) {
    if (list == nullptr) {
        return -1;
    }
    int steps = 0;
    const NameCell* cell = list->top->next;
    while (cell != list->bottom) {
        steps++;
        // Список сортирован: дальше имена только больше
        if (cell->name >= target) {
            return steps;
        }
        cell = cell->next;
    }
    return steps;
}

int steps_from_bottom(const NameList* list, std::string target) {
    if (list == nullptr) {
        return -1;
    }
    int steps = 0;
    const NameCell* cell = list->bottom->prev;
    while (cell != list->top) {
        steps++;
        if (cell->name <= target) {
            return steps;
        }
        cell = cell->prev;
    }
    return steps;
}

}  // namespace lab4
