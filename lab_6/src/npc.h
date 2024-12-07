#pragma once
#include <memory>
#include <random>
#include <set>

#include "logger/ILogger.h"

struct NPC;
struct Druid;
struct Orc;
struct SlaveTrader;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    DruidType = 1,
    OrcType = 2,
    SlaveTraderType = 3
};

struct IFightObserver{
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

struct NPC : std::enable_shared_from_this<NPC>
{
    NpcType type;
    int x{0};
    int y{0};
    std::string name;
    bool is_alive{true};
    std::vector<std::shared_ptr<Logger::ILogger>> loggers;

    NPC(NpcType t, int _x, int _y, std::string _name, bool _is_alive);
    NPC(NpcType t, std::istream &is);

    void subscribe(const std::shared_ptr<Logger::ILogger>&logger);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual void accept(const std::shared_ptr<NPC>& npc) = 0;

    std::string get_name() const;
    bool get_is_alive() const;

    virtual std::string get_type() const = 0;

    virtual void visit(std::shared_ptr<SlaveTrader> npc) = 0;
    virtual void visit(std::shared_ptr<Druid> npc) = 0;
    virtual void visit(std::shared_ptr<Orc> npc) = 0;

    virtual void print() = 0;

    void kill(const std::shared_ptr<NPC>& victim);
    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};