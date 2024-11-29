#include "pch.h"
#include "calculate.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

bool shouldSaveToFile(char saveToFile) {
    return saveToFile == 'y' || saveToFile == 'Y';
}

void checkValidParams(double a, double b, double s, int n) {
    if (n <= 0) {
        throw invalid_argument("Parameter n must be greater than 0.");
    }
    if (s <= 0) {
        throw invalid_argument("Step increment (s) must be greater than 0.");
    }
    if (a > b) {
        throw invalid_argument("Start of interval (a) must be less than or equal to end of interval (b).");
    }
}

double calculate(double x, int n) {
    double y = 0;

    if (x <= 0) {
        y = x;
        for (int i = 0; i < n; i++) {
            y *= (i * i - x);
        }
    } else {
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                y += x / (i + j);
            }
        }
    }

    return y;
}

void saveResultToFile(ofstream &fout, double x, double y) {
    cout << "x = " << x << ", y = " << y << "\n";
}

int main() {
    double a, b, s;
    int n;

    try {
        cout << "Enter the start of the interval (a): ";
        cin >> a;
        cout << "Enter the end of the interval (b): ";
        cin >> b;
        cout << "Enter the step increment (s): ";
        cin >> s;
        cout << "Enter the value of n (n > 0): ";
        cin >> n;

        if (cin.fail()) {
            throw invalid_argument("Invalid input. Please enter numeric values.");
        }

        checkValidParams(a, b, s, n);

        char saveToFile;
        cout << "Save the results to a file? (y/n): ";
        cin >> saveToFile;

        ofstream fout;
        if (shouldSaveToFile(saveToFile)) {
            fout.open("output.txt");
            if (!fout.is_open()) {
                throw runtime_error("Error: Unable to open file");
            }
        }

        double x = a;
        while (x <= b) {
            double y = calculate(x, n);

            cout << fixed << setprecision(4) << "x = " << x << ", y = " << y << "\n";

            if (shouldSaveToFile(saveToFile)) {
                saveResultToFile(fout, x, y);
            }

            x += s;
        }

        if (fout.is_open()) {
            fout.close();
            cout << "Results saved to file" << endl;
        }
    } catch (const exception &ex) {
        cerr << "Error: " << ex.what() << endl;
        return -1;
    } catch (...) {
        cerr << "Unknown error" << endl;
        return -2;
    }

    return 0;
}
