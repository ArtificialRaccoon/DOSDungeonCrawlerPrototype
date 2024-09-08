#include "BaseState.h"
#include "GameProcessor.h"

void BaseState::ChangeState(GameProcessor *game, BaseState *state) {
	UnloadResources();
	game->ChangeState(state);
}