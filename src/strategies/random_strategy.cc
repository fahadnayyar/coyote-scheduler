﻿// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include <iostream>
#include <thread>
#include "strategies/random_strategy.h"

namespace coyote
{
	RandomStrategy::RandomStrategy(Settings* settings) noexcept :
		iteration_seed(settings->random_seed()),
		generator(settings->random_seed())
	{
	}

	size_t RandomStrategy::next_operation(Operations& operations)
	{
		const size_t index = generator.next() % operations.size();
		return operations[index];
	}

	bool RandomStrategy::next_boolean()
	{
		return (generator.next() & 1) == 0;
	}

	size_t RandomStrategy::next_integer(size_t max_value)
	{
		return generator.next() % max_value;
	}

	void RandomStrategy::inject_sleep()
	{
		if (next_integer(100) == 0)
		{
			std::chrono::milliseconds time(generator.next() % 50);
			std::this_thread::sleep_for(time);
		}
	}

	size_t RandomStrategy::random_seed()
	{
		return iteration_seed;
	}

	void RandomStrategy::prepare_next_iteration()
	{
		iteration_seed += 1;
		generator.seed(iteration_seed);
	}
}
