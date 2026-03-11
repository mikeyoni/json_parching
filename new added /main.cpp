#include <vector>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

// Global vector to track duplicates across functions if needed
vector<string> dupe;

void clean_json(string filePath) {
    ifstream jsonfile(filePath);
    if (!jsonfile.is_open()) {
        cout << "ERROR: " << filePath << " not found!" << endl;
        return;
    }
    json data;
    jsonfile >> data;
    jsonfile.close();

    json onlysource = json::array();
    // Using size_t to prevent "signedness" warnings on GCC 15
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].contains("nsfw") && data[i]["nsfw"] == 0) {
            onlysource.push_back(data[i]["sources"]);
        }
    }

    string filename = "onlysource.json";
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << onlysource.dump(4);
        outfile.close();
        cout << "SUCCESS! Items kept: " << onlysource.size() << endl;
    }
}

void clear_source(const string &filePath, const string &finalfile) {
    ifstream jsonfile(filePath);
    if (!jsonfile.is_open()) {
        cout << "ERROR: " << filePath << " not found!" << endl;
        return;
    }
    json data;
    jsonfile >> data;
    jsonfile.close();

    json final = json::array();
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            if (data[i][j].contains("lang") && data[i][j]["lang"] == "all") {
                final.push_back(data[i][j]);
            }
        }
    }

    ofstream outfile(finalfile);
    if (outfile.is_open()) {
        outfile << final.dump(4);
        outfile.close();
    }
}

void dupe_remove(const string &filePath, const string &finalfile) {
    json data;
    ifstream jsonfile(filePath);
    if (!jsonfile.is_open()) {
        cout << "ERROR: " << filePath << " not found!" << endl;
        return;
    }
    // Fixed: direction was wrong in your snippet
    jsonfile >> data;
    jsonfile.close();

    json end = json::array();

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].contains("name")) {
            string currentName = data[i]["name"];
            auto it = find(dupe.begin(), dupe.end(), currentName);
            if (it == dupe.end()) {
                dupe.push_back(currentName);
                end.push_back(data[i]);
            }
        }
    }

    ofstream outfile(finalfile);
    if (outfile.is_open()) {
        outfile << end.dump(4);
        outfile.close();
        cout << "Duplicates removed. Final count: " << end.size() << endl;
    }
}

int main() {
    // Pipeline:
    // 1. Filter NSFW -> clean_json
    // 2. Filter Lang -> clear_source
    // 3. Filter Dupes -> dupe_remove

    // Adjust paths if your files are in a different folder
    dupe_remove("finalfile.json", "final_nondupe.json");

    cout << "Process Complete. Hahahhaha!" << endl;
    return 0;
}