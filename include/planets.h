#pragma once

#include <string>

namespace lab4 {

// Номера потоков многопотокового списка
inline constexpr int kByDistance = 1;
inline constexpr int kByMass = 2;
inline constexpr int kByDiameter = 3;

// Планета - ячейка сразу трёх отсортированных списков (потоков)
struct Planet {
    std::string name;
    double distance;  // расстояние до Солнца, а. е.
    double mass;      // масса, массы Земли
    double diameter;  // диаметр, км
    Planet* next_distance;
    Planet* next_mass;
    Planet* next_diameter;
};

/**
 * @brief Создание планеты, не связанной с потоками.
 * @return Новая планета, все ссылки next_* равны nullptr.
 */
Planet* new_planet(std::string name, double distance, double mass, double diameter);

/**
 * @brief Создание пустого многопотокового списка.
 * @return Ограничитель, его next_* - начала трёх потоков.
 */
Planet* create_planet_list();

/**
 * @brief Вставка планеты в каждый поток в отсортированном порядке (AddPlanetToList).
 * @param list Ограничитель списка.
 * @param planet Добавляемая планета.
 * @return false, если list или planet равны nullptr.
 */
bool add_planet_to_list(Planet* list, Planet* planet);

/**
 * @brief Следующая планета в потоке.
 * @param planet Текущая планета (или ограничитель - тогда первая в потоке).
 * @param thread kByDistance, kByMass или kByDiameter.
 * @return Следующая планета; nullptr в конце потока, при planet == nullptr
 *         или неверном номере потока.
 */
const Planet* next_in_thread(const Planet* planet, int thread);

/**
 * @brief Вывод планет таблицей в порядке потока thread.
 * @param list Ограничитель списка.
 * @param thread kByDistance, kByMass или kByDiameter.
 */
void print_planets(const Planet* list, int thread);

/**
 * @brief Удаление всех планет вместе с ограничителем.
 * @param list Ограничитель; при nullptr ничего не делает.
 */
void destroy_planet_list(Planet* list);

}  // namespace lab4
