// crypt (argument input)
// by Mariusz Lisowski for Coders School
// encrypting and decrypting an input message

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// alias
using  KeyPairs = vector<pair<char, char> >;

// direction of crypting
enum CryptDir { decrypt, encrypt };

// printable characters range (ASCII)
static const int printMin = 32;
static const int printMax = 126;

// functions
KeyPairs generateKey();
string crypt(const string &, const KeyPairs &, bool);
void showKey(KeyPairs const &);

// ******************************* MAIN BEGIN *******************************
int main(int argc, char** argv) {
   string message;

   /// input
   // only one argument
   if (argc == 2)
      message = static_cast<string>(argv[1]);
   // no arguments
   else if (argc == 1)
      message = "Hello, Coders School!";
   // two or more arguments
   else {
      cout << "Too many arguments!" << endl;
      cout << "USAGE: ./crypt <message>" << endl;
      exit(EXIT_FAILURE);
   }

   /// generate
   auto key = generateKey();

   /// encrypt
   auto cypher = crypt(message, key, encrypt);

   /// decrypt
   auto result = crypt(cypher, key, decrypt);

   /// output
   cout << "Message : " << message << endl;
   cout << "Cypher  : " << cypher << endl;
   cout << "Result  : " << result << endl;

   return 0;
}
// *******************************  MAIN END  *******************************

// generatting the key
KeyPairs generateKey() {
   // populating the containter with printable characters
   vector<char> printable;
   for (char ch = printMin; ch <= printMax; ch++)
      printable.push_back(ch);

   // shuffling printable characters container
   srand(unsigned(time(0)));
   random_shuffle(printable.begin(), printable.end());

   // generating pairs of printable characters and their counterparts
   KeyPairs charsPairs;
   for (char ch = printMin; ch <= printMax; ch++)
      charsPairs.push_back(make_pair(ch, printable.at(int(ch) - printMin)));

   return charsPairs;
}

// encrypting/decrypting an input
string crypt(const string &input, const KeyPairs &key, bool enc) {
   string output;
   KeyPairs::const_iterator it;
   for (auto ch : input) {
      // scanning the input string and
      // finding a corresponding character in a key
      it = find_if(key.begin(), key.end(),
         [&ch,&enc](const pair<char, char>& element) {
         if (enc)
            return element.first == ch;
         else
            return element.second == ch;
         }
      );
      // adding it depending on a crypting direction
      if (enc)
         output += it->second;
      else
         output += it->first;
   }
   return output;
}
