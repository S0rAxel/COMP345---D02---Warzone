#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>

HumanPlayer::HumanPlayer() 
{

}

HumanPlayer::HumanPlayer(const HumanPlayer& hPlayer) 
{
	this->player = hPlayer.player;
}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer& hPlayer) 
{
	// self-assignment guard
	if (this == &hPlayer)
		return *this;

	this->player = hPlayer.player;

	return *this;
}

void HumanPlayer::issueOrder()
{

}

void HumanPlayer::toAttack()
{

}

void HumanPlayer::toDefend()
{

}

AgressivePlayer::AgressivePlayer()
{

}

AgressivePlayer::AgressivePlayer(const AgressivePlayer& aPlayer)
{
	this->player = aPlayer.player;
}

AgressivePlayer& AgressivePlayer::operator=(const AgressivePlayer& aPlayer)
{
	// self-assignment guard
	if (this == &aPlayer)
		return *this;

	this->player = aPlayer.player;

	return *this;
}

void AgressivePlayer::issueOrder()
{

}

void AgressivePlayer::toAttack()
{

}

void AgressivePlayer::toDefend()
{

}

BenevolentPlayer::BenevolentPlayer()
{

}

BenevolentPlayer::BenevolentPlayer(const BenevolentPlayer& bPlayer)
{
	this->player = bPlayer.player;
}

BenevolentPlayer& BenevolentPlayer::operator=(const BenevolentPlayer& bPlayer)
{
	// self-assignment guard
	if (this == &bPlayer)
		return *this;

	this->player = bPlayer.player;

	return *this;
}

void BenevolentPlayer::issueOrder()
{

}

void BenevolentPlayer::toAttack()
{

}

void BenevolentPlayer::toDefend()
{

}

NeutralPlayer::NeutralPlayer()
{

}

NeutralPlayer::NeutralPlayer(const NeutralPlayer& nPlayer)
{
	this->player = nPlayer.player;
}

NeutralPlayer& NeutralPlayer::operator=(const NeutralPlayer& nPlayer)
{
	// self-assignment guard
	if (this == &nPlayer)
		return *this;

	this->player = nPlayer.player;

	return *this;
}

void NeutralPlayer::issueOrder()
{

}

void NeutralPlayer::toAttack()
{

}

void NeutralPlayer::toDefend()
{

}

CheaterPlayer::CheaterPlayer()
{

}

CheaterPlayer::CheaterPlayer(const CheaterPlayer& cPlayer)
{
	this->player = cPlayer.player;
}

CheaterPlayer& CheaterPlayer::operator=(const CheaterPlayer& cPlayer)
{
	// self-assignment guard
	if (this == &cPlayer)
		return *this;

	this->player = cPlayer.player;

	return *this;
}

void CheaterPlayer::issueOrder()
{

}

void CheaterPlayer::toAttack()
{

}

void CheaterPlayer::toDefend()
{

}