#ifndef LUNALLUXENGINE_BUFFER_UTIL
#define LUNALLUXENGINE_BUFFER_UTIL
struct COLOUR
{
	float  r;
	float  g;
	float  b;
	float  a;

	COLOUR()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}

	COLOUR(float d, float d1, float d2, float d3)
	{
		this->r = d;
		this->g = d1;
		this->b = d2;
		this->a = d3;
	}
};
struct VECTOR3
{
	float x, y, z;

	VECTOR3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	VECTOR3(float in_x, float in_y, float in_z)
	{
		this->x = in_x;
		this->y = in_y;
		this->z = in_z;
	}
};
struct VERTEX
{
	VECTOR3 vec;
	COLOUR color;

	VERTEX(){}

	VERTEX(VECTOR3 in_vec, COLOUR in_colour)
	{
		this->vec = in_vec;
		this->color = in_colour;
	}
};
#endif