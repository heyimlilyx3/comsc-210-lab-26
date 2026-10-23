#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <fstream>
#include <list>
#include <set>
#include <string>
#include <iomanip>
#include <iterator>

using namespace std;


int main() {
    ifstream inputFile("codes.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    // Start printing output
    cout << "Operation:\tVector\tList\tSet" << endl;

    // Start Inputs
    cout << "Input:\t\t";
    // Start timing 
    auto start = chrono::steady_clock::now();

    vector<string> codes;
    string code;
    while (inputFile >> code) {
        codes.push_back(code);
    }

    // End timing
    auto end = chrono::steady_clock::now();

    // Calculate duration
    auto duration = chrono::duration<double, milli>(end - start);
    cout << fixed << setprecision(3);
    cout << duration.count() << "\t";

    inputFile.close();

    // Input into list
    ifstream inputFileList("codes.txt");
    if (!inputFileList) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Start timing
    start = chrono::steady_clock::now();

    list<string> codeList;
    while (inputFileList >> code) {
        codeList.push_back(code);
    }

    // End timing
    end = chrono::steady_clock::now();

    // Calculate duration
    duration = chrono::duration<double, milli>(end - start);
    cout << duration.count() << "\t";

    inputFileList.close();

    // Input into set
    ifstream inputFileSet("codes.txt");
    if (!inputFileSet) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Start timing
    start = chrono::steady_clock::now();

    set<string> codeSet;
    while (inputFileSet >> code) {
        codeSet.insert(code);
    }

    // End timing
    end = chrono::steady_clock::now();

    // Calculate duration
    duration = chrono::duration<double, milli>(end - start);
    cout << duration.count() << endl;

    inputFileSet.close();

    // Now for sorting
    cout << "Sorting:\t";

    // vector sort
    start = chrono::steady_clock::now();
    sort(codes.begin(), codes.end());
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << "\t";

    // list sort
    start = chrono::steady_clock::now();
    codeList.sort();
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << "\t";

    // set sort (not needed, as set is always sorted)
    cout << "-1" << endl;

    // Inserting
    cout << "Inserting:\t";
    // vector insert
    start = chrono::steady_clock::now();
    codes.insert(codes.begin() + codes.size() / 2, "TESTCODE");
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << "\t";

    // list insert
    start = chrono::steady_clock::now();
    codeList.insert(next(codeList.begin(), codeList.size() / 2), "TESTCODE");
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << "\t";

    // set insert
    start = chrono::steady_clock::now();
    codeSet.insert("TESTCODE");
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << endl;


    // Deleting
    cout << "Deleting:\t";
    // delete middle element from vector
    start = chrono::steady_clock::now();
    codes.erase(codes.begin() + codes.size() / 2);
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << " \t";

    // delete middle element from list
    start = chrono::steady_clock::now();
    codeList.erase(next(codeList.begin(), codeList.size() / 2));
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << " \t";

    // delete element from set
    start = chrono::steady_clock::now();
    codeSet.erase("TESTCODE");
    end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end - start).count() << endl;
    return 0;
}

