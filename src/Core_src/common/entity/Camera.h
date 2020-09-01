//
// Created by luket on 01/09/2020.
//

#ifndef LUNALUXENGINE_CAMERA_H
#define LUNALUXENGINE_CAMERA_H
#include "IEntity.h"
#include <GLM/glm.hpp>
namespace LunaLuxEngine
{
    class Camera : public IEntity
    {
    private:
        float m_near = 0.0f, m_far = 0.0f;
    public:
        void onBaseCreate() override;

        void onUpdate() override;

        void onDestroy() override;

        glm::mat4 getProjectionMatrix();

        void setFieldForView(float = 0.1f, float = 100.f);
    };
}
#endif //LUNALUXENGINE_CAMERA_H
