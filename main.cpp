#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <filesystem>
using namespace std;

//function to help with folder creation at each run
string getCurrentTimestamp() {
    using namespace chrono;
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm local_tm = *localtime(&t);

    stringstream ss;
    ss << put_time(&local_tm, "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

// Coordinates struct (x, y)
struct Coord {
    int x, y;

    // Comparison operator for sorting in sets and maps
    bool operator<(const Coord& other) const {
        if (y < other.y) {
            return true;  // This coordinate comes first
        } else if (y > other.y) {
            return false;
        } else { // If y values are equal, compare x values
            return x < other.x; // Sort by x when y is the same
        }
    }
};

// Read the board from file
set<Coord> readBoard(const string filename) {
    set<Coord> liveCells;
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        exit(1); // Stop the program
    }
    string line;
    int expectedLength = -1;
    int y = 0;

    // Read from file
    while (getline(file, line)) {
        // Validate line length
        if (expectedLength == -1) {
            expectedLength = line.size();
        } else if (line.size() != expectedLength) {
            cerr << "Inconsistent line length!" << endl;
            exit(1);
        }
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '*') {
                liveCells.insert({x, y});
            } else if (line[x] != '_') {
                cerr << "Invalid character in file at line " << y << ", col " << x << endl;
            }
        }
        ++y;
    }
    return liveCells;
}

// Write board to file cropped
void writeBoard(const set<Coord>& liveCells, const string filename) {
    if (liveCells.empty()) {
        ofstream file(filename); // Create empty file
        return;
    }

    // Find min and max bounds of alive cells to create the smallest board
    int minX = liveCells.begin()->x;
    int maxX = liveCells.begin()->x;
    int minY = liveCells.begin()->y;
    int maxY = liveCells.begin()->y;

    for (const Coord& cell : liveCells) {
        minX = min(minX, cell.x);
        maxX = max(maxX, cell.x);
        minY = min(minY, cell.y);
        maxY = max(maxY, cell.y);
    }
     //output file writing
    ofstream out(filename);
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            bool isAlive = liveCells.count({x, y}) > 0;
            if (isAlive) {
                out << '*';  // living cell
            } else {
                out << '_';  // dead cell
            }
        }
        out << '\n'; // Move to next row
    }
}

// Compute next generation
set<Coord> nextGen(const set<Coord>& current) {
    map<Coord, int> neighborCounts; //using map to count lvie neighbor of each cell

    // Count neighbors for each cell
    for (const Coord& cell : current) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip itself
                Coord neighbor = {cell.x + dx, cell.y + dy};
                neighborCounts[neighbor]++;
            }
        }
    }

    set<Coord> next;
    for (const auto& pair : neighborCounts) {
        const Coord& cell = pair.first;
        int count = pair.second;

        // Apply rules
        if ((current.count(cell) && (count == 2 || count == 3)) || (!current.count(cell) && count == 3)) {
            next.insert(cell);
        }
    }
    return next;
}

int main(int argc, char* argv[]) {
    string inputFile;
    int iterations = 0;
    bool outputAll = false;

    //read command line
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--input" && (i + 1 < argc)) {
            inputFile = argv[++i];
        }
        else if (arg == "--iterations" && (i + 1 < argc))
        {
            iterations = stoi(argv[++i]);
        }
        else if (arg == "--all"){
            outputAll = true;

        }
    }

    //check validity of cmd line
    if (inputFile.empty() || iterations <= 0) {
        cerr << "Example: game_of_life --input <inpiut file> --iterations <n> [--all]" << endl;
        return 1;
    }

    //create dir to store the new files
    string timestamp = getCurrentTimestamp();
    filesystem::path outDir(timestamp);
    if (!filesystem::exists(outDir)) {
        filesystem::create_directory(outDir);
    }

    //start logic
    set<Coord> liveCells = readBoard(inputFile);
    filesystem::path p(inputFile);
    string base = p.stem().string();
    string ext = p.extension().string();

    for (int i = 0; i < iterations; ++i) {
        liveCells = nextGen(liveCells);
        if (outputAll || (i == iterations - 1)) {
            string outputFile = (outDir/ (base + "_" + to_string(i + 1) + ext)).string();
            cout << "Saving: " << outputFile << endl;
            writeBoard(liveCells, outputFile);
        }
    }

    return 0;
}
