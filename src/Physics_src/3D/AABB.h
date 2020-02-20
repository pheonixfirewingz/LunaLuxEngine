#ifndef LUNALUXENGINE_PHYSICS_AABB_H
#define LUNALUXENGINE_PHYSICS_AABB_H
#include "intersectData.h"
namespace LunaLuxEngine::Physics
{
	class AABB
	{
	private:
		const glm::vec3 aabb_minExtents, aabb_maxExtents;
	public:
		AABB(const glm::vec3& minExtents, const glm::vec3f& maxExtents) : aabb_minExtents(minExtents), aabb_maxExtents(maxExtents) {}
		IntersectData IntersectAABB(const AABB& other) const;
		inline const glm::vec3& GetMinExtents() const { return aabb_minExtents; }
		inline const glm::vec3& GetMaxExtents() const { return aabb_maxExtents; }
	};
}
#endif