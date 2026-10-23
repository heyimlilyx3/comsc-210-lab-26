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

// Function to read codes from a file into a vector
vector<string> readCodestoVector(const string& filename) {
    ifstream inputFile(filename);
    vector<string> codes;
    string code;
    while (inputFile >> code) {
        codes.push_back(code);
    }
    return codes;
}

list<string> readCodestoList(const string& filename) {
    ifstream inputFile(filename);
    list<string> codes;
    string code;
    while (inputFile >> code) {
        codes.push_back(code);
    }
    return codes;
}

set<string> readCodestoSet(const string& filename) {
    ifstream inputFile(filename);
    set<string> codes;
    string code;
    while (inputFile >> code) {
        codes.insert(code);
    }
    return codes;
}

vector<string> sortVector(const vector<string>& codes) {
    vector<string> sortedCodes = codes;
    sort(sortedCodes.begin(), sortedCodes.end());
    return sortedCodes;
}

list<string> sortList(const list<string>& codes) {
    list<string> sortedCodes = codes;
    sortedCodes.sort();
    return sortedCodes;
}

set<string> sortSet(const set<string>& codes) {
    return codes; // Sets are always sorted
}

struct testResult {
    double vectorReadTime;
    double listReadTime;
    double setReadTime;
    double vectorSortTime;
    double listSortTime;
    double setSortTime;
    double vectorDeleteTime;
    double listDeleteTime;
    double setDeleteTime;
};

testResult runTest(const string& filename) {
    testResult result;

    // Start timing for vector read
    auto start = chrono::steady_clock::now();
    vector<string> codes = readCodestoVector(filename);
    auto end = chrono::steady_clock::now();
    result.vectorReadTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for list read
    start = chrono::steady_clock::now();
    list<string> codeList = readCodestoList(filename);
    end = chrono::steady_clock::now();
    result.listReadTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for set read
    start = chrono::steady_clock::now();
    set<string> codeSet = readCodestoSet(filename);
    end = chrono::steady_clock::now();
    result.setReadTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for vector sort
    start = chrono::steady_clock::now();
    sort(codes.begin(), codes.end());
    end = chrono::steady_clock::now();
    result.vectorSortTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for list sort
    start = chrono::steady_clock::now();
    codeList.sort();
    end = chrono::steady_clock::now();
    result.listSortTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for set sort
    start = chrono::steady_clock::now();
    codeSet = sortSet(codeSet);
    end = chrono::steady_clock::now();
    result.setSortTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for vector delete
    start = chrono::steady_clock::now();
    codes.erase(codes.begin() + codes.size() / 2);
    end = chrono::steady_clock::now();
    result.vectorDeleteTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for list delete
    start = chrono::steady_clock::now();
    codeList.erase(next(codeList.begin(), codeList.size() / 2));
    end = chrono::steady_clock::now();
    result.listDeleteTime = chrono::duration<double, milli>(end - start).count();

    // Start timing for set delete
    start = chrono::steady_clock::now();
    codeSet.erase("TESTCODE");
    end = chrono::steady_clock::now();
    result.setDeleteTime = chrono::duration<double, milli>(end - start).count();

    return result;
}

testResult averageResults(const vector<testResult>& results) {
    testResult avgResult = {};
    for (const auto& result : results) {
        avgResult.vectorReadTime += result.vectorReadTime;
        avgResult.listReadTime += result.listReadTime;
        avgResult.setReadTime += result.setReadTime;
        avgResult.vectorSortTime += result.vectorSortTime;
        avgResult.listSortTime += result.listSortTime;
        avgResult.setSortTime += result.setSortTime;
        avgResult.vectorDeleteTime += result.vectorDeleteTime;
        avgResult.listDeleteTime += result.listDeleteTime;
        avgResult.setDeleteTime += result.setDeleteTime;
    }
    int numTests = results.size();
    avgResult.vectorReadTime /= numTests;
    avgResult.listReadTime /= numTests;
    avgResult.setReadTime /= numTests;
    avgResult.vectorSortTime /= numTests;
    avgResult.listSortTime /= numTests;
    avgResult.setSortTime /= numTests;
    avgResult.vectorDeleteTime /= numTests;
    avgResult.listDeleteTime /= numTests;
    avgResult.setDeleteTime /= numTests;

    return avgResult;
}

int main() {
    int numTests = 15;
    vector<testResult> results(numTests);
    for(int i = 0; i < numTests; ++i) {
        results[i] = runTest("codes.txt");
    }
    // Start printing output
    cout << "Number of simulations: " << numTests << endl;
    cout << "Operation:\tVector\tList\tSet" << endl;

    testResult avgResult = averageResults(results);
    cout << "Average:\t" << avgResult.vectorReadTime << "\t" << avgResult.listReadTime << "\t" << avgResult.setReadTime << endl;

    return 0;
}

