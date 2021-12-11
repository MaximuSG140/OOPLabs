#include "HumanControl.h"

HumanControl::HumanControl(IGameView* game_view) :
	game_interface_(game_view)
{}

Instruction HumanControl::GetInstruction()
{
	return game_interface_->GetInstruction();
}
