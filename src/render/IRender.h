#pragma once

#include "../Common_Header.h"
#include "../common/Entity.h"
#include <vector>
class IRender
{
protected:
	std::vector<IEntity> entitys;
public:
	void initRender();
	void prepRender();
	void fireRender();
	void destroyRender();
};

