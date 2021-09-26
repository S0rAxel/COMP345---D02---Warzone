#include "Player.h"

list<int> Player::toDefend() {
	cout << playerName << " is defending" << endl;
}

list<int> Player::toAttack() {
	cout << playerName << " is attacking" << endl;
}

void Player::issueOrder() {
	cout << playerName << " is issuing order" << endl;
}

void Order::executeOrder() {
	cout << " Order executing: " << order << endl;
}