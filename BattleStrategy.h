#pragma once
#ifndef BATTLESTRATEGY_H
#define BATTLESTRATEGY_H

#include "Army.h"

//#include <random>
#include <iostream>

class BattleStrategy {
public:
    virtual ~BattleStrategy() = default;
    virtual void executeRound(Army& a, Army& b) = 0;
};

class ClassicBattleStrategy : public BattleStrategy {
public:
    void executeRound(Army& a, Army& b) override {
        archerPhase(a, b);
        archerPhase(b, a);

        cavalryPhase(a, b);
        cavalryPhase(b, a);

        infantryPhase(a, b);
        infantryPhase(b, a);

        allOutPhase(a, b);
        allOutPhase(b, a);
    }

private:
    // Najde prvního živého vojáka v libovolné skupině
    Soldier* firstAliveAny(Army& army) {
        if (auto s = firstAlive(army.archers)) return s;
        if (auto s = firstAlive(army.cavalry)) return s;
        if (auto s = firstAlive(army.infantry)) return s;
        return nullptr;
    }

    Soldier* firstAlive(ArmyGroup& group) {
        for (auto& s : group.getSoldiers())
            if (s.isAlive())
                return &s;
        return nullptr;
    }

    void archerPhase(Army& attacker, Army& defender) {
        attackGroup(attacker.archers, defender.infantry, 1.5);
    }

    void cavalryPhase(Army& attacker, Army& defender) {
        attackGroup(attacker.cavalry, defender.archers, 1.5);
    }

    void infantryPhase(Army& attacker, Army& defender) {
        attackGroup(attacker.infantry, defender.cavalry, 1.5);
    }

    /*
     ČTVRTÁ FÁZE:
     Pokud zbyly jednotky, které nemají přirozený cíl,
     útočí se bez bonusu na jakéhokoliv živého protivníka.
    */
    void allOutPhase(Army& attacker, Army& defender) {
        Soldier* target = firstAliveAny(defender);
        if (!target) return;

        for (auto& s : attacker.archers.getSoldiers()) {
            if (s.isAlive()) {
                target->takeDamage(s.getDps());
                if (!target->isAlive())
                    target = firstAliveAny(defender);
                if (!target) return;
            }
        }

        for (auto& s : attacker.cavalry.getSoldiers()) {
            if (s.isAlive()) {
                target->takeDamage(s.getDps());
                if (!target->isAlive())
                    target = firstAliveAny(defender);
                if (!target) return;
            }
        }

        for (auto& s : attacker.infantry.getSoldiers()) {
            if (s.isAlive()) {
                target->takeDamage(s.getDps());
                if (!target->isAlive())
                    target = firstAliveAny(defender);
                if (!target) return;
            }
        }
    }

    // Standardní útok skupiny s bonusem
    void attackGroup(ArmyGroup& attackers,
                     ArmyGroup& defenders,
                     double bonus) {

        Soldier* target = firstAlive(defenders);
        if (!target) return;

        for (auto& attacker : attackers.getSoldiers()) {
            if (!attacker.isAlive()) continue;

            target->takeDamage(
                static_cast<int>(attacker.getDps() * bonus)
                );

            if (!target->isAlive()) {
                target = firstAlive(defenders);
                if (!target) return;
            }
        }
    }
};

class BattleSimulator {
public:
    BattleSimulator(BattleStrategy* strat)
        : strategy(strat) {}

    void fight(Army& a, Army& b) {
        int round = 1;

        while (a.totalAlive() > 0 && b.totalAlive() > 0) {
            std::cout << "Round " << round++ << "\n";

            strategy->executeRound(a, b);

            std::cout << "Army A alive: " << a.totalAlive()
                      << " | Army B alive: " << b.totalAlive()
                      << "\n\n";
        }

        if (a.totalAlive() > 0)
            std::cout << "Army A wins!\n";
        else
            std::cout << "Army B wins!\n";
    }

private:
    BattleStrategy* strategy;
};
#endif // BATTLESTRATEGY_H
