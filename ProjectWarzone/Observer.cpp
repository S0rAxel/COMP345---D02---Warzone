#include "Drivers.h"
#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include "Orders.h"

void ObserverDriver(Observer& obs)
{
	CommandProcessor* cmdP = new CommandProcessor();
	Command* cmd = new Command("Command for Observer");
	OrdersList* orders = new OrdersList();
	cmdP->Attach(&obs);
	cmd->Attach(&obs);
	orders->Attach(&obs);

	cmdP->saveCommand(cmd);
	cmd->saveEffect("Command's Effect Saved");
	orders->add(new Negotiate(new Player("player 1", nullptr), new Player("Player 2", nullptr)));
}