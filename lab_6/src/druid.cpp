#include <iostream>
#include <utility>
#include "druid.h"

Druid::Druid(int x, int y, std::string name, bool is_alive) : NPC(DruidType, x, y, std::move(name), is_alive) {}
Druid::Druid(std::istream &is) : NPC(DruidType, is) {}

void Druid::visit(std::shared_ptr<Orc> npc) {  }
void Druid::visit(std::shared_ptr<Druid> npc) {  }
void Druid::visit(std::shared_ptr<SlaveTrader> npc) {  }

void Druid::accept(const std::shared_ptr<NPC> &visitor) {
    auto ptrToThis = std::static_pointer_cast<Druid>(shared_from_this());
    visitor->visit(ptrToThis);
}

void Druid::print()
{
    std::cout << *this;
}

std::string Druid::get_type() const { return "Druid"; }

void Druid::save(std::ostream &os) 
{
    os << DruidType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Druid &druid)
{
    os << "druid: " << *static_cast<NPC *>(&druid) << std::endl;
    return os;
}