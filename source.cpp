#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

bool parseCSVLine(const string& line, string& title, string& author, string& year,  string& isbn) {
    size_t start = 0;
    int field = 0;
    string values[4];

    for (size_t i = 0; i <= line.size(); ++i) {
        if (i == line.size() || line[i] == ',') {
            if (field >= 4) return false;
            values[field++] = line.substr(start, i - start);
            start = i + 1;
        }
    }

    if (field != 4) return false;

    title = values[0];
    author = values[1];
    year = values[2];
    isbn = values[3];

    return true;
}

int main() {
    ifstream file("books.csv");
    if (!file.is_open()) {
        cerr << "ERROR!\n";
        return 1;
    }

    set<string> uniqueAuthors;
    string line;

    try {
        getline(file, line); 

        while (getline(file, line)) {
            string title, author, year, isbn;

            if (!parseCSVLine(line, title, author, year, isbn)) {
                throw runtime_error("Wrong format of csv");
            }

            uniqueAuthors.insert(author);
        }

        file.close();

        ofstream out("authors.json");
        if (!out.is_open()) {
            cerr << "Error with creating file json\n";
            return 1;
        }

        out << "[\n";

        bool first = true;
        for (auto it = uniqueAuthors.begin(); it != uniqueAuthors.end(); ++it) {
            if (!first) out << ",\n";
            first = false;

            out << "  \"" << *it << "\"";
        }

        out << "\n]";
        out.close();

        cout << "Ready! authors.json is created\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}