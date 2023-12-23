#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct window {
    vector<char> prevRow;
    vector<char> currRow;
    vector<char> nextRow;
};

inline bool checkIfSymbol(char s) {
    if ((s >= 48 && s <= 57) ||
        (s >= 65 && s <= 90) ||
        (s >= 97 && s <= 122) ||
        s == 46
    ) return false;
    return true;
}

inline bool checkSurround(window w, int startIdx, int endIdx, int top, int bottom) {
    if (top) {
        if (startIdx > 0 && checkIfSymbol(w.prevRow.at(startIdx - 1))) return true;
        if (endIdx < w.prevRow.size() - 1 && checkIfSymbol(w.prevRow.at(endIdx + 1))) return true;
        /* check mid row */
        for (int i = startIdx - 1; i <= endIdx + 1; i++) {
            if (i >= 0 && i < w.currRow.size()) {
                if (checkIfSymbol(w.currRow.at(i))) return true;
            }
        }
    } else if (bottom) {
        if (startIdx > 0 && checkIfSymbol(w.nextRow.at(startIdx - 1))) return true;
        if (endIdx < w.nextRow.size() - 1 && checkIfSymbol(w.nextRow.at(endIdx + 1))) return true;
        /* check mid row */
        for (int i = startIdx - 1; i <= endIdx + 1; i++) {
            if (i >= 0 && i < w.currRow.size()) {
                if (checkIfSymbol(w.currRow.at(i))) return true;
            }
        }
    } else {
        if (startIdx > 0 && checkIfSymbol(w.currRow.at(startIdx - 1))) return true;
        if (endIdx < w.currRow.size() - 1 && checkIfSymbol(w.currRow.at(endIdx + 1))) return true;
        /* check top and bottom row */
        for (int i = startIdx - 1; i <= endIdx + 1; i++) {
            if (i >= 0 && i < w.prevRow.size()) {
                if (checkIfSymbol(w.prevRow.at(i))) return true;
            }
        }
        for (int i = startIdx - 1; i <= endIdx + 1; i++) {
            if (i >= 0 && i < w.nextRow.size()) {
                if (checkIfSymbol(w.nextRow.at(i))) return true;
            }
        }
    }
    return false;
}

int checkWindow(window w, int first = 0, int last = 0) {
    int sum {0};
    int currentNumer {0};
    int startIdx {-1};
    int endIdx {-1};
    vector<char> rowToCheck = w.currRow;
    if (first) rowToCheck = w.prevRow;
    if (last) rowToCheck = w.nextRow;
    for (int i = 0; i < rowToCheck.size(); i++) {
        if (isdigit(rowToCheck.at(i))) {
            currentNumer = atoi(&rowToCheck.at(i));
            startIdx = i;
            endIdx = startIdx + std::to_string(currentNumer).length() - 1;
            if (checkSurround(w, startIdx, endIdx, first, last)) sum += currentNumer;
            i += (endIdx - startIdx);
        }
    }
    return sum;
}

int main(void)
{
    string line;
    ifstream file;
    window window;
    file.open("input.txt");
    int sum {0};
    if (file.is_open()) {
        try {
            getline(file, line);
            std::copy(line.c_str(), line.c_str() + line.length(), back_inserter(window.prevRow));
            getline(file, line);
            std::copy(line.c_str(), line.c_str() + line.length(), back_inserter(window.currRow));
            getline(file, line);
            std::copy(line.c_str(), line.c_str() + line.length(), back_inserter(window.nextRow));
            sum += checkWindow(window, 1, 0);
            sum += checkWindow(window);

        } catch (std::ifstream::failure e) {
            cerr << "Exception: " << e.what() << endl;
        }
        while(getline(file, line)) {
            window.prevRow = window.currRow;
            window.currRow = window.nextRow;
            std::copy(line.c_str(), line.c_str() + line.length(), window.nextRow.begin());
            sum += checkWindow(window);
        }
        sum += checkWindow(window, 0, 1);
    }

    file.close();

    cout << "Sum is: " << sum << endl;
    return 0;
}