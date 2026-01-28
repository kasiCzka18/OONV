#pragma once
#ifndef SOLDIER_H
#define SOLDIER_H

//#include <string>

enum class UnitType
{
    Archer, Cavalry, Infantry
};

class Soldier
{
public:
    Soldier(UnitType type, int hp, int dps)
        : type(type), hp(hp), dps(dps) {}

    bool isAlive() const { return hp > 0; }

    void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    int getDps() const { return dps; }
    UnitType getType() const { return type; }

private:
    UnitType type;
    int hp;
    int dps;
};

class SoldierBuilder {
public:
    SoldierBuilder& setType(UnitType t) {
        type = t;
        return *this;
    }

    SoldierBuilder& setHp(int h) {
        hp = h;
        return *this;
    }

    SoldierBuilder& setDps(int d) {
        dps = d;
        return *this;
    }

    Soldier build() {
        return Soldier(type, hp, dps);
    }

private:
    UnitType type;
    int hp;
    int dps;
};
#endif // SOLDIER_H
