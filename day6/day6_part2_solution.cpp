#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;


struct Race {
    long time;
    long distance;
};


/* 
    Since d = f(t_acl) = t_acl * (t_total - t_acl),
    t_acl can be calculated as quadratic function.
    Given d to beat can serve as constant term C.
    The parabola is conacave so numbers which give
    greater d are just numbers between two solution points.
*/
long calculateNumber(long t_total, long distance) {
    double numbersBetween = sqrt(pow(t_total, 2) - 4 * distance);
    return (long) ceil(numbersBetween);
}   


int main(void)
{
    ifstream file;
    file.open("input.txt");
    long multipliedWays {1};
    int i;
    Race race;

    if (file.is_open()) {
        string times;
        string distances;
        race.time = 0;
        race.distance = 0;
        getline(file, times); getline(file, distances);
        /* times */
        i = times.find(":") + 1;
        while (i < times.size()) {
            int t = atoi(&times.at(i));
            i = (times.find(std::to_string(t)) + std::to_string(t).length());
            race.time *= pow(10, std::to_string(t).length());
            race.time += t;
        }

        /* distances */
        i = distances.find(":") + 1;
        while (i < distances.size()) {
            int d = atoi(&distances.at(i));
            i = (distances.find(std::to_string(d)) + std::to_string(d).length());
            race.distance *= pow(10, std::to_string(d).length());
            race.distance += d;
        }

        long more_than_record {0};
        long d_to_beat = race.distance;
        long available_time = race.time;
        multipliedWays = calculateNumber(available_time, d_to_beat);
    }

    cout << "Multipied ways is: " << multipliedWays << endl;

    file.close();

    return 0;
}
