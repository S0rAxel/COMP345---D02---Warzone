#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

// An Order object, which contains data members and functions related to a Warzone order
class Order
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

private:
    string* effect;
    string* description;
    bool* hasBeenExecuted;
};

// A list of Order objects
class OrdersList
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

private:
    vector<Order>* list;
};

// Deploy, a certain type of order
class Deploy : public Order
{
public:
    Deploy();

    bool validate();
    void execute();
};

// Advance, a certain type of order
class Advance : public Order
{
public:
    Advance();

    bool validate();
    void execute();
};

// Bomb, a certain type of order
class Bomb : public Order
{
public:
    Bomb();

    bool validate();
    void execute();
};

// Blockade, a certain type of order
class Blockade : public Order
{
public:
    Blockade();

    bool validate();
    void execute();
};

// Airlift, a certain type of order
class Airlift : public Order
{
public:
    Airlift();

    bool validate();
    void execute();
};

// Negotiate, a certain type of order
class Negotiate : public Order
{
public:
    Negotiate();

    bool validate();
    void execute();
};
