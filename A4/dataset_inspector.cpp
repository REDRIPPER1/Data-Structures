#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

vector<pair<string, int>> readDataFromFile(const string& filename) {
    vector<pair<string, int>> data;
    ifstream file(filename);
    string key;
    int value;
    if (!file) {
        cerr << "Error reading file: " << filename << endl;
        return data;
    }
    while (file >> key >> value) {
        data.push_back({key, value});
    }
    file.close();
    return data;
}

void displayDatasetInfo(const string& filename) {
    cout << "\n==========================================" << endl;
    cout << "DATASET: " << filename << endl;
    cout << "==========================================" << endl;

    auto data = readDataFromFile(filename);

    if (data.empty()) {
        cout << "No data found or file could not be read." << endl;
        return;
    }

    cout << "Total records: " << data.size() << endl;
    cout << "\nFirst 10 records:" << endl;
    cout << setw(5) << "Index" << setw(35) << "Key" << setw(10) << "Value" << endl;
    cout << string(50, '-') << endl;

    for (size_t i = 0; i < min(size_t(10), data.size()); ++i) {
        cout << setw(5) << i + 1
             << setw(35) << data[i].first
             << setw(10) << data[i].second << endl;
    }

    if (data.size() > 10) {
        cout << "\nLast 5 records:" << endl;
        cout << setw(5) << "Index" << setw(35) << "Key" << setw(10) << "Value" << endl;
        cout << string(50, '-') << endl;

        for (size_t i = data.size() - 5; i < data.size(); ++i) {
            cout << setw(5) << i + 1
                 << setw(35) << data[i].first
                 << setw(10) << data[i].second << endl;
        }
    }

    // Analyze key characteristics
    cout << "\nDataset Analysis:" << endl;
    cout << "- Average key length: ";
    size_t totalLength = 0;
    for (const auto& pair : data) {
        totalLength += pair.first.length();
    }
    cout << fixed << setprecision(1) << (double)totalLength / data.size() << " characters" << endl;

    cout << "- Key length range: ";
    size_t minLen = data[0].first.length();
    size_t maxLen = data[0].first.length();
    for (const auto& pair : data) {
        minLen = min(minLen, pair.first.length());
        maxLen = max(maxLen, pair.first.length());
    }
    cout << minLen << " - " << maxLen << " characters" << endl;

    cout << "- Value range: ";
    int minVal = data[0].second;
    int maxVal = data[0].second;
    for (const auto& pair : data) {
        minVal = min(minVal, pair.second);
        maxVal = max(maxVal, pair.second);
    }
    cout << minVal << " - " << maxVal << endl;

    // Check for potential collisions (simple analysis)
    cout << "- Sequential values: " << (data[1].second - data[0].second == 1 ? "Yes" : "No") << endl;
}

int main() {
    cout << "HASH TABLE DATASET INSPECTOR" << endl;
    cout << "============================" << endl;

    vector<string> dataFiles = {
        "data/no_collision_data.txt",
        "data/low_collision_data.txt",
        "data/high_collision_data.txt"
    };

    for (const auto& file : dataFiles) {
        displayDatasetInfo(file);
    }

    cout << "\n==========================================" << endl;
    cout << "RAW DATA SAMPLE (first 20 lines of no_collision_data.txt)" << endl;
    cout << "==========================================" << endl;

    ifstream sampleFile("data/no_collision_data.txt");
    string line;
    int lineCount = 0;
    while (getline(sampleFile, line) && lineCount < 20) {
        cout << line << endl;
        lineCount++;
    }
    sampleFile.close();

    return 0;
}