
#include <iostream>
#include <string>
using namespace std;

void displayCarParkingDetails(int n, string carCode[]) {
    for (int i = 0; i < n; i++) {
        string w = carCode[i];

        // Last 4 digits are the duration
        string durationStr = w.substr(w.length() - 4);
        int duration = stoi(durationStr);

        // Remove duration
        string temp = w.substr(0, w.length() - 4);

        string typeCode;
        int rate;

        // Check the type code at the END
        if (temp.size() >= 4 &&
            temp.substr(temp.size() - 4) == "HTBK") {
            typeCode = "HTBK";
            rate = 50;
        }
        else if (temp.size() >= 3 &&
                 temp.substr(temp.size() - 3) == "DTS") {
            typeCode = "DTS";
            rate = 130;
        }
        else if (temp.size() >= 3 &&
                 temp.substr(temp.size() - 3) == "CTS") {
            typeCode = "CTS";
            rate = 150;
        }
        else if (temp.size() >= 2 &&
                 temp.substr(temp.size() - 2) == "S4") {
            typeCode = "S4";
            rate = 120;
        }
        else if (temp.size() >= 2 &&
                 temp.substr(temp.size() - 2) == "SE") {
            typeCode = "SE";
            rate = 120;
        }
        else if (temp.size() >= 2 &&
                 temp.substr(temp.size() - 2) == "SS") {
            typeCode = "SS";
            rate = 100;
        }
        else if (temp.size() >= 2 &&
                 temp.substr(temp.size() - 2) == "SD") {
            typeCode = "SD";
            rate = 80;
        }
        else if (temp.size() >= 2 &&
                 temp.substr(temp.size() - 2) == "SW") {
            typeCode = "SW";
            rate = 90;
        }

        // Car number is everything before the car type code
        string plate = temp.substr(0, temp.length() - typeCode.length());

        cout << plate << " " << duration * rate << endl;
    }
}

int main() {
    int n;
    cin >> n;

    string strs[10000];

    for (int i = 0; i < n; i++) {
        cin >> strs[i];
    }

    displayCarParkingDetails(n, strs);

    return 0;
}
