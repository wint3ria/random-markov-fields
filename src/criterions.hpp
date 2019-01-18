#ifndef MARKOV_RANDOM_FIELDS_CRITERIONS_HPP
#define MARKOV_RANDOM_FIELDS_CRITERIONS_HPP

# include "person.hpp"
# include "state.hpp"

namespace mr_fields
{
    unsigned parity_criterion(const state& s, const std::vector<Person>& persons);
}

#endif //MARKOV_RANDOM_FIELDS_CRITERIONS_HPP
