#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>

/// @brief The Random class.
class Random
{
public:
	/// @brief Constructor
	Random();
	static float getRandomBetween(float min, float max)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

		return (float)dist6(rng);
	};

	static float getRandomFloatBetween(float min, float max) 
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_real_distribution<float> dist6(min, max);
		return (float)dist6(rng);
	}

private:

};

#endif /* RANDOM_H */
#pragma once
