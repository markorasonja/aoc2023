#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

map<string, int> colorMaxMap = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

bool validateRound(string round) {
    size_t i {0};
    size_t startIdx = round.find(",");
    while (startIdx != string::npos) {
        size_t delimiter = round.find(" ", i);
        int num = stoi(round.substr(i, delimiter - i));
        string color = round.substr(delimiter + 1, startIdx - delimiter - 1);
        if (colorMaxMap[color] < num) return false;
        i = startIdx + 2;
        startIdx = round.find(",", i);
    }
    
    //last 
    size_t delimiter = round.find(" ", i);
    int num = stoi(round.substr(i, delimiter - i));
    string color = round.substr(delimiter + 1);
    return colorMaxMap[color] >= num;
}

bool validateLine(string line) {
    size_t i {0};
    size_t startIdx = line.find(";", i);
    while(startIdx != string::npos) {
        if (!validateRound(line.substr(i, startIdx - i))) {
            return false;
        }
        i = (startIdx + 2);
        startIdx = line.find(";", i);
    }
    // validate last
    return validateRound(line.substr(i));
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
            int gameId = stoi(line.substr(delimiter + 1, startIdx - delimiter));
            if(validateLine(line.substr(startIdx))) sum += gameId;
        }
    }

    file.close();

    cout << "Total sum: " << sum << endl;
 
    return 0;
}