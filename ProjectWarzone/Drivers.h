#pragma once
#include "Orders.h"
#include "LoggingObserver.h"

void CommandProcessingDemo(Observer& obs);
void OrderExecutionDriverDemo(Observer& obs);
void runGameLoop(vector<Player*>* players, Deck* deck);
void startupPhaseDemo(Observer& obs);
void ObserverDriver(Observer& obs);
void PlayerStrategyDriver();
