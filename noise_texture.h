#pragma once
#include "texture.h"
#include "perlin.h"
class noise_texture : public texture
{
public:
	noise_texture(){}
	virtual vec3 value(double u, double v, const vec3& p)const {
		return vec3(1, 1, 1)*noise.noise(p);
	}
	perlin noise;
};

