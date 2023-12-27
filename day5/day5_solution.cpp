#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main(void)
{
    string line;
    ifstream input;
    input.open("input.txt");
    long minLocation {std::numeric_limits<long>::max()};
    vector<long> current;

    if (input.is_open()) {
        getline(input, line);
        for (int i = line.find(":") + 2; i < line.size(); i++) {
            long num = atol(&line.at(i));
            current.push_back(num);
            i += std::to_string(num).length();
        }

        getline(input, line); getline(input, line);

        for (int it = 0; it < 7; it++) {
            vector<long> source;
            vector<long> destination;
            vector<long> ranges;
            while(getline(input, line) && line != "") {
                int offset {0};
                long n = atol(&line.at(offset));
                destination.push_back(n);
                offset += std::to_string(n).length() + 1;
                n = atol(&line.at(offset));
                source.push_back(n);
                offset += std::to_string(n).length() + 1;
                n = atol(&line.at(offset));
                ranges.push_back(n);
            }
            int size = current.size();
            for (int i = 0; i < size; i++) {
                bool inserted = false;
                long c = current.front(); current.erase(current.begin());
                for (int j = 0; j < source.size(); j++) {
                    if ((c >= source.at(j)) && (c <= source.at(j) + ranges.at(j))) {
                        current.push_back(destination.at(j) - source.at(j) + c);
                        inserted = true;
                        break;
                    }
                }
                if (!inserted) current.push_back(c);
            }
        }
        for (int i = 0; i < current.size(); i++) {
            if (minLocation > current.at(i)) minLocation = current.at(i);
        }
    }

    input.close();

    cout << "Minimum location is: " << minLocation << endl;

    return 0;
}

/*
    Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
    Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
    Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
    Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.
*/