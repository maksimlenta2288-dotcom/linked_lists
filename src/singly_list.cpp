#include "singly_list.h"

#include <iostream>

namespace lab4 {

Cell* new_cell(int value) {
    Cell* cell = new Cell;
    cell->value = value;
    cell->next = nullptr;
    return cell;
}

Cell* make_list(const int* values, int count) {
    if (values == nullptr || count <= 0) {
        return nullptr;
    }
    Cell* first = nullptr;
    Cell* last = nullptr;
    for (int i = 0; i < count; i++) {
        Cell* cell = new_cell(values[i]);
        if (first == nullptr) {
            first = cell;
        } else {
            last->next = cell;
        }
        last = cell;
    }
    return first;
}

void destroy_list(Cell* top) {
    while (top != nullptr) {
        // Сохраняем указатель на следующую ячейку и освобождаем текущую
        Cell* next_cell = top->next;
        delete top;
        top = next_cell;
    }
}

void print_list(const Cell* top) {
    if (top == nullptr) {
        std::cout << "(пусто)";
    }
    while (top != nullptr) {
        std::cout << top->value << " ";
        top = top->next;
    }
}

BottomList create_bottom_list() {
    BottomList list;
    list.top = nullptr;
    list.bottom = nullptr;
    return list;
}

// AddAtEndWithBottom: проход до конца не нужен
bool add_at_end_with_bottom(BottomList* list, Cell* cell) {
    if (list == nullptr || cell == nullptr) {
        return false;
    }
    cell->next = nullptr;
    if (list->top == nullptr) {
        list->top = cell;
        list->bottom = cell;
    } else {
        list->bottom->next = cell;
        list->bottom = cell;
    }
    return true;
}

bool add_at_beginning_with_bottom(BottomList* list, Cell* cell) {
    if (list == nullptr || cell == nullptr) {
        return false;
    }
    cell->next = list->top;
    list->top = cell;
    // Список был пуст - новая ячейка одновременно и последняя
    if (list->bottom == nullptr) {
        list->bottom = cell;
    }
    return true;
}

bool delete_with_bottom(BottomList* list, int target) {
    if (list == nullptr || list->top == nullptr) {
        return false;
    }
    // Удаляем первую ячейку
    if (list->top->value == target) {
        Cell* target_cell = list->top;
        list->top = list->top->next;
        // Удалили единственную ячейку - обнуляем оба указателя
        if (list->top == nullptr) {
            list->bottom = nullptr;
        }
        delete target_cell;
        return true;
    }
    // FindCellBefore: ищем ячейку перед удаляемой
    Cell* before = list->top;
    while (before->next != nullptr && before->next->value != target) {
        before = before->next;
    }
    if (before->next == nullptr) {
        return false;
    }
    Cell* target_cell = before->next;
    before->next = target_cell->next;
    // Удалили последнюю ячейку - bottom переносим на предыдущую
    if (target_cell == list->bottom) {
        list->bottom = before;
    }
    delete target_cell;
    return true;
}

void destroy_bottom_list(BottomList* list) {
    if (list == nullptr) {
        return;
    }
    destroy_list(list->top);
    list->top = nullptr;
    list->bottom = nullptr;
}

const Cell* find_max(const Cell* top) {
    if (top == nullptr) {
        return nullptr;
    }
    const Cell* max_cell = top;
    top = top->next;
    while (top != nullptr) {
        if (top->value > max_cell->value) {
            max_cell = top;
        }
        top = top->next;
    }
    return max_cell;
}

bool is_sorted(const Cell* top) {
    if (top == nullptr) {
        return true;
    }
    while (top->next != nullptr) {
        if (top->value > top->next->value) {
            return false;
        }
        top = top->next;
    }
    return true;
}

bool link_last_to(Cell* top, int index) {
    if (top == nullptr || index < 0) {
        return false;
    }
    Cell* target = nullptr;
    Cell* last = top;
    int i = 0;
    while (true) {
        if (i == index) {
            target = last;
        }
        if (last->next == nullptr) {
            break;
        }
        last = last->next;
        i++;
    }
    if (target == nullptr) {
        return false;
    }
    last->next = target;
    return true;
}

bool find_and_break_cycle(Cell* top, int* start_value, int* end_value) {
    Cell* tortoise = top;
    Cell* hare = top;
    // 1-2. Черепаха идёт на 1 ячейку, кролик на 2. Кролик дошёл до null - цикла нет
    while (hare != nullptr && hare->next != nullptr) {
        tortoise = tortoise->next;
        hare = hare->next->next;
        if (tortoise == hare) {
            break;
        }
    }
    if (hare == nullptr || hare->next == nullptr) {
        return false;
    }
    // 3-4. Кролик догнал черепаху: запускаем его с начала со скоростью 1.
    // Встретятся в начале цикла
    hare = top;
    while (hare != tortoise) {
        hare = hare->next;
        tortoise = tortoise->next;
    }
    // 5. Кролик ждёт, черепаха идёт по циклу до ячейки перед ним
    while (tortoise->next != hare) {
        tortoise = tortoise->next;
    }
    if (start_value != nullptr) {
        *start_value = hare->value;
    }
    if (end_value != nullptr) {
        *end_value = tortoise->value;
    }
    // 6. Разрываем цикл
    tortoise->next = nullptr;
    return true;
}

}  // namespace lab4
