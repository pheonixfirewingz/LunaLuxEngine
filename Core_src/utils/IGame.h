#pragma once
class Game
{
private:
    char* Name = nullptr;
public:
    virtual void preBoot() {};
	virtual void GameBoot() {};
	virtual void GameMain() {};
	inline char* getGameName() const { return Name; };
	inline void setGameName(char* name) { Name = name;};

};