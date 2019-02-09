# include "criterions.hpp"

namespace mr_fields
{
    static inline unsigned identity(int x)
    {
        return static_cast<unsigned>(x);
    }

    static inline void increment(int &c, const Person&, size_t)
    {
        c++;
    }

    template<typename counting_rule=decltype(increment),
             typename update_rule=decltype(identity)>
    unsigned counting_criterion(const state& s, const std::vector<Person>& persons,
                                const counting_rule& count=increment,
                                const update_rule& update=identity)
    {
        int c;
        unsigned energy = 0;
        for (size_t flat_idx = 0; flat_idx < s.flats.size(); flat_idx++)
        {
            c = 0;
            for (size_t person_idx : s.flats[flat_idx])
                count(c, persons[person_idx], flat_idx);
            energy += update(c);
        }
        return energy;
    }

    template<typename result_t>
    unsigned basic_criterion(const state& s,
                             const std::vector<Person>& persons,
                             const std::function<result_t(const Person&)>& getter)
    {
        result_t t;
        unsigned energy = 0;
        unsigned counts[3];
        unsigned *ptr = counts;
        for (auto flat : s.flats)
        {
            for (unsigned i = 0; i < 3; i++)
                counts[i] = 0;
            for (unsigned i = 0; i < 6; i++)
            {
                t = getter(persons[flat[i]]);
                counts[static_cast<unsigned>(t) - 1]++;
            }
            unsigned max = *std::max_element(ptr, ptr + 3);
            energy += 6 - max;
        }
        return energy;
    }

    unsigned parity_criterion(const state& s, const std::vector<Person>& persons)
    {
        auto count = [](int& c, const Person& p, size_t)
        {
            if (p.sex == man)
                c++;
            else if (p.sex == woman)
                c--;
        };
        return counting_criterion(s, persons, count, [](int a) {return std::abs(a);});
    }

    unsigned bathtube_criterion(const state& s, const std::vector<Person>& persons)
    {
        auto count = [](int& c, const Person& p, size_t flat_idx)
        {
            if (p.cleanliness == bath && flat_idx % 10 != 7)
                c++;
            else if (p.cleanliness != bath && flat_idx % 10 == 7)
                c++;
        };
        return counting_criterion(s, persons, count);
    }

    unsigned cleanliness_criterion(const state& s, const std::vector<Person>& persons)
    {
        std::function<enum cleanliness(const Person&)> g = [](const auto& p) { return p.cleanliness; };
        return basic_criterion(s, persons, g);
    }

    unsigned food_criterion(const state& s, const std::vector<Person>& persons)
    {
        std::function<enum food(const Person&)> g = [](const auto& p) { return p.food; };
        return basic_criterion(s, persons, g);
    }

    unsigned hobby_criterion(const state& s, const std::vector<Person>& persons)
    {
        std::function<enum hobbies(const Person&)> g = [](const auto& p) { return p.hobby; };
        return basic_criterion(s, persons, g);
    }

}
