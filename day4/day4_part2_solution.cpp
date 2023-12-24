#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

struct card {
    set<int> winning_numbers;
    set<int> my_numbers;
};

int validateCard(card c) {
    int sum {0};
    for (auto number: c.winning_numbers) {
        if (c.my_numbers.find(number) != c.my_numbers.end()) sum++;
    }
    return sum;
}

int main(void)
{
    string line;
    ifstream input;
    input.open("input.txt");
    int sum {0};
    int n_copies;
    vector<int> copies;

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
            n_copies = validateCard(c);
            
            int multiplier {1};
            sum += 1;

            if (!copies.empty()) {
                sum += copies.front();
                multiplier += copies.front();
                copies.erase(copies.begin());
            }

            for (int i = 0; i < n_copies; i++) {
                if (i >= copies.size()) {
                    copies.push_back(multiplier);
                } else {
                    copies.at(i) += multiplier;
                }
            }
        }
    }

    cout << "Sum is: " << sum << endl;

    input.close();

    return 0;
}
