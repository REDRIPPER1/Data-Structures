#include "hash.h"

// Constructor - initializing table based on chosen hash table variant
HashTable::HashTable(int size, CollisionHandling variant) 
{
    tableSize = size; 
    elementCount = 0; 
    method = variant;
    switch (method) {
        case CHAINING_VECTOR:
            tableVector.resize(size);
            break;
        case CHAINING_LIST:
            tableList.resize(size);
            break;
        case CHAINING_BST:
            tableBST.resize(size);
            break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            tableProbing.resize(size);
            break;
    }
}

HashTable::~HashTable() {}

int HashTable::hash1(const string& key) const {
    unsigned long hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c);
    }
    return hash % tableSize;
}

int HashTable::hash2(const string& key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return 1 + (hash % (tableSize - 1));
}

// complete this
int HashTable::probe(int index, int i, const string& key) const {
    switch (method) {
        case LINEAR_PROBING:
            return (index + i) % tableSize;
        case QUADRATIC_PROBING: {
            long long step = (long long)i * i;
            int probeIndex = (index + step) % tableSize;
            if (probeIndex < 0) probeIndex += tableSize;
            return probeIndex;
        }
        case DOUBLE_HASHING: {
            long long step = (long long)i * hash2(key);
            int probeIndex = (index + step) % tableSize;
            if (probeIndex < 0) probeIndex += tableSize;
            return probeIndex;
        }
        default:
            return index;
    }
}
void HashTable::insert(const string& key, int value) {
    resizeIfNeeded();
    int index = hash1(key);

    switch (method) {
        case CHAINING_VECTOR:
            for (auto& pair : tableVector[index]) {
                if (pair.first == key) {
                    pair.second = value; // Key already exists, update the value
                    return;
                }
            }
            tableVector[index].push_back({key, value});
            break;

        case CHAINING_LIST:
            for (auto& pair : tableList[index]) {
                if (pair.first == key) {
                    pair.second = value; // Key already exists, update the value
                    return;
                }
            }
            tableList[index].push_back({key, value});
            break;

        case CHAINING_BST:
            // complete this - use AVL insert method
            tableBST[index].insert(key, value);
            break;

        case LINEAR_PROBING:
            for (int i = 0; i < tableSize; ++i) {
                int probeIndex = probe(index, i, key);
                if (tableProbing[probeIndex].first.empty() || tableProbing[probeIndex].first == key) {
                    tableProbing[probeIndex] = {key, value};
                    break;
                }
            }
            break;

        case QUADRATIC_PROBING:
            for (int i = 0; i < tableSize; ++i) {
                int probeIndex = probe(index, i, key);
                if (tableProbing[probeIndex].first.empty() || tableProbing[probeIndex].first == key) {
                    tableProbing[probeIndex] = {key, value};
                    break;
                }
            }
            break;

        case DOUBLE_HASHING:
            for (int i = 0; i < tableSize; ++i) {
                int probeIndex = probe(index, i, key);
                if (tableProbing[probeIndex].first.empty() || tableProbing[probeIndex].first == key) {
                    tableProbing[probeIndex] = {key, value};
                    break;
                }
            }
            break;

    }
    elementCount++;
}

bool HashTable::search(const string& key, int& value) {
    int index = hash1(key);

    switch (method) {
        case CHAINING_VECTOR:
            for (const auto& pair : tableVector[index]) {
                if (pair.first == key) {
                    value = pair.second;
                    return true;
                }
            }
            break;

        case CHAINING_LIST:
            for (const auto& pair : tableList[index]) {
                if (pair.first == key) {
                    value = pair.second;
                    return true;
                }
            }
            break;

        case CHAINING_BST:
            // complete this - use AVL search method
            return tableBST[index].search(key, value);

        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            for (int i = 0; i < tableSize; ++i) {
                int probeIndex = probe(index, i, key);
                if (tableProbing[probeIndex].first.empty()) {
                    return false; // Key not found
                }
                if (tableProbing[probeIndex].first == key) {
                    value = tableProbing[probeIndex].second;
                    return true;
                }
            }
            break;
    }

    return false; // Key not found

}

