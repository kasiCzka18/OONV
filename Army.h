#pragma once
#ifndef ARMY_H
#define ARMY_H

#include "Soldier.h"
#include <vector>

class ArmyUnit {
public:
    virtual ~ArmyUnit() = default;
    virtual int getAliveCount() const = 0;
};

class ArmyGroup : public ArmyUnit {
public:
    void add(const Soldier& s) {
        soldiers.push_back(s);
    }

    std::vector<Soldier>& getSoldiers() {
        return soldiers;
    }

    int getAliveCount() const override {
        int count = 0;
        for (const auto& s : soldiers)
            if (s.isAlive()) count++;
        return count;
    }

private:
    std::vector<Soldier> soldiers;
};

class Army {
public:
    ArmyGroup archers;
    ArmyGroup cavalry;
    ArmyGroup infantry;

    int totalAlive() const {
        return archers.getAliveCount() +
               cavalry.getAliveCount() +
               infantry.getAliveCount();
    }
};

#endif // ARMY_H
