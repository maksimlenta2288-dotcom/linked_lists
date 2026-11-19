#pragma once

#include <string>

namespace lab4 {

// Ячейка сортированного двунаправленного списка имён
struct NameCell {
    std::string name;
    NameCell* next;
    NameCell* prev;
};

// Список имён с ограничителями top и bottom
struct NameList {
    NameCell* top;
    NameCell* bottom;
};

/**
 * @brief Создание списка имён (имена должны идти по алфавиту).
 * @param names Массив имён.
 * @param count Количество имён.
 * @return Список; при names == nullptr или count <= 0 - пустой список с ограничителями.
 */
NameList make_name_list(const std::string* names, int count);

/**
 * @brief Удаление списка вместе с ограничителями.
 * @param list Список; при nullptr ничего не делает.
 */
void destroy_name_list(NameList* list);

/**
 * @brief Сколько ячеек просмотрено при поиске от верхнего ограничителя (задание 7).
 *
 * Поиск останавливается на найденном имени или на первом имени больше искомого.
 *
 * @param list Список.
 * @param target Искомое имя.
 * @return Число просмотренных ячеек; -1, если list == nullptr.
 */
int steps_from_top(const NameList* list, std::string target);

/**
 * @brief Сколько ячеек просмотрено при поиске от нижнего ограничителя (задание 7).
 *
 * Поиск останавливается на найденном имени или на первом имени меньше искомого.
 *
 * @param list Список.
 * @param target Искомое имя.
 * @return Число просмотренных ячеек; -1, если list == nullptr.
 */
int steps_from_bottom(const NameList* list, std::string target);

}  // namespace lab4
