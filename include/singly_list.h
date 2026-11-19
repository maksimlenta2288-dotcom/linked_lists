#pragma once

namespace lab4 {

// Ячейка однонаправленного списка
struct Cell {
    int value;
    Cell* next;
};

// Однонаправленный список с указателями на первую (top) и последнюю (bottom) ячейки
struct BottomList {
    Cell* top;
    Cell* bottom;
};

/**
 * @brief Создание ячейки.
 * @param value Значение ячейки.
 * @return Новая ячейка с next = nullptr.
 */
Cell* new_cell(int value);

/**
 * @brief Создание списка из массива (без ограничителя).
 * @param values Массив значений.
 * @param count Количество элементов.
 * @return Первая ячейка списка; nullptr, если values == nullptr или count <= 0.
 */
Cell* make_list(const int* values, int count);

/**
 * @brief Удаление всего списка (DestroyList).
 * @param top Первая ячейка; при nullptr ничего не делает.
 * @warning В списке не должно быть цикла.
 */
void destroy_list(Cell* top);

/**
 * @brief Вывод значений списка через пробел (Iterate).
 * @param top Первая ячейка; для пустого списка выводится "(пусто)".
 */
void print_list(const Cell* top);

/**
 * @brief Создание пустого списка с указателем bottom (CreateListWithBottom).
 * @return Список с top = nullptr и bottom = nullptr.
 */
BottomList create_bottom_list();

/**
 * @brief Добавление ячейки в конец за O(1) (задание 1).
 * @param list Список.
 * @param cell Добавляемая ячейка.
 * @return false, если list или cell равны nullptr.
 */
bool add_at_end_with_bottom(BottomList* list, Cell* cell);

/**
 * @brief Добавление ячейки в начало с поддержкой bottom (задание 1).
 * @param list Список.
 * @param cell Добавляемая ячейка.
 * @return false, если list или cell равны nullptr.
 */
bool add_at_beginning_with_bottom(BottomList* list, Cell* cell);

/**
 * @brief Удаление первой ячейки со значением target (задание 1).
 *
 * Если удалена последняя ячейка, bottom переносится на предыдущую.
 * Если удалена единственная, top и bottom обнуляются.
 *
 * @param list Список.
 * @param target Удаляемое значение.
 * @return false, если list == nullptr или значения нет в списке.
 */
bool delete_with_bottom(BottomList* list, int target);

/**
 * @brief Удаление всех ячеек списка с указателем bottom.
 * @param list Список; после вызова top и bottom равны nullptr.
 */
void destroy_bottom_list(BottomList* list);

/**
 * @brief Поиск ячейки с наибольшим значением (задание 2).
 * @param top Первая ячейка.
 * @return Ячейка с наибольшим значением; nullptr для пустого списка.
 */
const Cell* find_max(const Cell* top);

/**
 * @brief Проверка, отсортирован ли список по неубыванию (задание 9).
 * @param top Первая ячейка.
 * @return true, если каждый элемент не больше следующего; пустой список отсортирован.
 */
bool is_sorted(const Cell* top);

/**
 * @brief Создание цикла: последняя ячейка ссылается на ячейку с номером index.
 * @param top Первая ячейка.
 * @param index Номер ячейки, начиная с 0.
 * @return false, если top == nullptr или index вне списка.
 */
bool link_last_to(Cell* top, int index);

/**
 * @brief Поиск и разрыв цикла алгоритмом черепахи и кролика (задание 11).
 * @param top Первая ячейка.
 * @param start_value Сюда записывается значение в начале цикла (если не nullptr).
 * @param end_value Сюда записывается значение в конце цикла (если не nullptr).
 * @return true, если цикл был и он разорван; false, если цикла нет.
 */
bool find_and_break_cycle(Cell* top, int* start_value, int* end_value);

}  // namespace lab4
