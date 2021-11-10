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
class Order //: public Subject, ILoggable
{
public:
    Order();
    Order(string* effect, string* description);
    Order(const Order& ord);
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
    /*void Attach(LogObserver* obs);
    void Detach(LogObserver* obs);
    void Notify(class ILoggable log);
    string StringToLog();*/
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
    OrdersList(vector<Order>* list);
    OrdersList(const OrdersList& ordList);
    ~OrdersList();

    void remove(int index);
    void move(int currIndex, int newIndex);
    void add(Order order);

    OrdersList& operator= (const OrdersList& ordList);
    friend ostream& operator<<(ostream& output, OrdersList& ordList);
    
#pragma region Subject and ILoggable implementation
    void Attach(Observer* obs);
    void Detach(Observer* obs);
    void Notify(ILoggable& log);
    string StringToLog();
#pragma endregion

private:
    vector<Order>* list;
};

// Deploy, a certain type of order
class Deploy : public Order
{
public:
    Deploy();

    bool validate(int numberOfArmies, Player* player, territory* territory);
    void execute(int numberOfArmies, Player* player, territory* targetTerritory);
};

// Advance, a certain type of order
class Advance : public Order
{
public:
    Advance();

    bool validate(int numberOfArmies, Player* player, territory* sourceTerritory, territory* targetTerritory);
    void execute(int numberOfArmies, Player* player, territory* sourceTerritory, territory* targetTerritory, Deck* deck);
};

// Bomb, a certain type of order
class Bomb : public Order
{
public:
    Bomb();

    bool validate(Player* player, territory* target);
    void execute(Player* player, territory* target);
};

// Blockade, a certain type of order
class Blockade : public Order
{
public:
    Blockade();

    bool validate(Player* player, Player* neutral, territory* target);
    void execute(Player* player, Player* neutral, territory* target);
};

// Airlift, a certain type of order
class Airlift : public Order
{
public:
    Airlift();

    bool validate(Player* player, territory* source, territory* target);
    void execute(int numOfArmies, Player* player, territory* source, territory* target);
};

// Negotiate, a certain type of order
class Negotiate : public Order
{
public:
    Negotiate();

    bool validate(Player* player, Player* target);
    void execute(Player* player, Player* target);
};
