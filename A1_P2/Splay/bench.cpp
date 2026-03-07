
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "splay.h" 

using namespace std;
using namespace std::chrono;

// I copied code from various sources to craft the benchmark search as no material was given in the class.
vector<int> loadPattern(const string& filename) {
    vector<int> keys;
    // Routes to the folder you specified
    string filepath = "accessPattern/" + filename; 
    ifstream file(filepath);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filepath << ". Check folder name and path." << endl;
        return keys;
    }
    
    int key;
    while (file >> key) {
        keys.push_back(key);
    }
    file.close();
    return keys;
}

// Benchmark execution function
void runBenchmark(SplayTree* tree, const vector<int>& pattern, const string& variantName, const string& patternName) {
    
    tree->resetMetrics();

    auto start = high_resolution_clock::now();
    
    for (int key : pattern) {
        tree->search(key);
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // Calculate Average Depth
    double avgDepth = (tree->searchCount > 0) ? 
                      (double)tree->totalSearchDepth / tree->searchCount : 0.0;

    // Print formatted row
    cout << left << setw(18) << variantName 
         << left << setw(18) << patternName 
         << left << setw(18) << tree->totalRotations 
         << left << setw(18) << fixed << setprecision(2) << avgDepth 
         << left << duration.count() << " ms" << endl;
}

void populateTree(SplayTree* tree, int numElements) {
    for (int i = 1; i <= numElements; i++) {
        tree->insert(i);
    }
}

int main() {
    const int TREE_SIZE = 10000; 

    cout << "Loading patterns from 'access pattern/' folder..." << endl;
    vector<int> seqPattern = loadPattern("sequential.txt");
    vector<int> uniPattern = loadPattern("uniform_random.txt");
    vector<int> skewPattern = loadPattern("zipf_skewed.txt");
    vector<int> wsPattern = loadPattern("working_set.txt");

    if (seqPattern.empty()) return 1; 

    cout << string(85, '-') << endl;
    cout << left << setw(18) << "Variant" 
         << left << setw(18) << "Access Pattern" 
         << left << setw(18) << "Total Rotations" 
         << left << setw(18) << "Avg Depth" 
         << left << "Total Time" << endl;
    cout << string(85, '-') << endl;


    BottomUpSplayTree bu_seq, bu_uni, bu_skew, bu_ws;

    cout << "sequential.txt..." << endl;
    
    populateTree(&bu_seq, TREE_SIZE);
    runBenchmark(&bu_seq, seqPattern, "Bottom-up", "Sequential");

    populateTree(&bu_uni, TREE_SIZE);
    runBenchmark(&bu_uni, uniPattern, "Bottom-up", "Uniform");

    populateTree(&bu_skew, TREE_SIZE);
    runBenchmark(&bu_skew, skewPattern, "Bottom-up", "Skewed");

    populateTree(&bu_ws, TREE_SIZE);
    runBenchmark(&bu_ws, wsPattern, "Bottom-up", "Working Set");

    cout << string(85, '-') << endl;

    TopDownSplayTree td_seq, td_uni, td_skew, td_ws;

    cout << "uniform_random.txt..." << endl;
    
    populateTree(&td_seq, TREE_SIZE);
    runBenchmark(&td_seq, seqPattern, "Top-Down", "Sequential");

    populateTree(&td_uni, TREE_SIZE);
    runBenchmark(&td_uni, uniPattern, "Top-Down", "Uniform");

    populateTree(&td_skew, TREE_SIZE);
    runBenchmark(&td_skew, skewPattern, "Top-Down", "Skewed");

    populateTree(&td_ws, TREE_SIZE);
    runBenchmark(&td_ws, wsPattern, "Top-Down", "Working Set");

    cout << string(85, '-') << endl;

    SemiSplayTree ss_seq, ss_uni, ss_skew, ss_ws;

    cout << "zipf_skewed.txt..." << endl;
    populateTree(&ss_seq, TREE_SIZE);
    runBenchmark(&ss_seq, seqPattern, "Semi-Splay", "Sequential");
    populateTree(&ss_uni, TREE_SIZE);
    runBenchmark(&ss_uni, uniPattern, "Semi-Splay", "Uniform");
    populateTree(&ss_skew, TREE_SIZE);
    runBenchmark(&ss_skew, skewPattern, "Semi-Splay", "Skewed");
    populateTree(&ss_ws, TREE_SIZE);
    runBenchmark(&ss_ws, wsPattern, "Semi-Splay", "Working Set");
    cout << string(85, '-') << endl;


    WeightedSplay ws_seq, ws_uni, ws_skew, ws_ws;

    cout << "working_set.txt..." << endl;
    populateTree(&ws_seq, TREE_SIZE);
    runBenchmark(&ws_seq, seqPattern, "Weighted-Splay", "Sequential");
    populateTree(&ws_uni, TREE_SIZE);
    runBenchmark(&ws_uni, uniPattern, "Weighted-Splay", "Uniform");
    populateTree(&ws_skew, TREE_SIZE);
    runBenchmark(&ws_skew, skewPattern, "Weighted-Splay", "Skewed");
    populateTree(&ws_ws, TREE_SIZE);
    runBenchmark(&ws_ws, wsPattern, "Weighted-Splay", "Working Set");
    cout << string(85, '-') << endl;

    return 0;
}