#include "Orders.h"
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::to_string;


Order::Order()
{
    effect = new string("unset");
    description = new string("unset");
    hasBeenExecuted = new bool(false);
}

Order::Order(string* effect, string* description) : effect(effect), description(description)
{
    hasBeenExecuted = new bool(false);
}

Order::Order(const Order& ord)
{
    effect = new string(*ord.effect);
    description = new string(*ord.description);
    hasBeenExecuted = new bool(*ord.hasBeenExecuted);
}

Order::~Order()
{
    delete effect;
    delete description;
    delete hasBeenExecuted;
}

// Getter for effect
string* Order::getEffect()
{
    return effect;
}

// Setter for effect
void Order::setEffect(string* passedEffect)
{
    *effect = *passedEffect;
}

// Getter for description
string* Order::getDescription()
{
    return description;
}

// Setter for description
void Order::setDescription(string* passedDescription)
{
    *description = *passedDescription;
}

// Getter for hasBeenExecuted
bool* Order::getHasBeenExecuted()
{
    return hasBeenExecuted;
}

// Setter for hasBeenExecuted
void Order::setHasBeenExecuted(bool* passedHasBeenExecuted)
{
    *hasBeenExecuted = *passedHasBeenExecuted;
}

// Assignment operator for Order
Order& Order::operator= (const Order& order)
{
    *effect = *order.effect;
    *description = *order.description;

    return *this;
}

// Stream insertion operator for Order
ostream& operator<< (ostream& output, Order& order)
{
    if (*order.hasBeenExecuted)
        return cout << "The order has been executed: " << *order.effect << "\n" << *order.description;
    else
        return cout << *order.description;
}

OrdersList::OrdersList()
{
    list = new vector<Order>();
}

OrdersList::OrdersList(vector<Order>* passedList)
{
    list = new vector<Order>();
    for (int i = 0; i < passedList->size(); i++)
    {
        Order copyOfOrder = Order(passedList->at(i));
        list->push_back(copyOfOrder);
    }
}

OrdersList::OrdersList(const OrdersList& ordList)
{
    list = new vector<Order>();
    for (int i = 0; i < ordList.list->size(); i++)
    {
        Order copyOfOrder = Order(ordList.list->at(i));
        list->push_back(copyOfOrder);
    }
}

OrdersList::~OrdersList()
{
    delete list;
}

// Moves an order at a specified index
void OrdersList::move(int currIndex, int newIndex)
{
    Order ord = Order(list->at(currIndex));

    remove(currIndex);

    vector<Order>* newList = new vector<Order>;
    for (int i = 0; i < newIndex; i++)
        newList->push_back(list->at(i));

    newList->push_back(ord);

    for (int i = newIndex + 1; i <= list->size(); i++)
        newList->push_back(list->at(i - 1));

    list->clear();
    list = newList;
}

// Removes an order in the list at a certain index
void OrdersList::remove(int index)
{
    vector<Order>* newList = new vector<Order>;
    for (int i = 0; i < list->size(); i++)
    {
        if (i != index)
            newList->push_back(list->at(i));
    }

    list->clear();
    list = newList;
}

// For testing purposes. Will probably be replaced with another method eventually
void OrdersList::add(Order order)
{
    list->push_back(order);
}

// Assignment operator for OrdersList
OrdersList& OrdersList::operator= (const OrdersList& ordList)
{
    for (int i = 0; i < ordList.list->size(); i++)
    {
        Order copyOfOrder = Order(ordList.list->at(i));
        list->push_back(copyOfOrder);
    }

    return *this;
}

// Stream insertion operator for OrdersList
ostream& operator<< (ostream& output, OrdersList& ordList)
{
    string information;
    for (int i = 0; i < ordList.list->size(); i++)
    {
        information += "Index " + to_string(i) + ": " + *ordList.list->at(i).getDescription() + "\n";
    }

    return cout << "The OrdersList contains a vector of Order objects of size " << ordList.list->size() << ": \n" << information;
}

Deploy::Deploy() : Order(new string("deploy"), new string("The deploy order places some armies on one of the current player's territories.")) {}

// Validates the order
bool Deploy::validate()
{
    // Code for the demonstration
    cout << "validate fct executed" << endl;
    return true; // TEMP
}

// Executes the order, provided that the order is valid
void Deploy::execute()
{
    // Code for the demonstration
    cout << "execute fct executed" << endl;

    if (validate())
    {
        setHasBeenExecuted(new bool(true));
    }
}

Advance::Advance() : Order(new string("advance"), new string ("The advance order moves some armies from one of the current player's territories (source) "
"to an adjacent territory (target). If the target territory belongs to the current player, the armies are moved to the target territory. "
"If the target territory belongs to another player, an attack happens between the two territories.")) {}

bool Advance::validate()
{
    return true; // TEMP
}

void Advance::execute()
{
    if (validate())
    {
        // Some code...

        setHasBeenExecuted(new bool(true));
    }
}

Bomb::Bomb() : Order(new string("bomb"), new string("The bomb order destroys half of the armies located on an opponent’s territory that is adjacent to one "
"of the current player's territories.")) {}

bool Bomb::validate()
{
    return true; // TEMP
}

void Bomb::execute()
{
    if (validate())
    {
        // Some code...

        setHasBeenExecuted(new bool(true));
    }
}

Blockade::Blockade() : Order(new string("blockade"), new string("The blockade order triples the number of armies on one of the current player's territories "
"and make it a neutral territory.")) {}

bool Blockade::validate()
{
    return true; // TEMP
}

void Blockade::execute()
{
    if (validate())
    {
        // Some code...

        setHasBeenExecuted(new bool(true));
    }
}

Airlift::Airlift() : Order(new string("airlift"), new string("The airlift order advances some armies from one of the current player's territories to any "
"another territory.")) {}

bool Airlift::validate()
{
    return true; // TEMP
}

void Airlift::execute()
{
    if (validate())
    {
        // Some code...

        setHasBeenExecuted(new bool(true));
    }
}

Negotiate::Negotiate() : Order(new string("negotiate"), new string("The negotiate order prevents attacks between the current player and another player until "
"the end of the turn.")) {}

bool Negotiate::validate()
{
    return true; // TEMP
}

void Negotiate::execute()
{
    if (validate())
    {
        // Some code...

        setHasBeenExecuted(new bool(true));
    }
}
