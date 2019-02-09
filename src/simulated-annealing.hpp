#ifndef MARKOV_RANDOM_FIELDS_SIMULATED_ANNEALING_HPP
#define MARKOV_RANDOM_FIELDS_SIMULATED_ANNEALING_HPP

# include <vector>
# include <cstdlib>
# include <ctime>
# include <math.h>
# include <limits>

# include "person.hpp"
# include "state.hpp"
# include "criterions.hpp"

namespace mr_fields
{
    template<typename first_criterion, typename... criterions>
    inline unsigned compute_energy(const state& s, const std::vector<Person>& persons, first_criterion c, criterions... cts)
    {
        return c(s, persons) + compute_energy(s, persons, cts...);
    }
    inline unsigned compute_energy(const state&, const std::vector<Person>&) { return 0; }

    inline unsigned default_energy_eval(const state& s, const std::vector<Person>& persons)
    {
        return compute_energy(s, persons,
                              parity_criterion,
                              cleanliness_criterion,
                              food_criterion,
                              hobby_criterion,
                              bathtube_criterion);
    }

    double constant_temperature(double)
    {
        return 1;
    }

    struct geometric_temperature
    {
        double operator () (double)
        {
            invocations++;
            return std::pow(lambda, invocations) * start_temperature;
        }

        double lambda=0.99;
        double start_temperature=5;
        size_t invocations=0;
    };

    double exponential_law(unsigned delta_e, double temperature)
    {
        return exp(-(double)delta_e / temperature);
    }

    using temperature_schedule_t = decltype(constant_temperature);
    using acceptance_law_t = decltype(exponential_law);
    using energy_eval_t = decltype(default_energy_eval);

    template<typename temperature_schedule=temperature_schedule_t,
             typename acceptance_law=acceptance_law_t,
             typename energy_eval=energy_eval_t>
    state simulated_annealing(const std::vector<Person>& persons,
                              size_t k_max=std::numeric_limits<size_t>::max(), unsigned energy_min=0,
                              temperature_schedule temp=constant_temperature,
                              acceptance_law P=exponential_law,
                              energy_eval E=default_energy_eval)
    {
        state s = random_state(persons);
        unsigned energy = E(s, persons);
        state opt = s;
        unsigned opt_energy = energy;

        for (size_t k = 0; k < k_max && energy > energy_min; k++)
        {
            state new_s = s.compute_neighbor();
            unsigned new_energy = E(new_s, persons);
            if (new_energy < energy || ((double)rand()) / RAND_MAX < P(new_energy - energy, temp((double)k / k_max)))
            {
                s = new_s;
                energy = new_energy;
            }
            if (energy < opt_energy)
            {
                opt = s;
                opt_energy = energy;
                std::cout << opt_energy << std::endl;
            }
        }
        return std::move(opt);
    }

    struct rand_init {
        rand_init() { std::srand(std::time(0)); }
    };
    extern rand_init ri_;
}

#endif //MARKOV_RANDOM_FIELDS_SIMULATED_ANNEALING_HPP
