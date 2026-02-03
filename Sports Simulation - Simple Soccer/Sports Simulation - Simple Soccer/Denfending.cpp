#include "Denfending.h"
#include "Params.h"

void Defending::Enter(SoccerTeam* team)
{
	//these define the home regions for this state of each of the players
	const int TeamSize = Prm.TeamSize;
	const int BlueRegions[TeamSize] = { 1,6,8,3,5 };
	const int RedRegions[TeamSize] = { 16,9,11,12,14 };

	//set up the player's home regions
	if (team->Color() == SoccerTeam::blue)
	{
		ChangePlayerHomeRegions(team, BlueRegions);
	}
	else
	{
		ChangePlayerRegions(team, RedRegions);
	}
}

void Defending::Execute(SoccerTeam* team)
{
}

void Defending::Exit(SoccerTeam* team)
{
}
