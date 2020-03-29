// crypt
// by Mariusz Lisowski for Coders School
// encrypting and decrypting an input message

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::srand;
using std::random_shuffle;
using std::pair;
using std::make_pair;
using std::vector;
using std::time;
using std::find_if;
using std::ifstream;
using std::exit;

// alias
using  KeyPairs = vector<pair<char, char> >;

// direction of crypting
enum CryptDir { decrypt, encrypt };

// input methods
enum InputMethod { text = 1, console, file };

// printable characters range (ASCII)
static const int printMin = 32;
static const int printMax = 126;

// functions
KeyPairs generateKey();
string crypt(const string &, const KeyPairs &, bool);
void showKey(KeyPairs const &);
string inputMenu();
string fileRead(string);
string consoleRead();
void exitProg();

// ******************************* MAIN BEGIN *******************************
int main(int argc, char** argv) {
   string message;

   /// input
   // only one argument
   if (argc == 2)
      message = fileRead(argv[1]);
   // no arguments
   else if (argc == 1)
      message = inputMenu();
   // two or more arguments
   else {
      cout << "Too many arguments!" << endl;
      cout << "USAGE: ./crypt filename" << endl;
      exit(EXIT_FAILURE);
   }

   /// generate
   auto key = generateKey();

   /// show (for debug purposes)
   // showKey(key);

   /// encrypt
   auto cypher = crypt(message, key, encrypt);

   /// decrypt
   auto result = crypt(cypher, key, decrypt);

   /// output
   cout << "Message : " << message << endl;
   cout << "Cypher  : " << cypher << endl;
   cout << "Result  : " << result << endl;

   exitProg();

   return 0;
}
// *******************************  MAIN END  *******************************

// generatting the key
KeyPairs generateKey() {
   // populating the containter with printable characters
   vector<char> printable;
   for (char ch = printMin; ch <= printMax; ch++)
      printable.push_back(ch);

   // shuffling this container
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

// outputting the key (debug purposes)
void showKey(KeyPairs const &key) {
   for (auto it : key)
      cout << it.first << " -> " << it.second << endl;
}

// choosing an input method
string inputMenu() {
   int choice;
   string message, filename;

   // menu
   cout << "#CYPHER YOUR TEXT#" << endl;
   cout << "\nWhat's your input?" << endl;
   cout << "1. Example" << endl;
   cout << "2. Console" << endl;
   cout << "3. File" << endl << "> ";

   // choice
   cin >> choice;
   switch (choice) {
      case text:
         message = "Hello, Coders School!";
         break;
      case console:
         message = consoleRead();
         break;
      case file:
         cout << "\nEnter file name: ";
         cin >> filename;
         message = fileRead(filename);
         break;
      default:
         cout << "\nIncorrect choice!\n";
         exitProg();
   }
   cout << endl;

   return message;
}

// console input method
string consoleRead() {
   string message;

   cout << "\nEnter the message: ";
   cin.ignore();
   getline(cin, message);

   return message;
}

// file input method
string fileRead(string filename) {
   string message, line;
   ifstream file;

   // opening the file
   file.open(filename);
   if (!file.is_open()) {
      cout << "File opening error!" << endl;
      exitProg();
   }

   // reading the file
   while (!file.eof()) {
      getline(file, line);
      message += line;
   }

   // closing the file
   file.close();

   return message;
}

void exitProg() {
    cout << "\nPress ENTER to exit" << endl;
    cin.clear();
    cin.sync();
    cin.get();
    exit(EXIT_FAILURE);
}
