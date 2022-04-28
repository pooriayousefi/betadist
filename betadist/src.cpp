
#include <iostream>
#include <exception>
#include <random>
#include <functional>
#include <thread>
#include <concepts>

// anonymous space
namespace
{
	// ------------------------------------------ manual seeder
	namespace manual { decltype(auto) seeder(unsigned seed_arg) { return seed_arg; }; }

	// ------------------------------------------ automatic seeder (if hardware supports, true random seed will be generated.
	//                                            if not, pseudo-random seed will be generated)
	namespace automatic {
		decltype(auto) seeder()
		{
			std::random_device rng;
			if (rng.entropy())
				return rng();
			else
			{
				auto another_thread{ std::thread{} };
				std::hash<std::thread::id> hasher;
				auto another_thread_hashed_id{ hasher(another_thread.get_id()) };
				another_thread.join();
				auto this_thread_now{ std::chrono::system_clock::now() };
				auto this_thread_now_time_t{ std::chrono::system_clock::to_time_t(this_thread_now) };
				return static_cast<unsigned>(another_thread_hashed_id)
					^ static_cast<unsigned>(this_thread_now_time_t % 10'000'000'000L);
			}
		}
	}

	// ------------------------------------------ β namespace
	namespace β
	{
		// -------------------------------------- β distribution parameters assertion
		template<std::floating_point T>
		decltype(auto) parameter_assertion(T α, T β)
		{
			// parameters check (α > 0.0, β > 0.0)
			if (α <= (T)0)
				throw std::runtime_error("ERROR: α parameter (shape parameter) in β distribution function must be greater than zero.");
			if (β <= (T)0)
				throw std::runtime_error("ERROR: β parameter (shape parameter) in β distribution function must be greater than zero.");
		}

		// -------------------------------------- β simulator
		template<std::floating_point T>
		decltype(auto) simulator(T α, T β)
		{
			std::gamma_distribution<T> parametrized_γ_distribution_α(α, (T)1);
			std::gamma_distribution<T> parametrized_γ_distribution_β(β, (T)1);
			return [parametrized_γ_distribution_α, parametrized_γ_distribution_β](auto& random_number_generator_arg) mutable {
				auto pγdα{ parametrized_γ_distribution_α(random_number_generator_arg) };
				return pγdα / (pγdα + parametrized_γ_distribution_β(random_number_generator_arg));
			};
		}

		// -------------------------------------- β distributor
		template<std::floating_point T>
		decltype(auto) distributor(T α, T β, size_t number_of_simulations_arg, size_t seed_arg) {
			std::vector<T> samples(number_of_simulations_arg, (T)0);
			std::mt19937 rng{};
			rng.seed(seed_arg);
			auto rnd{ simulator(α, β) };
			for (auto& v : samples)
				v = rnd(rng);
			return samples;
		}
	}
}

// entry point
auto main()->int
{
	try
	{
		auto samples{ β::distributor(1.5f, 20.06f, 1'00, 111937) };
		for (const auto& s : samples)
			std::cout << s << std::endl;
		return EXIT_SUCCESS;
	}
	catch (const std::exception& xxx)
	{
		std::cerr << xxx.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "UNCAUGHT EXCEPTION DETECTED" << std::endl;
		return EXIT_FAILURE;
	}
}
