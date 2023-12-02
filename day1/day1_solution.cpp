#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <vector>

using namespace std;

vector<string> stringNumbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

unsigned long findPosition(string s, int order, int *number) {
    unsigned long minIdx = INT32_MAX;
    unsigned long maxIdx = 0;
    int i = 0;
    for (vector<string>::iterator it = stringNumbers.begin(); it != stringNumbers.end(); it++) {
        i++;
        size_t idx;
        if (order == 1) {
            idx = s.rfind(*it);
        }
        else {
            idx = s.find(*it, 0);
        }
        if (idx == string::npos) continue;
        if (order == 1) {
            if (idx > maxIdx) {
                maxIdx = idx;
                *number = i;
            }
        }
        else 
        {   
            if (idx < minIdx) {
                minIdx = idx;
                *number = i;
            }
        }
    }
    if (order == 1) return maxIdx;
    else return minIdx;
}

int main(void)
{
    string line;
    ifstream input;
    input.open("puzzleInput.txt");
    int sum {0};

    if (input.is_open()) {
        while (std::getline(input, line)) {
            int first = -1;
            int last = -1;
            unsigned long minIdxString = findPosition(line, 0, &first);
            unsigned long maxIdxString = findPosition(line, 1, &last);
            unsigned long idxStart {0}; unsigned long idxEnd {line.length() - 1};
            bool foundFirst = false; bool foundLast = false;
            while (!foundFirst || !foundLast)
            {
                if (!foundFirst && idxStart <= minIdxString && isdigit(line.at(idxStart))) {
                    first = line.at(idxStart) - '0';
                    foundFirst = true;
                }
                if (!foundLast && idxEnd >= maxIdxString && isdigit(line.at(idxEnd))) {
                    last = line.at(idxEnd) - '0';
                    foundLast = true;
                }
                if (idxStart > minIdxString) foundFirst = true;
                if (idxEnd < maxIdxString) foundLast = true;
                idxStart++; idxEnd--;
            }   
            sum += first * 10 + last;
        }
        input.close();
    }

    cout << sum << endl;

    return 0;
}