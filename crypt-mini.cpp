#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<char, char> > generateKey() {
   vector<char> printable;
   for (char ch = 32; ch <= 126; ch++)
      printable.push_back(ch);
   srand(unsigned(time(0)));
   random_shuffle(printable.begin(), printable.end());
   vector<pair<char, char> > charsPairs;
   for (char ch = 32; ch <= 126; ch++)
      charsPairs.push_back(make_pair(ch, printable.at(int(ch) - 32)));
   return charsPairs;
}

string crypt(const string &input, const vector<pair<char, char> > &key, bool enc) {
   string output;
   vector<pair<char, char> >::const_iterator it;
   for (auto ch : input) {
      it = find_if(key.begin(), key.end(),
         [&ch,&enc](const pair<char, char>& element) {
         if (enc) return element.first == ch;
         else return element.second == ch;});
      if (enc)
         output += it->second;
      else
         output += it->first;
   }
   return output;
}

int main() {
   string message = "Hello, Coders School!";
   auto key = generateKey();
   auto cypher = crypt(message, key, 1);
   auto result = crypt(cypher, key, 0);
   cout << "Message : " << message << endl;
   cout << "Cypher  : " << cypher << endl;
   cout << "Result  : " << result << endl;
   return 0;
}
