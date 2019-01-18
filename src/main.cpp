# include <fstream>
# include <iostream>

# include "simulated-annealing.hpp"
# include "criterions.hpp"

std::ostream& operator <<(std::ostream& o, const mr_fields::Person& p)
{
    o << p.sex << ' ' << p.cleanliness << ' ' << p.food << ' ' << p.hobby;
    return o;
}

mr_fields::rand_init ri_;

int main()
{
    std::ifstream in("./tests/600a.txt");
    auto persons = mr_fields::parse_from_file(in);
    mr_fields::state s = mr_fields::simulated_annealing(persons, 1000000, 40);
    std::cout << "Final energy: " << mr_fields::compute_energy(s, persons, mr_fields::parity_criterion) << std::endl;
    return 0;
}