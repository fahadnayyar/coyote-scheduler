// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "test.h"
#include "coyote/strategies/random_strategy.h"

using namespace coyote;

int main()
{
	std::cout << "[test] started." << std::endl;
	auto start_time = std::chrono::steady_clock::now();

	size_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
#ifdef COYOTE_DEBUG_LOG
	std::cout << "[test] seed: " << seed << std::endl;
#endif // !COYOTE_DEBUG_LOG

	auto strategy = std::make_unique<RandomStrategy>(seed);
	auto replay_strategy = std::make_unique<RandomStrategy>(seed);

	const int num_ops = 20;
	const int num_bool_choices = 100;
	const int num_int_choices = 100;

	std::array<int, num_ops> op_choices;
	std::array<bool, num_bool_choices> bool_choices;
	std::array<int, num_int_choices> int_choices;

	Operations ops;
	for (int i = 0; i < num_ops; i++)
	{
		ops.insert(i);
	}

	for (int i = 0; i < num_ops; i++)
	{
		size_t op = strategy->next_operation(ops);
#ifdef COYOTE_DEBUG_LOG
		std::cout << "[test] random op choice: " << op << std::endl;
#endif // !COYOTE_DEBUG_LOG
		op_choices[i] = op;
	}

	for (int i = 0; i < num_bool_choices; i++)
	{
		bool value = strategy->next_boolean();
#ifdef COYOTE_DEBUG_LOG
		std::cout << "[test] random bool choice: " << value << std::endl;
#endif // !COYOTE_DEBUG_LOG
		bool_choices[i] = value;
	}

	for (int i = 0; i < num_int_choices; i++)
	{
		size_t value = strategy->next_integer(10);
#ifdef COYOTE_DEBUG_LOG
		std::cout << "[test] random int choice: " << value << std::endl;
#endif // !COYOTE_DEBUG_LOG
		int_choices[i] = value;
	}

	for (int i = 0; i < num_ops; i++)
	{
		size_t op = replay_strategy->next_operation(ops);
#ifdef COYOTE_DEBUG_LOG
		std::cout << "[test] replaying op choice: " << op << std::endl;
#endif // !COYOTE_DEBUG_LOG
		assert(op_choices[i] == op, "unexpected op");
	}

	for (int i = 0; i < num_bool_choices; i++)
	{
		bool value = replay_strategy->next_boolean();
#ifdef COYOTE_DEBUG_LOG
		std::cout << "[test] replaying bool choice: " << value << std::endl;
#endif // !COYOTE_DEBUG_LOG
		assert(bool_choices[i] == value, "unexpected bool choice");
	}

	for (int i = 0; i < num_int_choices; i++)
	{
		size_t value = replay_strategy->next_integer(10);
#ifdef COYOTE_DEBUG_LOG
		std::cout << "[test] replaying int choice: " << value << std::endl;
#endif // !COYOTE_DEBUG_LOG
		assert(int_choices[i] == value, "unexpected int choice");
	}

	std::cout << "[test] done in " << total_time(start_time) << "ms." << std::endl;
	return 0;
}
