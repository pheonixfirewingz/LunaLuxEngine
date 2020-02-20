#ifndef LUNALUXENGINE_LUNALUXENGINEPHYSICS_BOUDINGSPHERE_H
#define LUNALUXENGINE_LUNALUXENGINEPHYSICS_BOUDINGSPHERE_H
#include "../common/IntersectData.h"
namespace LunaLuxEngine::Physics
{
	class BSphere
	{
	private:
		const glm::vec3   sphere_center;
		const float			 sphere_radius;
	public:
		IntersectData intersectBoundingBox(cosnt BoundingSphere& other);
		BSphere(const glm:vec3& center,const float radius): sphere_center(center), sphere_radius(radius) {}
		inline const glm::vec3& getCenter() const { return sphere_center }
		inline float getRadius()						 const { return sphere_radius }
	};
}
#endif