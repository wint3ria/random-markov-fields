# include "state.hpp"

namespace mr_fields
{
    state::state(size_t nb_flats)
            : flats(nb_flats, std::vector<size_t>())
    { }

    state state::compute_neighbor()
    {
        state res = *this;
        size_t a = rand() % flats.size();
        size_t b = rand() % 6;
        size_t c = rand() % flats.size();
        size_t d = rand() % 6;
        size_t tmp = res.flats[a][b];
        res.flats[a][b] = res.flats[c][d];
        res.flats[c][d] = tmp;
        return std::move(res);
    }

    state random_state(const std::vector<Person>& persons)
    {

        std::vector<size_t> positions(persons.size());
        for (size_t i = 0; i < persons.size(); i++)
            positions[i] = i / 6;
        std::random_shuffle(positions.begin(), positions.end());
        state s(persons.size() / 6);
        for (size_t j = 0; j < positions.size(); j++)
            s.flats[positions[j]].push_back(j);
        return std::move(s);
    }

}