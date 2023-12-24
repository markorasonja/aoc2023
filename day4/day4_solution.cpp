#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct card {
    set<int> winning_numbers;
    set<int> my_numbers;
};

int validateCard(card c) {
    int sum {0};
    for (auto number: c.winning_numbers) {
        if (c.my_numbers.find(number) != c.my_numbers.end()) sum == 0 ? sum += 1 : sum *= 2;
    }
    return sum;
}

int main(void)
{
    string line;
    ifstream input;
    input.open("input.txt");
    int sum {0};

    if (input.is_open()) {
        while(getline(input, line)) {
            card c;
            size_t start = line.find(":") + 2;
            size_t my_num_start = line.find("|") + 2;
            for (int i = start; i < my_num_start - 3; i++) {
                int n = atoi(&line.at(i));
                c.winning_numbers.insert(n);
                i += std::to_string(n).length();
            }
            for (int i = my_num_start; i < line.size(); i++) {
                int n = atoi(&line.at(i));
                c.my_numbers.insert(n);
                i += std::to_string(n).length();
            }

            sum += validateCard(c);
        }
    }

    cout << "Sum is: " << sum << endl;

    input.close();

    return 0;
}