#include <iostream>
#include <cstring>
#include <fstream>
#include "src/npc.h"
#include "src/factory.h"
#include "src/backup.h"

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}

set_t fight(const set_t &array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) && (attacker->is_close(defender, distance)))
            {
                defender->accept(attacker);
            }

    return dead_list;
}

int main()
{
    set_t array;

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % 100,
                             std::rand() % 100,
                             std::to_string(i),
                             std::rand() % 100));
    std::cout << "Saving ..." << std::endl;

    Backuper::save(array, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    array = Backuper::load("npc.txt");

    std::cout << "Fighting ..." << std::endl
              << array;

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10)
    {
        auto dead_list = fight(array, distance);
        for (auto &d : dead_list)
            array.erase(d);
    }

    std::cout << "Survivors:" << array;

    return 0;
}