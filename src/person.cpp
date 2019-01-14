# include "person.hpp"

namespace mr_fields
{
    Person::Person(enum sex sex, enum cleanliness cleanliness, enum food food, enum hobbies hobby)
     : sex(sex)
     , cleanliness(cleanliness)
     , food(food)
     , hobby(hobby)
    { }

    std::vector<Person> parse_from_file(std::istream& in)
    {
        std::vector<Person> res;
        int sex, cleanliness, food, hobbies;
        while (in >> sex >> cleanliness >> food >> hobbies)
        {
            res.emplace_back(static_cast<enum sex>(sex),
                             static_cast<enum cleanliness>(cleanliness),
                             static_cast<enum food>(food),
                             static_cast<enum hobbies>(hobbies));
        }
        return std::move(res);
    }
}