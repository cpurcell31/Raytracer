#pragma once

#include "Utilities.hpp"

class Camera {
public:
	Camera();
	virtual ~Camera() = default;

	void setEye(atlas::math::Point const& e);

	void setLookAt(atlas::math::Point const& look);

	void setUpVector(atlas::math::Vector const& UP);

	void setD(float const& dist);

	void computeUVW(void);

	atlas::math::Point getEye(void);

	atlas::math::Vector getU(void);

	atlas::math::Vector getV(void);

	virtual atlas::math::Vector convertToVS(atlas::math::Vector const& p);

	std::vector<Colour> renderScene(std::shared_ptr<World>& world, std::size_t startIndex, std::size_t endIndex);

protected:
	atlas::math::Vector u;
	atlas::math::Vector v;
	atlas::math::Vector w;
	atlas::math::Point eye;
	atlas::math::Point l;
	atlas::math::Vector up;
	float d;

};