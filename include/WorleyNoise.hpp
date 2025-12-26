#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class WorleyNoise {
public:
	explicit WorleyNoise(unsigned int seed = 0);

	float sample(float x, float y) const;

private:
	unsigned int m_seed;
	int m_gridSize;

	std::vector<sf::Vector2f> m_featurePoints;

	void generateFeaturePoints();
};