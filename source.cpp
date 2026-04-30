#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

bool hasDigit(const string& s) {
    return any_of(s.begin(), s.end(), isdigit);
}

int main() {
    list<string> words;
    string line, word;

    getline(std::cin, line);

    istringstream iss(line);
    while (iss >> word) {
        if (hasDigit(word)) {
            throw string("Word with digits");
        }
        words.push_back(word);
    }

    words.sort([](const string& a, const string& b) {
        return a.size() < b.size();
        });

    for (const auto& w : words) {
        cout << w << "\n";
    }

    return 0;
}