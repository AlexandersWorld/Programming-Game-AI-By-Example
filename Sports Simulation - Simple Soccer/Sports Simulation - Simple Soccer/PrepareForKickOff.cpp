#include "PrepareForKickOff.h"
#include "SoccerTeam.h"
#include "Denfending.h"

void PrepareForKickOff::Enter(SoccerTeam* team)
{
	team->SetControllingPlayer(NULL);
	team->SetSupportingPlayer(NULL);
	team->SetReceiver(NULL);
	team->SetPlayerClosestBall(NULL);

	//send Msg_GoHome to each player.
	team->ReturnAllFieldPlayersToHome();
}

void PrepareForKickOff::Execute(SoccerTeam* team)
{
	//if both teams in position, start the game
	if (team->AllPlayersAtHome() && team->Opponents()->AllPlayersAtHome())
	{
		team->GetFSM()->ChangeState(Defending::Instance());
	}
}
