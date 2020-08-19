#pragma once

#include "types.h"
class Game
{
private:
	int8* name = nullptr;
	int16  win_width = 0, win_height = 0;
public:
	[[nodiscard]] inline int8* getGameName() const { return name; };
	[[nodiscard]] inline int16 getWindowWidth() const { return win_width; }
	[[nodiscard]] inline int16 getWindowHeight() const { return win_height; }
	virtual void preBoot() {}
	virtual void GameBoot() {}
	virtual void GameUpdate() {}
	virtual void GameLevel() {}
protected:
	inline void setGameName(int8* inname) { name = inname; }
	inline void setWindowSize(int16 w, int16 h) { win_width = w; win_height = h; }


};