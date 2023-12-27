#ifndef GAMEPROCESSOR_H
#define GAMEPROCESSOR_H

#include <vector>
#include "Globals.h"
#include "PlayerInstance.h"
using namespace std;

class BaseState;
class GameProcessor {
public:
	void InitializeGame();
	void HandleEvents();
	void ProcessEvents();
	void Render();
	void DeallocateResources();

	void ChangeState(BaseState *state);
	void PushState(BaseState *state);
	void PopState();

	PlayerInstance playerData;
private:
	std::vector<BaseState *> states;
};

#endif// GAMEPROCESSOR_H
