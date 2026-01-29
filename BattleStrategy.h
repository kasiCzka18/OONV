#pragma once

#ifndef BATTLESTRATEGY_H
#define BATTLESTRATEGY_H

#include <random>

#include "Army.h"
#include "Soldier.h"

//#include <random>
#include <iostream>

class BattleStrategy {
public:
    virtual void executeRound(IUnit& a, IUnit& b) = 0;
};



class ClassicBattleStrategy : public BattleStrategy {
public:
    void executeRound(IUnit& a, IUnit& b) override
    {
        auto soldiersA = a.getSoldiers();
        auto soldiersB = b.getSoldiers();

        Soldier* sa = getRandomAlive(soldiersA);
        Soldier* sb = getRandomAlive(soldiersB);

        if (!sa || !sb) return;

        // vzájemný útok
        sb->takeDamage(sa->getDps());
        sa->takeDamage(sb->getDps());
    }

private:
    Soldier* getRandomAlive(std::vector<IUnit*>& units)
    {
        std::vector<Soldier*> alive;

        for (auto* u : units)
        {
            auto* s = dynamic_cast<Soldier*>(u);
            if (s && s->isAlive())
                alive.push_back(s);
        }

        if (alive.empty()) return nullptr;
        
        // generator nahodneho ziveho vojaka z armady
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution<> dist(0, alive.size() - 1);

        return alive[dist(rng)];
    }
};

class BattleSimulator {
public:
    BattleSimulator(BattleStrategy* strat)
        : strategy(strat) {}

    void fight(IUnit& a, IUnit& b) {
        int round = 1;

        while (a.getAliveCount() > 0 && b.getAliveCount() > 0) {
            std::cout << "Round " << round++ << "\n";

            strategy->executeRound(a, b);

            std::cout << "Army A alive: " << a.getAliveCount()
                      << " | Army B alive: " << b.getAliveCount()
                      << "\n\n";
        }

        if (a.getAliveCount() > 0)
            std::cout << "Army A wins!\n";
        else
            std::cout << "Army B wins!\n";
    }

private:
    BattleStrategy* strategy;
};
#endif // BATTLESTRATEGY_H
