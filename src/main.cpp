# include <fstream>

# include "person.hpp"

int main()
{
    std::ifstream in("./tests/60a.txt");
    mr_fields::parse_from_file(in);
    return 0;
}