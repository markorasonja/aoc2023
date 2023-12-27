#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

struct Data {
    long number;
    long iteration;
};

bool operator==(const Data &d1, const Data &d2) {
    return d1.number == d2.number;
}

int main(void)
{
    string line;
    ifstream input;
    input.open("input.txt");
    long minLocation {std::numeric_limits<long>::max()};
    vector<Data> current;

    if (input.is_open()) {
        getline(input, line);
        for (int i = line.find(":") + 2; i < line.size(); i++) {
            Data d;
            long num = atol(&line.at(i));
            d.number = num;
            i += std::to_string(num).length() + 1;
            long iter = atol(&line.at(i));
            d.iteration = iter;
            i += std::to_string(iter).length();
            current.push_back(d);
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
            getline(input, line);
            bool moveNext {false};
            vector<Data> newMapped;
            while(!current.empty() && !moveNext) {
                vector<Data> oldCurrent = current;
                int size = current.size();
                for (int i = 0; i < size; i++) {
                    bool inserted {false};
                    Data curr = current.front(); current.erase(current.begin());
                    long c = curr.number;
                    long c_ = curr.number + curr.iteration;
                    for (int j = 0; j < source.size(); j++) {
                        long s = source.at(j);
                        long s_ = source.at(j) + ranges.at(j);
                        long d = destination.at(j);
                        if ((c >= s && c <= s_)|| (c_ >= s && c_ <= s_))
                        {
                            if (c >= s && c_ <= s_) {
                                Data new_d;
                                new_d.number = c + d - s;
                                new_d.iteration = curr.iteration;
                                newMapped.push_back(new_d);
                                inserted = true;
                                break;
                            } else if ((c <= s && c_ >= s) || (c <= s_ && c_ >= s_)) {
                                long outer = max((s - c), (c_ - s_));
                                long inside = min((c_ - s), (s_ - c));
                                if (outer > 0) {
                                    Data new_d;
                                    new_d.number = c;
                                    new_d.iteration = outer;
                                    current.push_back(new_d);
                                }
                                if (inside > 0) {
                                    Data new_d;
                                    if (c < s) {
                                        new_d.number = c + d - s + outer;
                                    } else {
                                        new_d.number = c + d - s;
                                    }
                                    new_d.iteration = inside;
                                    newMapped.push_back(new_d);
                                }
                                inserted = true;
                                break;
                            } else if (c <= s && c_ >= s_) {
                                long inside = s_ - s + 1;
                                long outer_first = s - c - 1;
                                long outer_second = c_ - s_;
                                if (inside > 0) {
                                    Data new_d;
                                    if (c < s) {
                                        new_d.number = c + d - s + outer_first;
                                    } else {
                                        new_d.number = c + d - s;
                                    }
                                    new_d.number = c + d - s;
                                    new_d.iteration = inside;
                                    newMapped.push_back(new_d);
                                }
                                if (outer_first > 0) {
                                    Data new_d;
                                    new_d.number = c;
                                    new_d.iteration = outer_first;
                                    current.push_back(new_d);
                                }
                                if (outer_second > 0) {
                                    Data new_d;
                                    new_d.number = c;
                                    new_d.iteration = outer_second;
                                    current.push_back(new_d);
                                }
                                inserted = true;
                                break;
                            }
                        }
                    }
                    if (!inserted) current.push_back(curr);
                }
                if (oldCurrent == current) moveNext = true;  
            }
            if (!newMapped.empty()) {
                std::copy(newMapped.begin(), newMapped.end(), back_inserter(current));
            }
        }
        for (int i = 0; i < current.size(); i++) {
            if (current.at(i).number < minLocation) minLocation = current.at(i).number;
        }
    }

    input.close();

    cout << "Minimum location is: " << minLocation << endl;

    return 0;
}
