//
// Created by luket on 01/09/2020.
//
#include <GLM/gtc/matrix_transform.hpp>
#include <CrossWindow/WindowAPI.h>
#include "Camera.h"

void LunaLuxEngine::Camera::onBaseCreate()
{

}

void LunaLuxEngine::Camera::onUpdate()
{

}

void LunaLuxEngine::Camera::onDestroy()
{

}

glm::mat4 LunaLuxEngine::Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(45.0f),CWin.getAspectRatio(),m_near,m_far);
}

void LunaLuxEngine::Camera::setFieldForView(float in_far , float in_near)
{
    m_near = in_near;
    m_far = in_far;
}
