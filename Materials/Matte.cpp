#include "Materials.hpp"

//Matte function memebrs
Matte::Matte() :
	Material{},
	mDiffuseBRDF{ std::make_shared<Lambertian>() }
{}

Matte::Matte(float const diffuseCoeff, Colour diffuseColour) :
	Matte{}
{
	setDiffuseReflection(diffuseCoeff);
	setDiffuseColour(diffuseColour);
}

void Matte::setDiffuseReflection(float const diffuseCoeff) {
	mDiffuseBRDF->setDiffuseReflection(diffuseCoeff);
}

void Matte::setDiffuseColour(Colour const& diffuseColour) {
	mDiffuseBRDF->setDiffuseColour(diffuseColour);
}

Colour Matte::shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	Colour result{ 0,0,0 };
	Colour ambient{ 0,0,0 };

	float ambientCoefficient = 0.13f;

	atlas::math::Ray<atlas::math::Vector> rayShade;
	ShadeRec srShade{};
	bool shadow = false;

	for (auto const& light : sr.world->lights) {
		Colour diffuse{ 0,0,0 };
		shadow = false;
		ambient = light->illumination(sr) * ambientCoefficient;

		//Shadows
		rayShade.d = light->getDirection(sr);
		rayShade.o = sr.hitPoint + sr.normal * 0.001f;

		for (auto obj : sr.world->scene) {
			if (obj->hit(rayShade, srShade) && light->distanceCheck(sr, srShade)) {
				shadow = true;
			}
		}
		if (!shadow) {
			//Diffuse
			float diffuseDot = std::max(0.0f, glm::dot(sr.normal, rayShade.d));
			diffuse = light->illumination(sr) * diffuseDot * mDiffuseBRDF->fn(sr, -ray.d, rayShade.d);
		}

		result += ambient + diffuse;
	}

	sr.shading = result;
	return result;
}