#include "Orders.h"
#include <vector>
#include <string>
#include <random>

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

void Order::execute()
{
    Notify(*this);
}

#pragma region Subject and ILoggable
void Order::Attach(Observer* obs)
{
    Subject::Attach(obs);
}

void Order::Detach(Observer* obs)
{
    Subject::Detach(obs);
}

void Order::Notify(ILoggable& log)
{
    Subject::Notify(log);
}

string Order::StringToLog()
{
    return "Order::Execute() - "+ *effect + " order has been executed. Effect: " + *description + " \n";
}

#pragma endregion

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
}

OrdersList::OrdersList(vector<Order*> passedList)
{
    for (int i = 0; i < passedList.size(); i++)
    {
        list.push_back(passedList.at(i));
    }
}

OrdersList::OrdersList(const OrdersList& ordList)
{
    for (int i = 0; i < ordList.list.size(); i++)
    {
        list.push_back(ordList.list.at(i));
    }
}

OrdersList::~OrdersList()
{
}

// Moves an order at a specified index
void OrdersList::move(int currIndex, int newIndex)
{
    if (currIndex > newIndex)
        rotate(list.rend() - currIndex - 1, list.rend() - currIndex, list .rend() - newIndex);
    else
        rotate(list.begin() + currIndex, list.begin() + currIndex + 1, list.begin() + newIndex + 1);
}

// Removes an order in the list at a certain index
void OrdersList::remove(int index)
{
    list.erase(list.begin() + index);
}

// For testing purposes. Will probably be replaced with another method eventually
void OrdersList::add(Order* order)
{
    list.push_back(order);

    //cout << "Add method was called" << endl;
    Notify(*this);
}

// Assignment operator for OrdersList
OrdersList& OrdersList::operator= (const OrdersList& ordList)
{
    for (int i = 0; i < ordList.list.size(); i++)
    {
        list.push_back(ordList.list.at(i));
    }

    return *this;
}

#pragma region Subject and ILoggable
    void OrdersList::Attach(Observer* obs)
    {
        Subject::Attach(obs);
    }
    
    void OrdersList::Detach(Observer* obs)
    {
        Subject::Detach(obs);
    }

    void OrdersList::Notify(ILoggable& log) 
    {
        Subject::Notify(log);
    }

    string OrdersList::StringToLog()
    {
        return "OrdersList::Add() - " + *this->list.back()->getEffect()+ " order has been added \n";
    }

#pragma endregion


// Stream insertion operator for OrdersList
ostream& operator<< (ostream& output, OrdersList& ordList)
{
    string information;
    for (int i = 0; i < ordList.list.size(); i++)
    {
        information += "Index " + to_string(i) + ": " + *ordList.list.at(i)->getDescription() + "\n";
    }

    return cout << "The OrdersList contains a vector of Order objects of size " << ordList.list.size() << ": \n" << information;
}

Deploy::Deploy(int numberOfArmies, Player* player, territory* target) : Order(new string("deploy"), new string("The deploy order places some armies on one of the current player's territories.")) {
    numOfArmies = numberOfArmies;
    this->player = player;
    this->target = target;
}

// Validates the order
bool Deploy::validate()
{
    if (player == target->getOwner() && player->getReinF() >= numOfArmies)
    {
        return true;
    }
    cout << "Invalid deploy order." << endl;
    return false;
}

// Executes the order, provided that the order is valid
void Deploy::execute()
{
    if (validate())
    {
        Order::execute();
        target->addArmies(numOfArmies);
        player->removeReinf(numOfArmies);
        setHasBeenExecuted(new bool(true));
        cout << "Deploy order sucess. Target territory now has " << target->getArmies() << " armies." << endl;
    }
}

Advance::Advance(int numberOfArmies, Player* player, territory* sourceTerritory, territory* targetTerritory, Deck* deck) : Order(new string("advance"), new string ("The advance order moves some armies from one of the current player's territories (source) "
"to an adjacent territory (target). If the target territory belongs to the current player, the armies are moved to the target territory. "
"If the target territory belongs to another player, an attack happens between the two territories.")) {
    numOfArmies = numberOfArmies;
    this->player = player;
    source = sourceTerritory;
    target = targetTerritory;
    this->deck = deck;
}

bool Advance::validate()
{
    if (player == source->getOwner() && source->isAdjacentTerritory(target) && numOfArmies <= source->getArmies() && !(target->getOwner()->isNegotiate(player)))
    {
        return true;
    }
    cout << "Invalid Advance order." << endl;
    return false;
}

