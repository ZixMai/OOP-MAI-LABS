#pragma once
#include "npc.h"
#include <memory>
#include <iostream>
#include "logger/console_logger.h"
#include "druid.h"
#include "slave_trader.h"
#include "orc.h"

static Logger::ConsoleLogger logger;
std::shared_ptr<Logger::ILogger> logger_ptr(&logger, [](Logger::ILogger*logger){});

std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type)
    {
        switch (type)
        {
            case DruidType:
                result = std::make_shared<Druid>(is);
                break;
            case OrcType:
                result = std::make_shared<Orc>(is);
                break;
            case SlaveTraderType:
                result = std::make_shared<SlaveTrader>(is);
                break;
        }
    }
    else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result)
        result->subscribe(logger_ptr);

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y, std::string name, size_t range, bool is_alive = true)
{
    std::cout << "Type:" << (int)type << std::endl;
    std::shared_ptr<NPC> result;
    switch (type)
    {
        case DruidType:
            result = std::make_shared<Druid>(x, y, name, is_alive, range);
            break;
        case OrcType:
            result = std::make_shared<Orc>(x, y, name, is_alive, range);
            break;
        case SlaveTraderType:
            result = std::make_shared<SlaveTrader>(x, y, name, is_alive, range);
            break;
        default:
            break;
    }
    if (result)
        result->subscribe(logger_ptr);

    return result;
}
