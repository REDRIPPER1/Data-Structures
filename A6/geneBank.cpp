#include "geneBank.h"
#include <algorithm>
#include <cstring>

// =================================== PUBLIC FUNCTIONS =======================================================

GENE_BANK::GENE_BANK() 
{
    this->fileSize = 0;
    this->entryByte = sizeof(Sample);
}

GENE_BANK::~GENE_BANK() 
{
    cout << "Destructing ..." << endl;
}

void GENE_BANK::sort(Sample array[], int fileSize)
{
    // fileSize is expected to be the last index in the array
    int n = fileSize + 1;
    if(n <= 1) return;

    std::sort(array, array + n, [](const Sample &a, const Sample &b){
        if(a.speciesCode != b.speciesCode)
            return a.speciesCode < b.speciesCode;
        return a.sampleID < b.sampleID;
    });
}

void GENE_BANK::indexSamples(Sample array[], int indexArray[]) 
{
    this->p_index(array, indexArray);
}

void GENE_BANK::displayResearcher(int speciesCode, int offset, char* filename) 
{
    bool checkSample;

    checkSample = searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_displayResearcher(speciesCode, offset, filename);
    } else {
        cout << "Sample record doesn't exist! Can't display researcher name." << endl;
    }
}

bool GENE_BANK::searchSample(int speciesCode, int offset, char* filename) 
{
    // Here the first parameter is the base index (starting record index) for a species
    int baseIndex = speciesCode;

    if(baseIndex < 0) return false;

    fstream in;
    in.open(filename, ios::in | ios::binary);
    if(!in.is_open()) return false;

    in.seekg(0, ios::end);
    int totalBytes = (int)in.tellg();
    int totalRecords = totalBytes / sizeof(Sample);

    int targetIndex = baseIndex + offset;
    if(targetIndex < 0 || targetIndex >= totalRecords){
        in.close();
        return false;
    }

    Sample s;
    in.seekg((long long)targetIndex * sizeof(Sample), ios::beg);
    in.read(reinterpret_cast<char*>(&s), sizeof(Sample));
    in.close();

    // consider a deleted record if sampleID == -1
    if(s.sampleID == -1) return false;
    return true;
}


void GENE_BANK::updateResearcher(int speciesCode, int offset, char* newName, char* filename) 
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_updateResearcher(speciesCode, offset, newName, filename);
    } else {
        cout << "Sample record to be updated doesn't exist!" << endl;
        p_updateResearcher(speciesCode, offset, newName, filename);
    }
}

void GENE_BANK::deleteSample(int speciesCode, int offset, char* filename)
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_deleteSample(speciesCode, offset, filename);
    } else {
        cout << "Sample record to be deletesd doesn't exist!" << endl;
    }
}

void GENE_BANK::printSampleRange(int speciesCode, int startIndex, int endIndex, char* filename) 
{
    if(startIndex >= endIndex)
        throw MyException("ERROR: start index is larger than end index!");
    else
        this->p_printRange(speciesCode, startIndex, endIndex, filename);
}

// =================================== PRIVATE FUNCTIONS =======================================================

// your sorting algorithm here

void GENE_BANK::p_index(Sample array[], int indexArray[]) 
{
    // Build starting-record index for each species code (0..4)
    // Assumes `this->fileSize` has been set to total number of records
    int total = this->fileSize;
    for(int i=0;i<5;i++) indexArray[i] = -1;

    for(int i=0;i<total;i++){
        int sc = array[i].speciesCode;
        if(sc >=0 && sc <=4){
            if(indexArray[sc] == -1) indexArray[sc] = i;
        }
    }

    // For species codes that do not appear, set index to total (so ranges compute as 0)
    for(int i=0;i<5;i++) if(indexArray[i] == -1) indexArray[i] = total;
}

void GENE_BANK::p_displayResearcher(int speciesCode, int offset, char* filename) 
{
    /* These are the 5 unique species codes
        0 - H_SAP
        1 - M_MUS
        2 - D_MEL
        3 - E_COL
        4 - A_THA
    */

    int baseIndex = speciesCode;
    fstream in;
    in.open(filename, ios::in | ios::binary);
    if(!in.is_open()){
        cout<<"ERROR: cannot open file "<<filename<<endl;
        return;
    }

    int target = baseIndex + offset;
    in.seekg((long long)target * sizeof(Sample), ios::beg);
    Sample s;
    in.read(reinterpret_cast<char*>(&s), sizeof(Sample));
    if(s.sampleID == -1){
        cout<<"Sample record doesn't exist!"<<endl;
    } else {
        cout<<"Researcher: "<<s.researcher<<endl;
    }

    in.close();
}

void GENE_BANK::p_updateResearcher(int speciesCode, int offset, char* newName, char* filename) 
{
    int baseIndex = speciesCode;
    fstream io;
    io.open(filename, ios::in | ios::out | ios::binary);
    if(!io.is_open()){
        cout<<"ERROR: cannot open file "<<filename<<endl;
        return;
    }

    int target = baseIndex + offset;
    io.seekg((long long)target * sizeof(Sample), ios::beg);
    Sample s;
    io.read(reinterpret_cast<char*>(&s), sizeof(Sample));

    // update researcher name (safe copy)
    strncpy(s.researcher, newName, MAX_RESEARCHER_NAME-1);
    s.researcher[MAX_RESEARCHER_NAME-1] = '\0';

    io.seekp((long long)target * sizeof(Sample), ios::beg);
    io.write(reinterpret_cast<char*>(&s), sizeof(Sample));
    io.close();
}

void GENE_BANK::p_deleteSample(int speciesCode, int offset, char* filename) 
{
    int baseIndex = speciesCode;
    fstream io;
    io.open(filename, ios::in | ios::out | ios::binary);
    if(!io.is_open()){
        cout<<"ERROR: cannot open file "<<filename<<endl;
        return;
    }

    int target = baseIndex + offset;
    io.seekg((long long)target * sizeof(Sample), ios::beg);
    Sample s;
    io.read(reinterpret_cast<char*>(&s), sizeof(Sample));

    // mark as deleted
    s.sampleID = -1;
    s.speciesCode = -1;
    s.purityScore = 0.0f;
    s.researcher[0] = '\0';

    io.seekp((long long)target * sizeof(Sample), ios::beg);
    io.write(reinterpret_cast<char*>(&s), sizeof(Sample));
    io.close();
}

void GENE_BANK::p_printRange(int speciesCode, int startIndex, int endIndex, char* filename) 
{
    int baseIndex = speciesCode;
    fstream in;
    in.open(filename, ios::in | ios::binary);
    if(!in.is_open()){
        cout<<"ERROR: cannot open file "<<filename<<endl;
        return;
    }

    for(int off = startIndex; off <= endIndex; off++){
        int target = baseIndex + off;
        in.seekg((long long)target * sizeof(Sample), ios::beg);
        Sample s;
        in.read(reinterpret_cast<char*>(&s), sizeof(Sample));
        if(s.sampleID == -1) continue;
        cout<<"ID: "<<s.sampleID<<" Species: "<<s.speciesCode<<" Purity: "<<s.purityScore<<" Researcher: "<<s.researcher<<endl;
    }

    in.close();
}
