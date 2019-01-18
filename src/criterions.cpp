# include "criterions.hpp"

namespace mr_fields
{
    unsigned parity_criterion(const state& s, const std::vector<Person>& persons)
    {
        int c;
        unsigned energy = 0;
        for (auto flat : s.flats)
        {
            c = 0;
            for (size_t person_idx : flat)
            {
                if (persons[person_idx].sex == man)
                    c++;
                else if (persons[person_idx].sex == woman)
                    c--;
            }
            energy += std::abs(c);
        }
        return energy;
    }
}
