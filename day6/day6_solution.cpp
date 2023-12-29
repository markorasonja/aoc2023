#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct Race {
    int time;
    int distance;
};


int calculateDistance(int t_total, int t_acl) {
    return t_acl * (t_total - t_acl);
}


int main(void)
{
    ifstream file;
    file.open("input.txt");
    int multipliedWays {1};
    int i;
    int raceIdx {0};
    vector<Race> races;

    if (file.is_open()) {
        string times;
        string distances;
        getline(file, times); getline(file, distances);
        /* times */
        i = times.find(":") + 1;
        while (i < times.size()) {
            Race r;
            int t = atoi(&times.at(i));
            i = (times.find(std::to_string(t)) + std::to_string(t).length());
            r.time = t;
            races.push_back(r);
        }

        /* distances */
        i = distances.find(":") + 1;
        while (i < distances.size()) {
            int d = atoi(&distances.at(i));
            i = (distances.find(std::to_string(d)) + std::to_string(d).length());
            races.at(raceIdx++).distance = d;
        }

        for (int j = 0; j < races.size(); j++) {
            int more_than_record {0};
            int d_to_beat = races.at(j).distance;
            int available_time = races.at(j).time;
            for (int t = 1; t < available_time; t++) {
                if (calculateDistance(available_time, t) > d_to_beat) more_than_record++;
            }
            multipliedWays *= more_than_record;
        }
    }

    cout << "Multipied ways is: " << multipliedWays << endl;

    file.close();

    return 0;
}

/*
    starting speed - 0 mm/ms
    each ms -> += 1 mm/ms

    Time:        60     80     86     76
    Distance:   601   1163   1559   1300

*/