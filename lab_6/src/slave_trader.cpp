#include <iostream>
#include <utility>
#include "slave_trader.h"

SlaveTrader::SlaveTrader(int x, int y, std::string name, bool is_alive) : NPC(SlaveTraderType, x, y, std::move(name), is_alive) {}
SlaveTrader::SlaveTrader(std::istream &is) : NPC(SlaveTraderType, is) {}

void SlaveTrader::print()
{
    std::cout << *this;
}

void SlaveTrader::save(std::ostream &os)
{
    os << SlaveTraderType << std::endl;
    NPC::save(os);
}

void SlaveTrader::visit(std::shared_ptr<SlaveTrader> npc) {  }
void SlaveTrader::visit(std::shared_ptr<Druid> npc) { kill(npc); }
void SlaveTrader::visit(std::shared_ptr<Orc> npc) {  }

void SlaveTrader::accept(const std::shared_ptr<NPC> &visitor) {
    auto ptrToThis = std::static_pointer_cast<SlaveTrader>(shared_from_this());
    visitor->visit(ptrToThis);
}

std::string SlaveTrader::get_type() const { return "SlaveTrader"; }

std::ostream &operator<<(std::ostream &os, SlaveTrader &slave_trader)
{
    os << "slave trader: " << *static_cast<NPC *>(&slave_trader) << std::endl;
    return os;
}