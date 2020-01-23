#pragma once
class Game
{
private:

public:
	virtual void GameBoot() {};
	virtual void GameMain() {};
	char* getGameName() { return (char*)"LunaLuxEngine"; };

};