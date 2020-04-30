#include "Material.hpp"

//Material member functions
Material::Material() : diffuseCoefficient{ 0 }, specularCoefficient{ 0 }, reflectionCoefficient{ 0 }
{}

Material::Material(float const difCoeff, float const specCoeff, float const reflectCoeff) :
	diffuseCoefficient{ difCoeff }, specularCoefficient{ specCoeff }, reflectionCoefficient{ reflectCoeff }
{}

void Material::setDiffuse(float difCoeff) {
	diffuseCoefficient = difCoeff;
}

void Material::setSpecular(float specCoeff) {
	specularCoefficient = specCoeff;
}

void Material::setReflective(float reflective) {
	reflectionCoefficient = reflective;
}

float Material::getDiffuse(void) {
	return diffuseCoefficient;
}

float Material::getSpecular(void) {
	return specularCoefficient;
}

float Material::getReflective(void) {
	return reflectionCoefficient;
}