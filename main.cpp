#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

vector<double> mags;

int Magpartition(int low, int high) {
    double pivot = mags[low];
    int up = low+1;
    int down = high;

    while (up <= down) {
        while (up <= down && mags[up] >= pivot) {
            up++;
        }
        while (up <= down && mags[down] < pivot) {
            down--;
        }
        if (up < down) {
            std::swap(mags[up], mags[down]);
        }
    }
    std::swap(mags[low], mags[down]);
    return down;
}

void MagquickSort(int low, int high) {
    if (low < high) {
        if (low < 0)
            cout << "LOW IS OUT OF BOUNDS: " << low << "\n";
        if (high > mags.size()-1)
            cout << "HIGH IS OUT OF BOUNDS: " << high << "\n";
        int pivot = Magpartition(low, high);
        MagquickSort(low, pivot - 1);
        MagquickSort(pivot + 1, high);
    }
}


int main() {

    int testNum = 0;
    int count = 0;
    cout << "\n";
    for (int i = 1; i <= 1; i++) {

        ifstream file;
        file.open("data\\query_" + to_string(i) + ".csv");
        cout << "Loading Earthquake(" << to_string(i) << ")...\n";

        string line = "";

        while(getline(file, line) && testNum < 10) {
            string time = "", temp = "";
            double lat = -1, lon = -1, mag = -1;
            stringstream tokens(line);
            getline(tokens, time, ',');
            getline(tokens, temp, ',');
            lat = stod(temp);
            getline(tokens, temp, ',');
            lon = stod(temp);
            getline(tokens, temp, ',');
            mag = stod(temp);

            count++;
            mags.push_back(mag);
            line = "";
            testNum++;
        }
    }
    cout << count << " EQs loaded.\n\n";

    cout << "\n---------------------------\n";
    cout << "[SORTING]\n\n";

    MagquickSort(0, mags.size()-1);

    cout << "\n---------------------------\n";
    cout << "[Display List]\n\n";

    for (int i = 0; i < 10; i++)
        cout << i+1 << ". " << mags[i] << "\n";

    return 0;
}