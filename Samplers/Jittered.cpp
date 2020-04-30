#include "Samplers.hpp"

Jittered::Jittered(int nSamples, int nSets) : Sampler{ nSamples, nSets }
{
	generateSamples();
}

void Jittered::generateSamples(void) {


	int n = static_cast<int>(glm::sqrt(static_cast<float>(numSamples)));

	atlas::math::Random<float> engine;

	for (int j = 0; j < numSets; ++j)
	{
		for (int p = 0; p < n; ++p)
		{
			for (int q = 0; q < n; ++q)
			{
				samples.push_back(atlas::math::Point{ (q + engine.getRandomRange(0.0f, 1.0f)) / n, (p + engine.getRandomRange(0.0f, 1.0f)) / n, 0.0f });
			}
		}
	}
}