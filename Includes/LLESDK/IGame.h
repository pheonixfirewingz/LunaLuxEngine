#pragma once

#include "types.h"
class Game
{
private:
	LLEbool  usenative = LLEfalse;
    int8* name = nullptr;
    int16  win_width = 0 ,win_height = 0;
public:
	[[nodiscard]] inline LLEbool  getShouldUsNativeRenderer() const { return usenative;}
	[[nodiscard]] inline int8* getGameName() const { return name; };
	[[nodiscard]] inline int16 getWindowWidth() const {return win_width;}
	[[nodiscard]] inline int16 getWindowHeight() const {return win_height;}
	virtual void preBoot() {}
	virtual void GameBoot() {}
	virtual void GameMain() {}
protected:
	inline void setNativeMode(LLEbool inusenative) { usenative = inusenative;}
	inline void setGameName(int8* inname) { name = inname;}
	inline void setWindowSize(int16 w,int16 h) { win_width = w; win_height = h;}


};