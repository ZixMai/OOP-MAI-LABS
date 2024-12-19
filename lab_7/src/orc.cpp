#include <iostream>
#include "orc.h"

Orc::Orc(int x, int y, std::string name, bool is_alive, size_t range) : NPC(OrcType, x, y, std::move(name), is_alive, range) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

void Orc::print()
{
    std::cout << *this;
}

void Orc::visit(std::shared_ptr<Orc> npc) { kill(npc); }
void Orc::visit(std::shared_ptr<Druid> npc) { kill(npc); }
void Orc::visit(std::shared_ptr<SlaveTrader> npc) { kill(npc); }

void Orc::accept(const std::shared_ptr<NPC> &visitor) {
    auto ptrToThis = std::static_pointer_cast<Orc>(shared_from_this());
    if (!visitor->get_is_alive()) { return; }
    visitor->visit(ptrToThis);
}

std::string Orc::get_type() const { return "Orc"; }

void Orc::save(std::ostream &os)
{
    os << OrcType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Orc &orc)
{
    os << "orc: " << *static_cast<NPC *>(&orc) << std::endl;
    return os;
}