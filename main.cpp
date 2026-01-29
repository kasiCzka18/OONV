
#include "BattleStrategy.h"
#include "Soldier.h"
#include "Army.h"

#include <iostream>>
#include <QCoreApplication>
//#include <random>

//Soldier newSoldier(UnitType type)
//{
//    SoldierBuilder builder;
//    if (type == UnitType::Archer)
//        return builder.setType(type).setHp(60).setDps(15).build();
//    if (type == UnitType::Cavalry)
//        return builder.setType(type).setHp(120).setDps(25).build();
//    return builder.setType(type).setHp(100).setDps(20).build();
//}

void generateArmy(ComplexUnit& army)
{
    Director director;
    SoldierBuilder soldierBuilder;
    ComplexUnit *archers = new ComplexUnit;
    ComplexUnit *infantry = new ComplexUnit;
    ComplexUnit *cavalry = new ComplexUnit;

    for (int i = 0; i < 100; ++i)
    {
        director.makeArcher(&soldierBuilder);
        archers->add(soldierBuilder.getSoldier());

        director.makeInfantry(&soldierBuilder);
        infantry->add(soldierBuilder.getSoldier());

        director.makeCavalry(&soldierBuilder);
        cavalry->add(soldierBuilder.getSoldier());
    }
    army.add(archers);
    army.add(infantry);
    army.add(cavalry);
}

int main()
{
    ComplexUnit army1;
    ComplexUnit army2;

    generateArmy(army1);
    generateArmy(army2);

    std::cout << "Army A start: " << army1.getAliveCount() << "\n";
    std::cout << "Army B start: " << army2.getAliveCount() << "\n";

    const auto &s = army2.getSoldiers();

    std::cout << s.size();
   ClassicBattleStrategy strategy;
   BattleSimulator simulator(&strategy);
   simulator.fight(army1, army2);
}
