#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void validateRound(string round, map<string, int> &colorMaxMap) {
    size_t i {0};
    size_t startIdx = round.find(",");
    while (startIdx != string::npos) {
        size_t delimiter = round.find(" ", i);
        int num = stoi(round.substr(i, delimiter - i));
        string color = round.substr(delimiter + 1, startIdx - delimiter - 1);
        if (colorMaxMap[color] < num) colorMaxMap[color] = num;
        i = startIdx + 2;
        startIdx = round.find(",", i);
    }
    
    //last 
    size_t delimiter = round.find(" ", i);
    int num = stoi(round.substr(i, delimiter - i));
    string color = round.substr(delimiter + 1);
    if (colorMaxMap[color] < num) colorMaxMap[color] = num;
    return;
}

int validateLine(string line) {
    map<string, int> colorMaxMap = {
        {"red", 0},
        {"green", 0},
        {"blue", 0}
    };
    size_t i {0};
    size_t startIdx = line.find(";", i);
    while(startIdx != string::npos) {
        validateRound(line.substr(i, startIdx - i), colorMaxMap);
        i = (startIdx + 2);
        startIdx = line.find(";", i);
    }
    // validate last
    validateRound(line.substr(i), colorMaxMap);

    return colorMaxMap["red"] * colorMaxMap["blue"] * colorMaxMap["green"];
}

int main(void)
{
    string line;
    ifstream file;
    file.open("puzzleInput.txt");
    int sum {0};
    if (file.is_open()) {
        while (getline(file, line)) {
            size_t startIdx = line.find(":") + 2;
            size_t delimiter = line.find(" ");
            sum += validateLine(line.substr(startIdx));
        }
    }

    file.close();

    cout << "Total sum of powers: " << sum << endl;
 
    return 0;
}