void Advance::execute()
{
    if (validate())
    {
        Order::execute();

        if (source->getOwner() == target->getOwner())
        {
            source->removeArmies(numOfArmies);
            target->addArmies(numOfArmies);
            cout << "Advance order sucess. Result: Moved armies between player owned territories. Target territory now has " << target->getArmies() << " armies." << endl;
        }
        else
        {
            bool capture = false;
            source->removeArmies(numOfArmies);
            int defendingArmies = target->getArmies();
            int attackingArmies = numOfArmies;
            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<std::mt19937::result_type> dist(0, 99);
            for (int i = 0; i < defendingArmies; i++) {
                if (attackingArmies == 0) {
                    break;
                }
                if (dist(rng) < 70)
                {
                    cout << "killing 1 atk" << endl;
                    attackingArmies--;
                    if (attackingArmies == 0) {
                        break;
                    }
                }
            }
            for (int i = 0; i < numOfArmies; i++) {
                if (defendingArmies == 0) {
                    break;
                }
                if (dist(rng) < 60)
                {
                    cout << "killing 1 def" << endl;
                    defendingArmies--;
                    if (defendingArmies == 0) {
                        break;
                    }
                }
            }

            if (attackingArmies > 0 && defendingArmies == 0) {
                target->getOwner()->removeTerritories(target);
                target->setOwner(player);
                player->addTerritories(target);
                target->setArmies(attackingArmies);
                capture = true;
                cout << "Advance order sucess. Result: Capture with " << attackingArmies << " armies remaining." << endl;
            }
            else if (defendingArmies > 0) {
                source->addArmies(attackingArmies);
                target->setArmies(defendingArmies);
                cout << "Advance order sucess. Result: Capture failed. Remaining attacking armies sent back: " << attackingArmies << ". Remaining defending armies: " << defendingArmies << "." << endl;
            }
            else if (attackingArmies == 0 && defendingArmies == 0) {
                target->setArmies(0);
                cout << "Advance order sucess. Result: Capture failed. No remaining attacking or defending armies." << endl;
            }

            if (capture && !player->getDrawn()) {
                cout << "Player draws a card." << endl;
                deck->draw(player->getHand());
                cout << *player->getHand() << endl;
                player->setDrawn(true);
            }
        }
        setHasBeenExecuted(new bool(true));
    }
}

Bomb::Bomb(Player* player, territory* target) : Order(new string("bomb"), new string("The bomb order destroys half of the armies located on an opponent’s territory that is adjacent to one "
"of the current player's territories.")) {
    this->player = player;
    this->target = target;
}

bool Bomb::validate()
{
    if (player != target->getOwner() && !(target->getOwner()->isNegotiate(player)))
    {
        vector<territory*> territories = player->getTerritories();
        for (int i = 0; i < territories.size(); i++) {
            if (target->isAdjacentTerritory(territories.at(i))) {
                return true;
            }
        }
    }
    cout << "Invalid Bomb order." << endl;
    return false;
}

void Bomb::execute()
{
    if (validate())
    {
        Order::execute();

        target->setArmies(target->getArmies() / 2);
        cout << "Bomb order sucess. Target territory has " << target->getArmies() << " armies." << endl;
        setHasBeenExecuted(new bool(true));
    }
}

Blockade::Blockade(Player* player, Player* neutral, territory* target) : Order(new string("blockade"), new string("The blockade order triples the number of armies on one of the current player's territories "
"and make it a neutral territory.")) {
    this->player = player;
    this->neutral = neutral;
    this->target = target;
}

bool Blockade::validate()
{
    if (target->getOwner() == player)
    {
        return true;
    }
    cout << "Invalid Blockade order." << endl;
    return false;
}

void Blockade::execute()
{
    if (validate())
    {
        Order::execute();

        target->setOwner(neutral);
        player->removeTerritories(target);
        target->setArmies(target->getArmies() * 2);
        cout << "Blockade order sucess. Target territory is neutral and has " << target->getArmies() << " armies." << endl;
        setHasBeenExecuted(new bool(true));
    }
}

Airlift::Airlift(int numOfArmies, Player* player, territory* source, territory* target) : Order(new string("airlift"), new string("The airlift order advances some armies from one of the current player's territories to any "
    "another territory.")) {
    this->numOfArmies = numOfArmies;
    this->player = player;
    this->source = source;
    this->target = target;
}

bool Airlift::validate()
{
    if (player == source->getOwner() && player == target->getOwner())
    {
        return true;
    }
    cout << "Invalid Airlift order." << endl;
    return false;
}

void Airlift::execute()
{
    if (validate())
    {
        Order::execute();

        source->removeArmies(numOfArmies);
        target->addArmies(numOfArmies);
        cout << "Airlift order sucess. target territory now has " << target->getArmies() << " armies." << endl;
        setHasBeenExecuted(new bool(true));
    }
}

Negotiate::Negotiate(Player* player, Player* target) : Order(new string("negotiate"), new string("The negotiate order prevents attacks between the current player and another player until "
    "the end of the turn.")) {
    this->player = player;
    this->target = target;
}

bool Negotiate::validate()
{
    if (target != player) {
        return true;
    }
    cout << "Invalid Negotiate order." << endl;
    return false;
}

void Negotiate::execute()
{
    if (validate())
    {
        Order::execute();

        player->addNegotiate(target);
        target->addNegotiate(player);
        cout << "Negotiate order sucess. " << player->playerName << " and "  << target->playerName << " cannot attack eachother until next turn."<< endl;
        setHasBeenExecuted(new bool(true));
    }
}
