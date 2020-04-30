#pragma once

#include "Utilities.hpp"

class Material {
public:
	Material();
	virtual ~Material() = default;

	Material(float difCoeff, float specCoeff, float reflectCoeff);

	void setDiffuse(float difCoeff);

	void setSpecular(float specCoeff);

	void setReflective(float reflective);

	float getDiffuse(void);

	float getSpecular(void);

	float getReflective(void);

	virtual Colour shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);



private:
	float diffuseCoefficient;
	float specularCoefficient;
	float reflectionCoefficient;
};