#ifndef MARKOV_RANDOM_FIELDS_STATE_HPP
#define MARKOV_RANDOM_FIELDS_STATE_HPP

# include <vector>
# include <algorithm>

# include "person.hpp"

namespace mr_fields
{
    struct state {
        state(size_t nb_flats);

        state compute_neighbor();

        std::vector<std::vector<size_t>> flats;
    };

    state random_state(const std::vector<Person>& persons);

}

#endif //MARKOV_RANDOM_FIELDS_STATE_HPP
