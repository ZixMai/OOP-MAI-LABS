#pragma once
#include <fstream>
#include <cstring>
#include "npc.h"
#include "factory.h"
#include <iostream>

class Backuper{
public:
    void static save(const set_t &array, const std::string &filename)
    {
        std::ofstream fs(filename);
        fs << array.size() << std::endl;
        for (auto &n : array)
            n->save(fs);
        fs.flush();
        fs.close();
    }

    set_t static load(const std::string &filename)
    {
        set_t result;
        std::ifstream is(filename);
        if (is.good() && is.is_open())
        {
            int count;
            is >> count;
            for (int i = 0; i < count; ++i)
                result.insert(factory(is));
            is.close();
        }
        else
            std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return result;
    }
};