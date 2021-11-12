#include "Cards.h"

using namespace std;
/// <summary>
/// Card Class implementation
/// </summary>
Card::Card() {
	cardType = EMPTY;
	hand = NULL;
	deck = NULL;
}

Card::Card(ctype type) {
	cardType = type;
	hand = NULL;
	deck = NULL;
}

Card::Card(ctype type, Hand* hand, Deck* deck) {
	cardType = type;
	this->hand = hand;
	this->deck = deck;
}

Card::Card(const Card& card) {
	cardType = card.cardType;
	hand = card.hand;
	deck = card.deck;
}

Card::ctype Card::getCardType() {
	return cardType;
}

void Card::setDeck(Deck* deck) {
	this->deck = deck;
}

void Card::setHand(Hand* hand) {
	this->hand = hand;
}

//Plays the card at index i in hand, then returns it to bottom of deck
void Card::play(int i) {
	if (hand != NULL) {
		hand->removeCard(i);
		deck->addCard(this);
	}
}

void Card::createRandomCards(Deck* deck, Hand* hand, int amount) {
	for (int i = 0; i < amount; i++) {
		deck->addCard(new Card((ctype)(rand() % 5), hand, deck));
	}
}

ostream& operator << (ostream& out, const Card& c) {
	switch (c.cardType)
	{
	case Card::ctype::bomb:
		out << "Card type: Bomb.";
		break;
	case Card::ctype::reinforcement:
		out << "Card type: Reinforcement.";
		break;
	case Card::ctype::airlift:
		out << "Card type: Airlift.";
		break;
	case Card::ctype::blockade:
		out << "Card type: Blockade.";
		break;
	case Card::ctype::diplomacy:
		out << "Card type: Diplomacy";
		break;
	}
	return out;
}

/// <summary>
/// Hand class implementation
/// </summary>

Hand::Hand() {

}

Hand::Hand(const Hand& hand) {
	cards = hand.cards;
}

vector<Card*> Hand::getCards() {
	return cards;
}

int Hand::size() {
	return cards.size();
}

void Hand::removeCard(int i) {
	cards[i]->setHand(NULL);
	cards.erase(cards.begin()+i);
}

void Hand::addCard(Card* card) {
	cards.push_back(card);
	card->setHand(this);
}

ostream& operator << (ostream& out, const Hand& h) {
	out << "Hand size: " << h.cards.size() << "." << endl;
	out << "Cards in hand: " << endl;
	for (int i = 0; i < h.cards.size(); i++) {
		out << "Card " << i << "=" << *(h.cards[i]) << endl;
	}
	return out;
}

/// <summary>
/// Deck class implementation
/// </summary>
Deck::Deck() {
}

Deck::Deck(const Deck &deck) {
	cards = deck.cards;
}

int Deck::size() {
	return cards.size();
}

vector<Card*> Deck::getCards() {
	return cards;
}

void Deck::removeCard(int i) {
	if (cards.size() == 0) {
		cout << "Deck is empty" << endl;
		return;
	}
	cards.erase(cards.begin() + i);
}

void Deck::addCard(Card* card) {
	cards.push_back(card);
	card->setDeck(this);
}

//Deck is a pile of card, and drawn card will be the top of the pile.
void Deck::draw(Hand* hand) {
	Card* drawnCard = new Card(*cards.front());
	this->removeCard(0);
	hand->addCard(drawnCard);
}

ostream& operator << (ostream& out, const Deck& d) {
	out << "Deck size: " << d.cards.size() << "." << endl;
	out << "Cards in deck: " << endl;
	for (int i = 0; i < d.cards.size(); i++) {
		out << "Card " << i << "=" << *(d.cards[i]) << endl;
	}
	return out;
}
