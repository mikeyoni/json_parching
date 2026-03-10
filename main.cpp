#include "json.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using json = nlohmann::json;

// Changed parameter name to 'filePath' to avoid confusion
void clean_json(string filePath) {

    // 1. Open the source file
    ifstream jsonfile(filePath);
    if (!jsonfile.is_open()) {
        cout << "ERROR: " << filePath << " not found!" << endl;
        return; // 'void' functions just use return;
    }

    json data; // Renamed from 'index' to avoid clashing with the parameter
    jsonfile >> data;
    jsonfile.close();

    // 2. Prepare the clean list
    json onlysource = json::array();

    // 3. Filter Loop
    for (int i = 0; i < data.size(); i++)
    {
        // Check if nsfw key exists and is 0
        // Added the missing ) here --------------------v
        if (data[i].contains("nsfw") && data[i]["nsfw"] == 0) {
            onlysource.push_back(data[i]["sources"]);
        }
    }
    // 4. Save the output
    string filename = "onlysource.json";
    ofstream outfile(filename);

    if (outfile.is_open()) {
        outfile << onlysource.dump(4);
        outfile.close();

        cout << "------------------------------------" << endl;
        cout << "SUCCESS!" << endl;
        cout << "File saved at: " << filesystem::absolute(filename) << endl;
        cout << "Items kept:    " << onlysource.size() << " / " << data.size() << endl;
        cout << "------------------------------------" << endl;
    } else {
        cout << "ERROR: Could not create the output file!" << endl;
    }
}

int main() {
    // Make sure you pass the correct filename here!
    // Usually, your source is "index.json"
    clean_json("non_nsfw.json");
	cout<< "hahahhaha!" << endl;

    return 0;
}