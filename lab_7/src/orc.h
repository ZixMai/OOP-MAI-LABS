#pragma once
#include "npc.h"
#include "druid.h"
#include "orc.h"
#include "slave_trader.h"

class Orc : public NPC
{
    public:
    Orc(int x, int y, std::string name, bool is_alive, size_t range);
    explicit Orc(std::istream &is);
    void print() override;

    void accept(const std::shared_ptr<NPC>& visitor) override;

    void visit(std::shared_ptr<Druid> npc) override;
    void visit(std::shared_ptr<Orc> npc) override;
    void visit(std::shared_ptr<SlaveTrader> npc) override;

    std::string get_type() const override;

    void save(std::ostream &os) override;
    friend std::ostream &operator<<(std::ostream &os, Orc &orc);
};