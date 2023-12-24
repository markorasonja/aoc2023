#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

inline int checkSurround(window w, int idx, int top, int bottom) {
    int gearRatio {1};
    int numCnt {0};
    int leftTopEnd {-1};
    int leftBotEnd {-1};
    vector<char> rowToCheck = w.currRow;
    if (top) rowToCheck = w.nextRow;
    if (bottom) rowToCheck = w.prevRow;
    if (idx > 0 && isdigit(rowToCheck.at(idx - 1))) {
        int tmpIdx = idx;
        while ((tmpIdx - 1) >= 0 && isdigit(rowToCheck.at(tmpIdx - 1))) tmpIdx--;
        gearRatio *= atoi(&rowToCheck.at(tmpIdx));
        numCnt++;
    }
    if (idx < rowToCheck.size() - 1 && isdigit(rowToCheck.at(idx + 1))) {
        gearRatio *= atoi(&rowToCheck.at(idx + 1));
        numCnt++;
    }
    if (top || bottom) {
        if (idx > 0 && isdigit(w.currRow.at(idx - 1))) {
            int tmpIdx = idx;
            while ((tmpIdx - 1) >= 0 && isdigit(w.currRow.at(tmpIdx - 1))) tmpIdx--;
            gearRatio *= atoi(&w.currRow.at(tmpIdx));
            leftTopEnd = tmpIdx + std::to_string(gearRatio).length() - 1;
            if (numCnt < 2) numCnt++;
            else return 0;
        }
        if (idx < w.currRow.size() - 1 && isdigit(w.currRow.at(idx + 1)) && leftTopEnd < idx + 1) {
            int tmpIdx = idx + 1;
            while ((tmpIdx - 1) >= 0 && isdigit(w.currRow.at(tmpIdx - 1))) tmpIdx--;
            gearRatio *= atoi(&w.currRow.at(tmpIdx));
            leftTopEnd = -1;
            if (numCnt < 2) numCnt++;
            else return 0;
        }
    } else {
        if (idx > 0 && isdigit(w.prevRow.at(idx - 1))) {
            int tmpIdx = idx;
            while ((tmpIdx - 1) >= 0 && isdigit(w.prevRow.at(tmpIdx - 1))) tmpIdx--;
            gearRatio *= stoi(&w.prevRow.at(tmpIdx));
            leftTopEnd = tmpIdx + std::to_string(gearRatio).length() - 1;
            if (numCnt < 2) numCnt++;
            else return 0;
        }
        if (idx < w.prevRow.size() - 1 && isdigit(w.prevRow.at(idx + 1)) && leftTopEnd < idx + 1) {
            int tmpIdx = idx + 1;
            while ((tmpIdx - 1) >= 0 && isdigit(w.prevRow.at(tmpIdx - 1))) tmpIdx--;
            gearRatio *= atoi(&w.prevRow.at(tmpIdx));
            leftTopEnd = -1;
            if (numCnt < 2) numCnt++;
            else return 0;
        }
        if (idx > 0 && isdigit(w.nextRow.at(idx - 1))) {
            int tmpIdx = idx;
            while ((tmpIdx - 1) >= 0 && isdigit(w.nextRow.at(tmpIdx - 1))) tmpIdx--;
            gearRatio *= atoi(&w.nextRow.at(tmpIdx));
            leftBotEnd = tmpIdx + std::to_string(gearRatio).length() - 1;
            if (numCnt < 2) numCnt++;
            else return 0;
        }
        if (idx < w.nextRow.size() - 1 && isdigit(w.nextRow.at(idx + 1)) && leftBotEnd < idx + 1) {
            int tmpIdx = idx + 1;
            while ((tmpIdx - 1) >= 0 && isdigit(w.nextRow.at(tmpIdx - 1))) tmpIdx--;
            gearRatio *= atoi(&w.nextRow.at(tmpIdx));
            if (numCnt < 2) numCnt++;
            else return 0;
        }
    }
    if (numCnt < 2) return 0;
    return gearRatio;
}

int checkWindow(window w, int first = 0, int last = 0) {
    int sum {0};
    vector<char> rowToCheck = w.currRow;
    if (first) rowToCheck = w.prevRow;
    if (last) rowToCheck = w.nextRow;
    for (int i = 0; i < rowToCheck.size(); i++) {
        if (rowToCheck.at(i) == '*') sum += checkSurround(w, i, first, last);
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
