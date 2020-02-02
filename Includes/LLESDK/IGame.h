#pragma once

#include "types.h"

class Game
{
private:
    char* Name = nullptr;
    int16  Win_Width,Win_Height;
public:
	inline char* getGameName() const { return Name; };
	inline int16 getWindowWidth() const {return Win_Width;}
	inline int16 getWindowHeight() const {return Win_Height;}
	virtual void preBoot() {}
	virtual void GameBoot() {}
	virtual void GameMain() {}
protected:
	inline void setGameName(char* name) { Name = name;}
	inline void setWindowSize(int16 w,int16 h) { Win_Width = w; Win_Height = h;}


};