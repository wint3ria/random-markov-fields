#ifndef MARKOV_RANDOM_FIELDS_PERSON_HPP
#define MARKOV_RANDOM_FIELDS_PERSON_HPP

# include <vector>
# include <fstream>

namespace mr_fields
{
    enum sex {
        man=1,
        woman,
        hesitating,
    };

    enum cleanliness {
        none=1,
        shower,
        bath,
    };

    enum food
    {
        fat=1,
        vegan,
        classical,
    };

    enum hobbies
    {
        troll=1,
        loaf_abt,
        program,
    };


    struct Person
    {
        Person(enum sex sex, enum cleanliness cleanliness, enum food food, enum hobbies hobby);

        enum sex sex;
        enum cleanliness cleanliness;
        enum food food;
        enum hobbies hobby;
    };


    std::vector<Person> parse_from_file(std::istream& in);
}

#endif //MARKOV_RANDOM_FIELDS_PERSON_HPP
