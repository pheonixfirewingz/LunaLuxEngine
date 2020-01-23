//
// Created by luket on 22/01/2020.
//

#ifndef LUNALUXENGINE_ENTITY_H
#define LUNALUXENGINE_ENTITY_H


#include "../Common_Header.h"
#include <memory>
class IMesh
{
protected:
	virtual std::unique_ptr<glm::vec3[]>* getVaos() = 0;
	virtual std::unique_ptr<glm::vec3[]>* getVbos() = 0;
	virtual void createMesh();
};

class IEntity
{
protected:
	glm::vec3 pos,rot;
public:
	glm::vec3* getPos();
	glm::vec1* getPosX();
	glm::vec1* getPosY();
	glm::vec1* getPosZ();
	virtual IEntity* getEntity();
};
#endif //LUNALUXENGINE_ENTITY_H
