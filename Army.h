#pragma once
#ifndef ARMY_H
#define ARMY_H

#include "Soldier.h"

#include <vector>

class ComplexUnit : public IUnit
{
public:
    void add(IUnit* s)
    {
        m_units.push_back(s);
    }

    std::vector<IUnit*> getSoldiers() override
    {
        std::vector<IUnit*> tmp;
        for(auto& s : m_units)
            for(auto &ss : s->getSoldiers())
                tmp.push_back(ss);
        return tmp;
    }

    int getAliveCount() const override
    {
        int count = 0;
        for (const auto& s : m_units)
            count += s->getAliveCount();
        return count;
    }

private:
    std::vector<IUnit*> m_units;
};

#endif // ARMY_H

