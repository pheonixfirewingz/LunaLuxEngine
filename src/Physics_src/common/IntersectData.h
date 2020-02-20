#ifndef LUNALUXENGINE_LUNALUXENGINEPHYSICS_INTERSECTDATA_H
#define LUNALUXENGINE_LUNALUXENGINEPHYSICS_INTERSECTDATA_H
#include <GLM/glm.hpp>

namespace LunaLuxEngine::Physics
{
	class IntersectData
	{
	private:
		const bool  data_doseIntersect;
		const float	data_distance;
	public:
		IntersectData(const bool  doseIntersect, const float distance) : data_doseIntersect(doseIntersect), data_distance(distance) {}
		inline bool getDoseIntersect() const { return data_doseIntersect }
		inline float getDistance()			 const { return data_distance }
	};
}
#endif