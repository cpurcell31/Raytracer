#include "Sampler.hpp"

Sampler::Sampler(int nSamples, int nSets)
	: numSamples{ nSamples }, numSets{ nSets }, count{ 0 }, jump{ 0 }
{
	samples.reserve(numSets* numSamples);
	setupShuffledIndeces();
}

int Sampler::getNumSamples(void) const {
	return numSamples;
}

void Sampler::setupShuffledIndeces(void) {
	shuffledIndeces.reserve(numSamples * numSets);
	std::vector<int> indices;

	std::random_device d;
	std::mt19937 generator(d());

	for (int j = 0; j < numSamples; ++j)
	{
		indices.push_back(j);
	}

	for (int p = 0; p < numSets; ++p)
	{
		std::shuffle(indices.begin(), indices.end(), generator);

		for (int j = 0; j < numSamples; ++j)
		{
			shuffledIndeces.push_back(indices[j]);
		}
	}
}

void Sampler::mapSamplesToHemisphere(float const e) {

	hemisphereSamples.reserve(numSets * numSamples);
	std::size_t size = samples.size();
	for (std::size_t j = 0; j < size; ++j) {
		float cosPhi = glm::cos(2.0f * glm::pi<float>() * samples[j].x);
		float sinPhi = glm::sin(2.0f * glm::pi<float>() * samples[j].x);
		float cosTheta = pow((1.0f - samples[j].y), 1.0f / (e + 1.0f));
		float sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);
		float pu = sinTheta * cosPhi;
		float pv = sinTheta * sinPhi;
		float pw = cosTheta;
		hemisphereSamples.push_back(atlas::math::Point(pu, pv, pw));
	}
}

atlas::math::Point Sampler::sampleUnitSquare(void) {
	if (count % numSamples == 0)
	{
		atlas::math::Random<int> engine;
		jump = (engine.getRandomMax() % numSets) * numSamples;
	}

	return samples[jump + shuffledIndeces[jump + count++ % numSamples]];
}

atlas::math::Point Sampler::sampleHemisphere(void) {
	if (count % numSamples == 0)
	{
		atlas::math::Random<int> engine;
		jump = (engine.getRandomMax() % numSets) * numSamples;
	}

	return hemisphereSamples[jump + shuffledIndeces[jump + count++ % numSamples]];
}