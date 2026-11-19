#include "doubly_list.h"

#include <climits>
#include <iostream>

namespace lab4 {

namespace {
// Значения ограничителей: меньше и больше любого значения в списке
constexpr int kTopSentinel = INT_MIN;
constexpr int kBottomSentinel = INT_MAX;
}  // namespace

DCell* new_dcell(int value) {
    DCell* cell = new DCell;
    cell->value = value;
    cell->next = nullptr;
    cell->prev = nullptr;
    return cell;
}

DList create_dlist() {
    DList list;
    list.top = new_dcell(kTopSentinel);
    list.bottom = new_dcell(kBottomSentinel);
    list.top->next = list.bottom;
    list.bottom->prev = list.top;
    return list;
}

void destroy_dlist(DList* list) {
    if (list == nullptr) {
        return;
    }
    DCell* cell = list->top;
    while (cell != nullptr) {
        DCell* next_cell = cell->next;
        delete cell;
        cell = next_cell;
    }
    list->top = nullptr;
    list->bottom = nullptr;
}

// Задание 3: благодаря ограничителю у новой ячейки всегда есть сосед справа
bool add_at_beginning_d(DList* list, DCell* cell) {
    if (list == nullptr || cell == nullptr) {
        return false;
    }
    cell->next = list->top->next;
    cell->prev = list->top;
    list->top->next->prev = cell;
    list->top->next = cell;
    return true;
}

// Задание 4
bool add_at_end_d(DList* list, DCell* cell) {
    if (list == nullptr || cell == nullptr) {
        return false;
    }
    cell->next = list->bottom;
    cell->prev = list->bottom->prev;
    list->bottom->prev->next = cell;
    list->bottom->prev = cell;
    return true;
}

bool insert_cell_d(DCell* after_me, DCell* cell) {
    if (after_me == nullptr || cell == nullptr || after_me->next == nullptr) {
        return false;
    }
    cell->next = after_me->next;
    cell->prev = after_me;
    after_me->next->prev = cell;
    after_me->next = cell;
    return true;
}

// Задание 5: начало - вставка после верхнего ограничителя
bool add_at_beginning_via_insert(DList* list, DCell* cell) {
    if (list == nullptr) {
        return false;
    }
    return insert_cell_d(list->top, cell);
}

// Задание 5: конец - вставка после последней ячейки (перед нижним ограничителем)
bool add_at_end_via_insert(DList* list, DCell* cell) {
    if (list == nullptr) {
        return false;
    }
    return insert_cell_d(list->bottom->prev, cell);
}

DCell* find_d(const DList* list, int target) {
    if (list == nullptr) {
        return nullptr;
    }
    DCell* cell = list->top->next;
    while (cell != list->bottom) {
        if (cell->value == target) {
            return cell;
        }
        cell = cell->next;
    }
    return nullptr;
}

// Задание 6: у обычной ячейки всегда есть prev и next, поэтому особых случаев нет
bool delete_cell_d(DCell* target) {
    if (target == nullptr || target->prev == nullptr || target->next == nullptr) {
        return false;
    }
    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;
    return true;
}

// Задание 8: цикл всегда остановится на нижнем ограничителе (INT_MAX),
// поэтому проверка на конец списка не нужна
bool insert_sorted_d(DList* list, DCell* cell) {
    if (list == nullptr || cell == nullptr) {
        return false;
    }
    DCell* after_me = list->top;
    while (after_me->next->value < cell->value) {
        after_me = after_me->next;
    }
    return insert_cell_d(after_me, cell);
}

void print_dlist(const DList* list) {
    if (list == nullptr) {
        return;
    }
    const DCell* cell = list->top->next;
    while (cell != list->bottom) {
        std::cout << cell->value << " ";
        cell = cell->next;
    }
    std::cout << "| ";
    cell = list->bottom->prev;
    while (cell != list->top) {
        std::cout << cell->value << " ";
        cell = cell->prev;
    }
}

}  // namespace lab4
