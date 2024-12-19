#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <thread>
#include "src/npc.h"
#include "src/factory.h"
#include "src/backup.h"
#include "src/coroutine.h"

using namespace std::chrono_literals;

int minX(0), maxX(30), minY(0), maxY(30);

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}

Coroutine fight(const std::set<std::shared_ptr<NPC>>& npcs)
{
    while (true) {
        for (auto &npc1 : npcs) {
            for (auto &npc2 : npcs) {
                npc1->accept(npc2);
            }
        }

        co_await std::suspend_always{};
    }
}

Coroutine moveNpcs(const std::set<std::shared_ptr<NPC>>& npcs) {
    while (true) {
        for (auto &npc : npcs) {
            if (!npc->getIsAlive()) continue;
            auto md = npc->getMoveDistance();
            auto pos = npc->getPos();

            auto range = std::rand() % static_cast<int>(std::floor(md));
            std::uniform_int_distribution<int> distribution(-std::floor(std::sqrt(range)), std::floor(std::sqrt(range)));
            auto randomEngine = std::mt19937();
            auto dx = distribution(randomEngine);
            auto dy = static_cast<int>(std::floor(std::sqrt(range * range - dx * dx)) * std::pow(-1, range % 2));

            if (pos.first + dx > maxX) dx = maxX - pos.first;
            if (pos.second + dy > maxY) dy = maxY - pos.second;

            if (pos.first + dx < minX) dx = minX - pos.first;
            if (pos.second + dy < minY) dy = minY - pos.second;

            *npc += std::pair<int, int>(dx, dy);
        }

        co_await std::suspend_always{};
    }
}


void play(int sec, const std::set<std::shared_ptr<NPC>>& npcs) {
    auto start = std::chrono::steady_clock::now();
    auto duration_limit = std::chrono::seconds(sec);
    Logger::ConsoleLogger logger;

    auto st = std::thread([npcs, start, duration_limit] (){
        auto fightCor = fight(npcs);
        auto moveCor = moveNpcs(npcs);

        while (std::chrono::steady_clock::now() - start < duration_limit){
            moveCor.resume();
            fightCor.resume();

            std::this_thread::sleep_for(250ms);
        }
    });

     while(std::chrono::steady_clock::now() - start < duration_limit){
         std::vector field(maxY + 1, std::vector<char>(maxX + 1, ' '));

         for (const auto & npc: npcs) {
             auto [x, y] = npc->getPos();

             if (!npc->get_is_alive()) {
                 field[y][x] = 'x';
                 continue;
             }

             switch (npc->get_npc_type()) {
                 case SlaveTraderType:
                     field[y][x] = 'S';
                 break;
                 case OrcType:
                     field[y][x] = 'O';
                 break;
                 case DruidType:
                     field[y][x] = 'D';
                 break;
                 default:
                     throw std::logic_error("Unknown type");
             }
         }

         std::stringstream stream;
         for (const auto & line : field) {
             for (const auto & ch : line) {
                 stream << '[' << ch << ']';
             }
             stream << std::endl;
         }
         logger.log(stream.str());

        std::this_thread::sleep_for(1s);
    }

    st.join();
}

int main()
{
    set_t array;

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % 30 + 1,
                             std::rand() % 30 + 1,
                             std::to_string(i),
                             std::rand() % 100));

    play(15, array);

    return 0;
}