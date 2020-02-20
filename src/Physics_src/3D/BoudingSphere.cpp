#include "BoudingSphere.h"
#include <GLM/geometric.hpp>

IntersectData LunaLuxEngine::Physics::BSphere::intersectBoundingBox(cosnt BoundingSphere& other)
{
	float radiusDistance = sphere_radius + other.GetRadius();
	float centerDistance = glm::length(other.GetCenter() - sphere_center);
	float distance = centerDistance - radiusDistance;

	return IntersectData(centerDistance < radiusDistance, distance);
}