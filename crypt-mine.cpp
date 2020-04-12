// crypt by Mariusz Lisowski
// all unit tests passed
// bugs fixed: random generator & new line detection

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

vector<pair<char, char> > generateKey() {
    vector<char> printable;
    for (char ch = 32; ch <= 126; ch++)
        printable.push_back(ch);
    random_device rd;
    shuffle(printable.begin(), printable.end(), mt19937(rd()));
    vector<pair<char, char> > charsPairs;
    for (char ch = 32; ch <= 126; ch++)
        charsPairs.push_back(make_pair(ch, printable.at(int(ch) - 32)));
    return charsPairs;
}

string encrypt(const string &input, const vector<pair<char, char> > &key) {
    string output;
    vector<pair<char, char> >::const_iterator it;
    for (auto ch : input) {
        if (ch != '\n') {
            it = find_if(key.begin(), key.end(),
                [&ch](const pair<char, char>& element) {
                    return element.first == ch;});
            output += it->second;
        }
        else
            output += '\n';
    }
    return output;
}

string decrypt(const string &input, const vector<pair<char, char> > &key) {
    string output;
    vector<pair<char, char> >::const_iterator it;
    for (auto ch : input) {
        if (ch != '\n') {
            it = find_if(key.begin(), key.end(),
                [&ch](const pair<char, char>& element) {
                    return element.second == ch;});
            output += it->first;
        }
        else
            output += '\n';
    }
    return output;
}

int main() {
    string message = "Hello, Coders School!";

    // randomness test
    /*
    auto keyOne = generateKey();
    auto cipherOne = encrypt(message, keyOne);
    cout << cipherOne << endl;

    auto keyTwo = generateKey();
    auto cipherTwo = encrypt(message, keyTwo);
    cout << cipherTwo << endl;
    */

    auto key = generateKey();
    auto cypher = encrypt(message, key);
    auto result = decrypt(cypher, key);

    cout << "Message : " << message << endl;
    cout << "Cypher  : " << cypher << endl;
    cout << "Result  : " << result << endl;

    return 0;
}
