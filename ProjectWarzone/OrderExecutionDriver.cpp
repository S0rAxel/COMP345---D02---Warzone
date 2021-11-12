#include "OrderExecutionDriver.h"
using namespace std;

void OrderExecutionDriverDemo() {
	territory* t0 = new territory(0, "t0", 0);
	territory* t1 = new territory(1, "t1", 0);
	territory* t2 = new territory(2, "t2", 0);
	territory* t3 = new territory(3, "t3", 1);
	territory* t4 = new territory(4, "t4", 0);
	territory* t5 = new territory(5, "t5", 0);

	// territories ordered as such (t5 | t0 | t1 | t2 | t4, t1 | t4)   (t3), () = continent, | = border

	t0->addBorders(t1);
	t1->addBorders(t0);
	t1->addBorders(t2);
	t1->addBorders(t4);
	t2->addBorders(t1);
	t2->addBorders(t4);
	t4->addBorders(t1);
	t4->addBorders(t2);
	t5->addBorders(t0);
	t0->addBorders(t5);

	Deck* deck = new Deck();

	Player* p1 = new Player("p1", new Hand());
	Player* p2 = new Player("p2", new Hand());
	Player* p3 = new Player("p3", new Hand());
	Player* neutral = new Player("neutral");

	//Assigning ownership to territories: p1: t0. p2: t2, t3. p3: t5, neutral: t1, t4

	t0->setOwner(p1);
	t1->setOwner(neutral);
	t2->setOwner(p2);
	t3->setOwner(p2);
	t4->setOwner(neutral);
	t5->setOwner(p3);

	//Deploy
	cout << "Simulating deploy order.\n==========================================" << endl;
	p1->addReinF(10);
	cout << "p1 tries to deploy 5 on t0, 5 on t2. There are currently no armies anywhere on the map." << endl;
	Order* o = new Deploy(5, p1, t0);
	Order* o2 = new Deploy(5, p1, t1);
	cout << "trying to execute deploy 5 on t0" << endl;
	o->execute();
	cout << "trying to execute deploy 5 on t1" << endl;
	o2->execute();

	cout << "t0 has " << t0->getArmies() << " armies." << endl << "==========================================\nSimulating Advance Order\n==========================================" << endl;

	//Advance
	cout << "giving t1 8 armies to resist t0's 5 army advance." << endl;

}