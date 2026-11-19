#pragma once

#include <string>

namespace lab4 {

// Пункт меню «выход» / «назад»
inline constexpr int kExitChoice = 0;

/**
 * @brief Ввод целого числа с подсказкой.
 *
 * При вводе не числа выводит сообщение и просит повторить.
 *
 * @param prompt Текст подсказки.
 * @return Введённое число; kExitChoice, если ввод закончился (EOF).
 */
int read_number(std::string prompt);

/**
 * @brief Демонстрация задания с номером number (вывод в консоль).
 * @param number Номер задания 1-11.
 * @return false, если такого задания нет.
 */
bool run_task(int number);

}  // namespace lab4
