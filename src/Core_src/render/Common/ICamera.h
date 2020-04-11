//
// Created by luket on 04/04/2020.
//

#ifndef LUNALUXENGINE_ICAMERA_H
#define LUNALUXENGINE_ICAMERA_H
#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>
namespace LunaLuxEngine
{
	class ICamera
	{
	private:
		glm::vec3 position, rotation;
		bool loack_to_2d_plane;
	public:
		virtual glm::mat4 getCurrentProjectionMatrix() = 0;

		inline void lockTo2D(bool lock)
		{
			loack_to_2d_plane = lock;
		}

		inline void setPos(float x, float y, float z)
		{
			position.x = x;
			position.y = y;
			if (loack_to_2d_plane)
				rotation.z = z;
			else
				rotation.z = 0.0f;
		}

		inline void incrementPos(float x, float y, float z)
		{
			position.x =+ x;
			position.y =+ y;
			if (loack_to_2d_plane)
				rotation.z =+ z;
		}

		inline void setRot(float x, float y, float z)
		{
			rotation.x = x;
			rotation.y = y;
			if (loack_to_2d_plane)
				rotation.z = z;
			else
				rotation.z = 0.0f;
		}

		inline void incrementRot(float x, float y, float z)
		{
			rotation.x =+ x;
			rotation.y =+ y;
			if (loack_to_2d_plane)
				rotation.z =+ z;
		}

		inline glm::vec3 getPos()
		{
			return position;
		}

		inline glm::vec3 getRot()
		{
			return rotation;
		}
	};
}
#endif //LUNALUXENGINE_ICAMERA_H