bool HashTable::remove(const string& key) {
    int index = hash1(key);
    int dummy;
    switch (method) {
        case CHAINING_VECTOR:
            for (auto it = tableVector[index].begin(); it != tableVector[index].end(); ++it) {
                if (it->first == key) {
                    tableVector[index].erase(it);
                    elementCount--;
                    return true;
                }
            }
            break;

        case CHAINING_LIST:
            for (auto it = tableList[index].begin(); it != tableList[index].end(); ++it) {
                if (it->first == key) {
                    tableList[index].erase(it);
                    elementCount--;
                    return true;
                }
            }
            break;

        case CHAINING_BST:
            // complete this - use AVL delete method
            if (tableBST[index].search(key, dummy)) {
                tableBST[index].remove(key);
                elementCount--;
                return true;
            }
            break;

        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            for (int i = 0; i < tableSize; ++i) {
                int probeIndex = probe(index, i, key);
                if (tableProbing[probeIndex].first.empty()) {
                    return false; // Key not found
                }
                if (tableProbing[probeIndex].first == key) {
                    tableProbing[probeIndex] = {"", 0}; // Mark as deleted
                    elementCount--;
                    return true;
                }
            }
            break;
    }
    
    return false;
}

// Function to read data from file
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

// Benchmark function for custom HashTable
void HashTable::benchmarkHashTable(HashTable& table, const vector<pair<string, int>>& data, int numSearch, int numDelete) {
    auto start = chrono::high_resolution_clock::now();

    // Insertions
    for (const auto& pair : data) {
        table.insert(pair.first, pair.second);
    }

    auto insertEnd = chrono::high_resolution_clock::now();

    // Searches
    int value;
    for (int i = 0; i < numSearch; ++i) {
        table.search(data[rand() % data.size()].first, value);
    }

    auto searchEnd = chrono::high_resolution_clock::now();

    // Deletions
    for (int i = 0; i < numDelete; ++i) {
        table.remove(data[rand() % data.size()].first);
    }

    auto end = chrono::high_resolution_clock::now();

    auto insertTime = chrono::duration_cast<chrono::microseconds>(insertEnd - start);
    auto searchTime = chrono::duration_cast<chrono::microseconds>(searchEnd - insertEnd);
    auto deleteTime = chrono::duration_cast<chrono::microseconds>(end - searchEnd);

    cout << "Insertion time: " << insertTime.count() << " microseconds" << endl;
    cout << "Search time: " << searchTime.count() << " microseconds" << endl;
    cout << "Deletion time: " << deleteTime.count() << " microseconds" << endl;
}

void HashTable::displayStats() {
    int totalElements = 0;
    int maxChainLength = 0;
    int emptyBuckets = 0;

    switch (method) {
        case CHAINING_VECTOR:
            for (const auto& bucket : tableVector) {
                if (bucket.empty()) emptyBuckets++;
                maxChainLength = max(maxChainLength, (int)bucket.size());
                totalElements += bucket.size();
            }
            break;
        case CHAINING_LIST:
            for (const auto& bucket : tableList) {
                if (bucket.empty()) emptyBuckets++;
                maxChainLength = max(maxChainLength, (int)bucket.size());
                totalElements += bucket.size();
            }
            break;
        case CHAINING_BST:
            for (const auto& bucket : tableBST) {
                vector<pair<string, int>> elements = bucket.inOrderTraversal();
                if (elements.empty()) {
                    emptyBuckets++;
                } else {
                    maxChainLength = max(maxChainLength, (int)elements.size());
                    totalElements += elements.size();
                }
            }
            break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            for (const auto& entry : tableProbing) {
                if (!entry.first.empty()) totalElements++;
                else emptyBuckets++;
            }
            break;
    }

    cout << "Total elements: " << totalElements << endl;
    cout << "Load factor: " << (double)totalElements / tableSize << endl;
    cout << "Empty buckets: " << emptyBuckets << endl;
    if (method == CHAINING_VECTOR || method == CHAINING_LIST || method == CHAINING_BST) {
        cout << "Max chain length: " << maxChainLength << endl;
    }
}


