#include "npc.h"
#include <format>
#include <iostream>
#include <cstring>
#include <cmath>
#include <utility>

NPC::NPC(NpcType t, int _x, int _y, std::string _name, bool _is_alive, size_t _range) : type(t), x(_x), y(_y), name(std::move(_name)), is_alive(_is_alive), range(_range) {}
NPC::NPC(NpcType t, std::istream &is) : type(t)
{
    is >> x;
    is >> y;
    is >> name;
    is >> is_alive;
    is >> range;
}

void NPC::kill(const std::shared_ptr<NPC>& victim) {
    if (!is_close(victim, victim->get_range())) return;
    if (loggers.empty()) return;
    for (auto& logger : loggers)
        logger->log(std::format("{} of type {} got killed by {} of type {}", victim->get_name(), victim->get_type(), name, get_type()));
}

void NPC::subscribe(const std::shared_ptr<Logger::ILogger>&logger)
{
   loggers.push_back(logger);
}

std::string NPC::get_name() const { return name; }
bool NPC::get_is_alive() const { return is_alive; }
size_t NPC::get_range() const { return range; }

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const
{
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    return false;
}

void NPC::save(std::ostream &os)
{
    os << x << std::endl;
    os << y << std::endl;
    os << name << std::endl;
    os << is_alive << std::endl;
    os << range << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{ name:" << npc.name << ", x:" << npc.x << ", y:" << npc.y << ", is_alive:" << (npc.is_alive ? "Yes" : "No") << " }";
    return os;
}