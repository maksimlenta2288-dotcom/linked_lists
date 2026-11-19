#include "planets.h"

#include <iostream>

namespace lab4 {

Planet* new_planet(std::string name, double distance, double mass, double diameter) {
    Planet* planet = new Planet;
    planet->name = name;
    planet->distance = distance;
    planet->mass = mass;
    planet->diameter = diameter;
    planet->next_distance = nullptr;
    planet->next_mass = nullptr;
    planet->next_diameter = nullptr;
    return planet;
}

Planet* create_planet_list() {
    return new_planet("", 0, 0, 0);
}

// Каждый поток - сортированный однонаправленный список: ищем ячейку,
// после которой вставлять, и вставляем как InsertCell
bool add_planet_to_list(Planet* list, Planet* planet) {
    if (list == nullptr || planet == nullptr) {
        return false;
    }
    Planet* after_me = list;
    while (after_me->next_distance != nullptr &&
           after_me->next_distance->distance < planet->distance) {
        after_me = after_me->next_distance;
    }
    planet->next_distance = after_me->next_distance;
    after_me->next_distance = planet;

    after_me = list;
    while (after_me->next_mass != nullptr && after_me->next_mass->mass < planet->mass) {
        after_me = after_me->next_mass;
    }
    planet->next_mass = after_me->next_mass;
    after_me->next_mass = planet;

    after_me = list;
    while (after_me->next_diameter != nullptr &&
           after_me->next_diameter->diameter < planet->diameter) {
        after_me = after_me->next_diameter;
    }
    planet->next_diameter = after_me->next_diameter;
    after_me->next_diameter = planet;
    return true;
}

const Planet* next_in_thread(const Planet* planet, int thread) {
    if (planet == nullptr) {
        return nullptr;
    }
    if (thread == kByDistance) {
        return planet->next_distance;
    } else if (thread == kByMass) {
        return planet->next_mass;
    } else if (thread == kByDiameter) {
        return planet->next_diameter;
    }
    return nullptr;
}

void print_planets(const Planet* list, int thread) {
    std::cout << "а. е.\tмасса\tдиаметр\tпланета" << std::endl;
    const Planet* planet = next_in_thread(list, thread);
    while (planet != nullptr) {
        std::cout << planet->distance << "\t" << planet->mass << "\t" << planet->diameter << "\t"
                  << planet->name << std::endl;
        planet = next_in_thread(planet, thread);
    }
}

// Каждая планета стоит в потоке по расстоянию ровно один раз - удаляем по нему
void destroy_planet_list(Planet* list) {
    while (list != nullptr) {
        Planet* next_planet = list->next_distance;
        delete list;
        list = next_planet;
    }
}

}  // namespace lab4
