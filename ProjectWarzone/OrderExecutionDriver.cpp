#include "Drivers.h"
using namespace std;

void OrderExecutionDriverDemo(Observer& obs) {
	cout << "==========================================\nINDIVIDUAL ORDER SHOWCASE\n==========================================" << endl;
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

	createRandomCards(deck, NULL, 10);

	cout << *deck << endl;

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

	p1->addTerritories(t0);
	p2->addTerritories(t2);
	p2->addTerritories(t3);
	p3->addTerritories(t5);
	neutral->addTerritories(t1);
	neutral->addTerritories(t4);

	//Deploy

	cout << "==========================================\nSimulating deploy order.\n==========================================" << endl;
	p1->addReinF(10);
	cout << "p1 tries to deploy 5 on t0, 5 on t2. There are currently no armies anywhere on the map." << endl;
	Order* o = new Deploy(5, p1, t0);
	Order* o2 = new Deploy(5, p1, t1);
	o->Attach(&obs);
	o2->Attach(&obs);
	cout << "trying to execute deploy 5 on t0" << endl;
	o->execute();
	cout << "trying to execute deploy 5 on t1" << endl;
	o2->execute();

	cout << "==========================================\nSimulating Advance Order\n==========================================" << endl;

	//Advance
	cout << "giving t1 8 armies to resist t0's 5 army advance." << endl;
	t1->addArmies(8);
	o = new Advance(5, p1, t0, t1, deck);
	o->execute();
	cout << "owner of t1 is " << t1->getOwner()->playerName << endl;

	cout << "giving t0 30 armies to capture t1." << endl;
	t0->addArmies(30);
	o = new Advance(30, p1, t0, t1, deck);
	o->execute();
	cout << "owner of t1 is " << t1->getOwner()->playerName << endl;

	cout << "attempting to advance onto t3 from t1 without borders" << endl;
	o = new Advance(5, p1, t1, t3, deck);
	o->execute();

	cout << "giving t0 to neutral and doing a second successfull advance order with 15 armies" << endl;
	t0->setOwner(neutral);
	neutral->addTerritories(t0);
	p1->removeTerritories(t0);
	o = new Advance(10, p1, t1, t0, deck);
	o->execute();

	cout << "==========================================\nSimulating Bomb\n==========================================" << endl;
	cout << "trying to bomb self" << endl;
	o = new Bomb(p1, t1);
	o->execute();
	cout << "giving t2 30 armies to bomb" << endl;
	t2->addArmies(30);
	o = new Bomb(p1, t2);
	o->execute();
	cout << "bombing again" << endl;
	o->execute();
	cout << "trying to bomb t3 (no borders)" << endl;
	o = new Bomb(p1, t3);
	o->execute();

	cout << "==========================================\nSimulating Blockade\n==========================================" << endl;
	cout << "trying to blockade t2 owned by p2 as p1" << endl;
	o = new Blockade(p1, neutral, t2);
	o->execute();
	cout << "Blockading t0 as p1" << endl;
	o = new Blockade(p1, neutral, t0);
	o->execute();

	cout << "==========================================\nSimulating Negotiate\n==========================================" << endl;
	cout << "trying to negotiate with self" << endl;
	o = new Negotiate(p1, p1);
	o->execute();
	cout << "p1 negotiate with p2" << endl;
	o = new Negotiate(p1, p2);
	o->execute();
	cout << "p1 trying to advance on t2, owned by p2" << endl;
	o = new Advance(15, p1, t1, t2, deck);
	o->execute();
	cout << "p2 trying to advance on t1, owned by p1" << endl;
	t2->addArmies(15);
	o = new Advance(15, p2, t2, t1, deck);
	o->execute();
	cout << "p1 advancing on t0, owned by neutral" << endl;
	o = new Advance(15, p1, t1, t0, deck);
	o->execute();
	 
}