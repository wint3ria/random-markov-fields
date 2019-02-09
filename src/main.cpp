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

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "usage: " << argv[0] << " [filein] [fileout]" << std::endl;
        exit(1);
    }
    std::ifstream in(argv[1]);
    if (!in.good())
    {
        std::cerr << "Invalid input file: " << argv[1] << std::endl;
        exit(2);
    }
    std::ofstream out(argv[2]);
    if (!out.good())
    {
        std::cerr << "Invalid output file: " << argv[2] << std::endl;
        exit(3);
    }
    auto persons = mr_fields::parse_from_file(in);
    auto temperature_schedule = mr_fields::geometric_temperature();
    mr_fields::state s = mr_fields::simulated_annealing(persons, 1000000, 170, temperature_schedule);
    std::cout << "Final energy: " << mr_fields::default_energy_eval(s, persons) << std::endl;
    return 0;
}