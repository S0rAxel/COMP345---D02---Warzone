#include "Orders.h"
#include "OrdersDriver.h"
#include <iostream>

using std::cout;
using std::endl;

void OrderDriverDemo()
{
    Deploy deploy;
    Advance advance;
    Bomb bomb;
    Blockade blockade;
    Airlift airlift;
    Negotiate negotiate;

    OrdersList ordersList;

    ordersList.add(deploy);
    ordersList.add(advance);
    ordersList.add(bomb);
    ordersList.add(blockade);
    ordersList.add(airlift);
    ordersList.add(negotiate);

    cout << "Outputing a description of the orders: " << endl;
    cout << deploy << endl;
    cout << advance << endl;
    cout << bomb << endl;
    cout << blockade << endl;
    cout << airlift << endl;
    cout << negotiate << endl;
    cout << endl;

    deploy.validate();
    cout << endl;
    deploy.execute();
    cout << endl;
    cout << "After execution of the Deploy order: " << endl;
    cout << deploy << endl;
    cout << endl;
    cout << endl;

    cout << "Before moving an element in the list: " << endl;
    cout << ordersList << endl;
    ordersList.move(5, 0);
    cout << "After moving an element in the list: " << endl;
    cout << ordersList << endl;
    cout << endl;

    cout << "Before removing an element in the list: " << endl;
    cout << ordersList << endl;
    ordersList.remove(5);
    cout << "After removing an element in the list: " << endl;
    cout << ordersList << endl;
    cout << endl;
    cout << endl;

    cout << "Some other misc test stuff:" << endl;
    vector<Order>* test = new vector<Order>();
    test->push_back(deploy);
    test->push_back(advance);

    cout << "OrdersList parameter constructor:" << endl;
    OrdersList testList = OrdersList(test);
    cout << testList;
    cout << endl;

    cout << "OrdersList copy constructor:" << endl;
    OrdersList testList2 = OrdersList(ordersList);
    cout << testList2;
    cout << endl;
}
