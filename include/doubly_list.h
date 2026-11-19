#pragma once

namespace lab4 {

// Ячейка двунаправленного списка
struct DCell {
    int value;
    DCell* next;
    DCell* prev;
};

// Двунаправленный список с ограничителями top и bottom.
// В top хранится наименьшее значение int, в bottom - наибольшее (нужно в задании 8)
struct DList {
    DCell* top;
    DCell* bottom;
};

/**
 * @brief Создание ячейки.
 * @param value Значение ячейки.
 * @return Новая ячейка с next = prev = nullptr.
 */
DCell* new_dcell(int value);

/**
 * @brief Создание пустого списка из двух связанных ограничителей.
 * @return Список; освобождается через destroy_dlist.
 */
DList create_dlist();

/**
 * @brief Удаление всех ячеек вместе с ограничителями.
 * @param list Список; при nullptr ничего не делает.
 */
void destroy_dlist(DList* list);

/**
 * @brief Добавление ячейки в начало (задание 3).
 * @param list Список.
 * @param cell Добавляемая ячейка.
 * @return false, если list или cell равны nullptr.
 */
bool add_at_beginning_d(DList* list, DCell* cell);

/**
 * @brief Добавление ячейки в конец (задание 4).
 * @param list Список.
 * @param cell Добавляемая ячейка.
 * @return false, если list или cell равны nullptr.
 */
bool add_at_end_d(DList* list, DCell* cell);

/**
 * @brief Вставка ячейки после after_me (InsertCell).
 * @param after_me Ячейка, после которой вставляем; не нижний ограничитель.
 * @param cell Вставляемая ячейка.
 * @return false, если указатель равен nullptr или after_me - нижний ограничитель.
 */
bool insert_cell_d(DCell* after_me, DCell* cell);

/**
 * @brief Добавление в начало через InsertCell (задание 5).
 * @return false, если list или cell равны nullptr.
 */
bool add_at_beginning_via_insert(DList* list, DCell* cell);

/**
 * @brief Добавление в конец через InsertCell (задание 5).
 * @return false, если list или cell равны nullptr.
 */
bool add_at_end_via_insert(DList* list, DCell* cell);

/**
 * @brief Поиск первой ячейки со значением target.
 * @param list Список.
 * @param target Искомое значение.
 * @return Найденная ячейка; nullptr, если её нет или list == nullptr.
 */
DCell* find_d(const DList* list, int target);

/**
 * @brief Удаление ячейки из списка с освобождением памяти (задание 6).
 * @param target Удаляемая ячейка.
 * @return false, если target == nullptr или это ограничитель.
 */
bool delete_cell_d(DCell* target);

/**
 * @brief Вставка в сортированный список (задание 8).
 * @param list Список, отсортированный по неубыванию.
 * @param cell Вставляемая ячейка.
 * @return false, если list или cell равны nullptr.
 */
bool insert_sorted_d(DList* list, DCell* cell);

/**
 * @brief Вывод списка вперёд по next и назад по prev: "1 2 3 | 3 2 1".
 * @param list Список; при nullptr ничего не выводит.
 */
void print_dlist(const DList* list);

}  // namespace lab4
