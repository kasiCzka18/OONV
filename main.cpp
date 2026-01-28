
#include "BattleStrategy.h"
#include "Soldier.h"
#include "Army.h"

#include <QCoreApplication>
//#include <random>

Soldier newSoldier(UnitType type) {
    SoldierBuilder builder;
    if (type == UnitType::Archer)
        return builder.setType(type).setHp(60).setDps(15).build();
    if (type == UnitType::Cavalry)
        return builder.setType(type).setHp(120).setDps(25).build();
    return builder.setType(type).setHp(100).setDps(20).build();
}

void generateArmy(Army& army) {
    for (int i = 0; i < 100; ++i) {
        army.archers.add(newSoldier(UnitType::Archer));
        army.cavalry.add(newSoldier(UnitType::Cavalry));
        army.infantry.add(newSoldier(UnitType::Infantry));
    }
}

int main() {
    Army armyA, armyB;

    generateArmy(armyA);
    generateArmy(armyB);

    std::cout << "Army A start: " << armyA.totalAlive() << "\n";
    std::cout << "Army B start: " << armyB.totalAlive() << "\n";

    ClassicBattleStrategy strategy;
    BattleSimulator simulator(&strategy);
    simulator.fight(armyA, armyB);
}
