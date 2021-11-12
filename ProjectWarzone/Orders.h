#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Cards.h"
#include "LoggingObserver.h"

using std::string;
using std::ostream;
using std::vector;

// An Order object, which contains data members and functions related to a Warzone order
class Order : public Subject, ILoggable
{
public:
    Order();
    Order(string* effect, string* description);
    Order(const Order& ord);
    virtual void execute() = 0;

    ~Order();
    string* getEffect();
    void setEffect(string* effect);
    string* getDescription();
    void setDescription(string* description);
    bool* getHasBeenExecuted();
    void setHasBeenExecuted(bool* hasBeenExecuted);

    Order& operator= (const Order& order);
    friend ostream& operator<< (ostream& output, Order& order);

#pragma region Subject and ILoggable implementation
    void Attach(Observer* obs);
    void Detach(Observer* obs);
    void Notify(ILoggable& log);
    string StringToLog();
#pragma endregion

private:
    string* effect;
    string* description;
    bool* hasBeenExecuted;
};

// A list of Order objects
class OrdersList : public Subject, ILoggable
{
public:
    OrdersList();
    OrdersList(vector<Order*> list);
    OrdersList(const OrdersList& ordList);
    ~OrdersList();

    void remove(int index);
    void move(int currIndex, int newIndex);
    void add(Order* order);
    Order* getOrder(int i) { return list.at(i); }

    OrdersList& operator= (const OrdersList& ordList);
    friend ostream& operator<<(ostream& output, OrdersList& ordList);
    
#pragma region Subject and ILoggable implementation
    void Attach(Observer* obs);
    void Detach(Observer* obs);
    void Notify(ILoggable& log);
    string StringToLog();
#pragma endregion

private:
    vector<Order*> list;
};

// Deploy, a certain type of order
class Deploy : public Order
{
public:
    Deploy(int numberOfArmies, Player* player, territory* target);
    bool validate();
    void execute();
private:
    int numOfArmies;
    Player* player;
    territory* target;
};

// Advance, a certain type of order
class Advance : public Order
{
public:
    Advance(int numberOfArmies, Player* player, territory* sourceTerritory, territory* targetTerritory, Deck* deck);

    bool validate();
    void execute();
private:
    int numOfArmies;
    Player* player;
    territory* source;
    territory* target;
    Deck* deck;
};

// Bomb, a certain type of order
class Bomb : public Order
{
public:
    Bomb(Player* player, territory* target);

    bool validate();
    void execute();
private:
    Player* player;
    territory* target;
};

// Blockade, a certain type of order
class Blockade : public Order
{
public:
    Blockade(Player* player, Player* neutral, territory* target);

    bool validate();
    void execute();
private:
    Player* player;
    Player* neutral;
    territory* target;
};

// Airlift, a certain type of order
class Airlift : public Order
{
public:
    Airlift(int numOfArmies, Player* player, territory* source, territory* target);

    bool validate();
    void execute();
private:
    int numOfArmies;
    Player* player;
    territory* source;
    territory* target;
};

// Negotiate, a certain type of order
class Negotiate : public Order
{
public:
    Negotiate(Player* player, Player* target);

    bool validate();
    void execute();
    Player* player;
    Player* target;
};
