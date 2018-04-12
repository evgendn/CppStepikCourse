#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>

void eraseSpaces(std::string& line);
std::string derivative(std::string polynomial);
void splitToItems(std::string polinom, std::map<int, int>& items);
std::pair<int, int> parseToPair(std::string item);
std::string buildString(std::map<int, int>& items);

int main()
{
    std::string line("  -3*x^3  - x^2 + x  -10 +5*x     - x^2");
    eraseSpaces(line);
    std::cout << derivative(line) << std::endl;
}

void eraseSpaces(std::string& line) {
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
}

std::string derivative(std::string polynomial) {
    std::map<int, int> items;
    splitToItems(polynomial, items);
    return (std::string)"";
}

void splitToItems(std::string polinom, std::map<int, int>& items) {
    std::regex re("([\+-]?)(([0-9]{0,})(\\*?)x((\\^[0-9]{1,})?)|[0-9]{0,})");
    std::sregex_token_iterator iter(polinom.begin(), polinom.end(), re);
    std::sregex_token_iterator end;
    for (iter; iter != end; ++iter) {
        std::cout << *iter << " ";
        auto tmp = parseToPair(*iter);
        if (items[tmp.first] == tmp.second) {
            items[tmp.first] += tmp.second;
        } else {
            items[tmp.first] = tmp.second;
        }
    }
    std::cout << std::endl;
}

std::pair<int, int> parseToPair(std::string item) {
    std::pair<int, int> result;

    return result;
}

std::string buildString(std::map<int, int>& items){
    return (std::string)"";
}
