#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#if !defined(ONLINE_JUDGE)
#   include <gtest/gtest.h>
#endif

class CharCounter
{
// typedefs
public:
    struct occurrence_t
    {
        char character_;
        size_t count_;

        // disable default constructor
        occurrence_t() = delete;
        occurrence_t(char ch, size_t count)
            : character_(ch)
            , count_(count)
        { }
    };

// methods
public:
    std::map<char, size_t> const & map() const { return occurrences_; }
    std::vector<occurrence_t> to_vector() const
    {
        std::vector<occurrence_t> result;
        for (const auto & element : occurrences_)
        {
            result.push_back(occurrence_t{element.first, element.second});
        }
        return result;
    }

// operators
public:
    CharCounter & operator<<(const std::string & s)
    {
        for (char ch : s)
        {
            if (isalpha(ch))
            {
                occurrences_[static_cast<char>(toupper(ch))]++;
            }
        }
        return *this;
    }

// data
private:
    std::map<char, size_t> occurrences_;
};

void solve_uva_problem(std::istream & is, std::ostream & os)
{
    std::string line;
    std::getline(is, line);
    int n_lines = std::stoi(line);

    CharCounter char_counter;
    for (int i = 0; i < n_lines; ++i)
    {
        std::getline(is, line);
        char_counter << line;
    }

    auto occurrences = char_counter.to_vector();
    std::sort(occurrences.begin(),
              occurrences.end(),
              [] (const CharCounter::occurrence_t & lhs, const CharCounter::occurrence_t & rhs)
    {
        return (lhs.count_ == rhs.count_)
            ? (lhs.character_ < rhs.character_)
            : (lhs.count_ > rhs.count_);
    });

    for (const auto & occurrence : occurrences)
    {
        os << occurrence.character_ << " " << occurrence.count_ << std::endl;
    }
}

int main(int argc, char ** argv)
{
#if defined(ONLINE_JUDGE)
    solve_uva_problem(std::cin, std::cout);
#else
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}

#if !defined(ONLINE_JUDGE)
TEST(Cryptanalysis, test_1)
{
    std::istringstream iss("3\n"
                           "This is a test.\n"
                           "Count me 1 2 3 4 5.\n"
                           "Wow!!!! Is this question easy?\n");
    std::ostringstream oss;
    solve_uva_problem(iss, oss);

    EXPECT_EQ("S 7\n"
              "T 6\n"
              "I 5\n"
              "E 4\n"
              "O 3\n"
              "A 2\n"
              "H 2\n"
              "N 2\n"
              "U 2\n"
              "W 2\n"
              "C 1\n"
              "M 1\n"
              "Q 1\n"
              "Y 1\n", oss.str());
}
#endif
