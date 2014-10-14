#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

class StateManager
{
public:

	StateManager();

	enum GameState
	{
		MAIN_MENU,
		INSTRUCTIONS,
		LEVEL_ONE,
		LEVEL_TWO,
		LEVEL_THREE,
	};

	void SetState(GameState gameState);
	GameState GetState();

	~StateManager();

private:

	GameState gameState;

};
#endif