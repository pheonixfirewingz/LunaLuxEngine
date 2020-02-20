#include "AABB.h"

IntersectData LunaLuxEngine::Physics::AABB::IntersectAABB(const AABB& other) const
{
	glm::vec3 distances1 = other.GetMinExtents() - m_maxExtents;
	glm::vec3 distances2 = m_minExtents - other.GetMaxExtents();

	glm::vec3 distances = glm::vec3(glm::max(distances2));

	float maxDistance = glm::max(distances);

	return IntersectData(maxDistance < 0, maxDistance);
}