void HashTable::rehash() {
    // Save old data
    vector<pair<string, int>> oldData;
    
    switch (method) {
        case CHAINING_VECTOR:
            for (const auto& bucket : tableVector) {
                for (const auto& pair : bucket) {
                    oldData.push_back(pair);
                }
            }
            break;
        case CHAINING_LIST:
            for (const auto& bucket : tableList) {
                for (const auto& pair : bucket) {
                    oldData.push_back(pair);
                }
            }
            break;
        case CHAINING_BST:
            for (const auto& bucket : tableBST) {
                vector<pair<string, int>> elements = bucket.inOrderTraversal();
                for (const auto& pair : elements) {
                    oldData.push_back(pair);
                }
            }
            break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            for (const auto& entry : tableProbing) {
                if (!entry.first.empty()) {
                    oldData.push_back(entry);
                }
            }
            break;
    }
    
    // Find next prime or double the size
    int newSize = tableSize * 2 + 1;
    tableSize = newSize;
    elementCount = 0;
    
    // Clear and resize containers
    switch (method) {
        case CHAINING_VECTOR:
            tableVector.clear();
            tableVector.resize(newSize);
            break;
        case CHAINING_LIST:
            tableList.clear();
            tableList.resize(newSize);
            break;
        case CHAINING_BST:
            tableBST.clear();
            tableBST.resize(newSize);
            break;
        case LINEAR_PROBING:
        case QUADRATIC_PROBING:
        case DOUBLE_HASHING:
            tableProbing.clear();
            tableProbing.resize(newSize, {"", 0});
            break;
    }
    
    // Re-insert all old data
    for (const auto& pair : oldData) {
        insert(pair.first, pair.second);
    }
}


int HashTable::findEmptySlot(const string& key) {
    // For probing-based methods, find an empty slot
    // Returns the index of an empty slot, or -1 if table is full
    for (int i = 0; i < tableSize; ++i) {
        int probeIndex = probe(hash1(key), i, key);
        if (tableProbing[probeIndex].first.empty()) {
            return probeIndex;
        }
    }
    return -1; // Table is full
}

// try experimenting with different thresholds for each technique
void HashTable::resizeIfNeeded() {
    // Check load factor and resize if needed
    double loadFactor = (double)elementCount / tableSize;
    
    // Different thresholds for different methods:
    // Chaining methods can handle higher load factors (0.75-1.0)
    // Probing methods need lower load factors (0.5-0.75) for performance
    double threshold = 0.75;
    
    if (method == LINEAR_PROBING || method == QUADRATIC_PROBING || method == DOUBLE_HASHING) {
        threshold = 0.65; // More conservative for probing methods
    }
    
    if (loadFactor >= threshold) {
        rehash();
    }
}

// Benchmark function for built-in hash table in C++
void benchmarkStdUnorderedMap(const vector<pair<string, int>>& data, int numSearch, int numDelete) {
    unordered_map<string, int> stdMap;

    auto start = chrono::high_resolution_clock::now();

    // Insertions
    for (const auto& pair : data) {
        stdMap[pair.first] = pair.second;
    }

    auto insertEnd = chrono::high_resolution_clock::now();

    // Searches
    int value;
    for (int i = 0; i < numSearch; ++i) {
        auto it = stdMap.find(data[rand() % data.size()].first);
        if (it != stdMap.end()) {
            value = it->second;
        }
    }

    auto searchEnd = chrono::high_resolution_clock::now();

    // Deletions
    for (int i = 0; i < numDelete; ++i) {
        stdMap.erase(data[rand() % data.size()].first);
    }

    auto end = chrono::high_resolution_clock::now();

    auto insertTime = chrono::duration_cast<chrono::microseconds>(insertEnd - start);
    auto searchTime = chrono::duration_cast<chrono::microseconds>(searchEnd - insertEnd);
    auto deleteTime = chrono::duration_cast<chrono::microseconds>(end - searchEnd);

    cout << "std::unordered_map Benchmark Results:" << endl;
    cout << "Insertion time: " << insertTime.count() << " microseconds" << endl;
    cout << "Search time: " << searchTime.count() << " microseconds" << endl;
    cout << "Deletion time: " << deleteTime.count() << " microseconds" << endl;
}