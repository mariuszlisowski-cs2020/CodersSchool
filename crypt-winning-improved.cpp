// crypt
// for Coders School
// winning solution of Krzysztof Szytko
// improved & tested (all unit tests passed)
// improvements:
// ~ ASCII char constants instead of numbers
// ~ arguments passed as 'const &' (Return Value Optimisation)
// ~ no use of STL's 'vector' ('string' only)

#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <random>

using namespace std;

const char ASCII_BEGIN = ' ';
const char ASCII_END = '~';

string generateKey() {
    string key;
    key.assign(ASCII_END - 1 - ASCII_BEGIN, ' ');
    iota(key.begin(), key.end(), ASCII_BEGIN);
    shuffle(key.begin(), key.end(), mt19937{ random_device{}() });
    return key;
}

string encrypt(const string &input, const string &key) {
    string message = input;
    transform(message.begin(), message.end(), message.begin(),
        [&key](char c) {
            return (c >= ASCII_BEGIN && c < ASCII_END - 1) ? key[c - ASCII_BEGIN] : c; });
    return message;
}

string decrypt(const string &input, const string &key) {
    string message = input;
    transform(message.begin(), message.end(), message.begin(),
        [&key](char c) {
            return (c >= ASCII_BEGIN && c < ASCII_END - 1) ? key.find(c) + ASCII_BEGIN : c; });
    return message;
}

int main() {
    string message = "Hello, Coders School!";

    auto key = generateKey();
    auto cypher = encrypt(message, key);
    auto result = decrypt(cypher, key);

    cout << "Message : " << message << endl;
    cout << "Cypher  : " << cypher << endl;
    cout << "Result  : " << result << endl;

    return 0;
}
