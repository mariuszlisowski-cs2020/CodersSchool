#include <iostream>
#include <string>

bool isPalindrome(std::string str) {
	size_t i {}, j {str.size() - 1};
	while (i < j) {
		if (std::tolower(str[i++]) != std::tolower(str[j--]))
			return false;
	}
	return true;
}

int main() {
    std::string s;

    std::cout << "Wpisz słowo..." << std::endl;
    std::cout << ": ";
    std::cin >> s;

	if (isPalindrome(s))
		std:: cout << s << " to palindrom" << std::endl;
	else
		std:: cout << s << " to NIE palindrom" << std::endl;


}
