#pragma once
#ifndef SOLDIER_H
#define SOLDIER_H

//#include <string>
#include <vector>

enum class UnitType
{
    Archer, Cavalry, Infantry
};

class IUnit
{
public:
    virtual int getAliveCount() const = 0;
    virtual std::vector<IUnit*> getSoldiers() = 0;
    //virtual int getTotalAtt() = 0;
    //virtual int getTotalHp() = 0;
};

class Soldier : public IUnit
{
public:

    bool isAlive() const { return m_hp > 0; }
    int getAliveCount() const override
    {
        if(m_hp > 0)
            return 1;
        else
            return 0;
    }

    std::vector<IUnit*> getSoldiers() override
    {
        return std::vector<IUnit*>({this});
    }

    void takeDamage(int dmg) {
        m_hp -= dmg;
        if (m_hp < 0) m_hp = 0;
    }

    int getDps() const { return m_dps; }
    UnitType getType() const { return m_type; }

    void setType(const UnitType type){this->m_type = type;}
    void setHp(const int hp){this->m_hp = hp;}
    void setDps(const int dps){this->m_dps = dps;}

private:
    UnitType m_type;
    int m_hp{0};
    int m_dps{0};
};

class Builder
{
public:
    virtual void reset() = 0;
    virtual void setType(const UnitType t) = 0;
    virtual void setHp(int h) = 0;
    virtual void setDps(int d) = 0;
};

class SoldierBuilder : public Builder
{
public:
    SoldierBuilder(){this->reset();}
    void reset() {this->soldier = new Soldier;}
    void setType(const UnitType t) override {soldier->setType(t);}
    void setHp(int h) override {soldier->setHp(h);}
    void setDps(int d) override {soldier->setDps(d);}

    Soldier* getSoldier() {return soldier;}

private:
    Soldier* soldier;
};

class Director
{
public:
    void makeArcher(Builder* builder)
    {
        builder->reset();
        builder->setType(UnitType::Archer);
        builder->setHp(60);
        builder->setDps(15);
    }

    void makeCavalry(Builder* builder)
    {
        builder->reset();
        builder->setType(UnitType::Archer);
        builder->setHp(120);
        builder->setDps(25);
    }

    void makeInfantry(Builder* builder)
    {
        builder->reset();
        builder->setType(UnitType::Archer);
        builder->setHp(100);
        builder->setDps(20);
    }
};

#endif // SOLDIER_H
