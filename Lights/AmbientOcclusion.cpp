#include "Lights.hpp"

//AmbientOcclusion member functions
AmbientOcclusion::AmbientOcclusion() : Light{ 1.0f, {0,0,0}, {1,1,1} }
{
	setAmbient({ 0.5f, 0.5f, 0.5f });
}

void AmbientOcclusion::setAmbient(Colour min) {
	minColour = min;
}

void AmbientOcclusion::computeUVW(ShadeRec const& sr) {
	w = sr.normal;
	v = glm::normalize(glm::cross(w, { 0.0075f,1.0f,0.0065f }));
	u = glm::cross(v, w);
}

atlas::math::Vector AmbientOcclusion::getDirection(ShadeRec const& sr) {
	atlas::math::Point samplePoint = sr.world->sampler->sampleHemisphere();
	return (samplePoint.x * u + samplePoint.y * v + samplePoint.z * w);
}

Colour AmbientOcclusion::illumination(ShadeRec const& sr) {
	computeUVW(sr);
	atlas::math::Ray<atlas::math::Vector> rayShade;
	rayShade.o = sr.hitPoint + sr.normal * 0.001f;
	rayShade.d = getDirection(sr);
	ShadeRec srShade{};
	bool shadow = false;

	for (auto obj : sr.world->scene) {
		if (obj->hit(rayShade, srShade)) {
			shadow = true;
		}
	}
	if (shadow) {
		return minColour * intensity * colour;
	}
	else {
		return intensity * colour;
	}
}
