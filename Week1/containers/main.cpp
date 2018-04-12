#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>

void eraseSpaces(std::string& line);
std::string derivative(std::string polynomial);
void splitToItems(std::string polinom, std::map<int, int>& items);
void incrementalDerivative(std::map<int, int>& items);
std::pair<int, int> parseToPair(std::string item);
std::string buildString(std::map<int, int>& items);
std::string buildItem(const std::pair<int, int>& item);

int main()
{
    std::string line("-3*x^3 + x - 1");
    eraseSpaces(line);
    std::cout << "Polinom: " << line << std::endl;
    std::cout << derivative(line) << std::endl;
}

void eraseSpaces(std::string& line) {
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
}

std::string derivative(std::string polynomial) {
    std::map<int, int> items;
    splitToItems(polynomial, items);
    incrementalDerivative(items);
    return buildString(items);
}

void splitToItems(std::string polinom, std::map<int, int>& items) {
    std::regex re("([\+-]?)(([0-9]{0,})(\\*?)x((\\^[0-9]{1,})?)|[0-9]{1,})");
    auto iter = std::sregex_token_iterator (polinom.begin(), polinom.end(), re);
    auto end = std::sregex_token_iterator();
    for (iter; iter != end; ++iter) {
        auto tmp = parseToPair(*iter);
        if (items[tmp.first] == tmp.second) {
            items[tmp.first] += tmp.second;
        } else {
            items[tmp.first] = tmp.second;
        }
    }
}

std::pair<int, int> parseToPair(std::string item) {
    std::string::size_type index;
    int power = 1;
    int coeff = 1;

    index = item.find("x");
    if (index != std::string::npos) {
        int powerIndex = item.find("^");
        if (powerIndex != std::string::npos) {
            power = std::stoi(item.substr(powerIndex + 1));
        }

        int coeffIndex = item.find("*");
        if (coeffIndex != std::string::npos) {
            coeff = std::stoi(item.substr(0, coeffIndex));
        }
    } else {
        coeff = std::stoi(item);
        power = 0;
    }
    std::cout << coeff << " " << power << std::endl;
    return std::make_pair(power, coeff);
}

void incrementalDerivative(std::map<int, int> &items) {
    for (auto& kv: items) {
        kv.second *= kv.first;
    }
}

std::string buildString(std::map<int, int>& items){
    std::string result;
    for (auto& kv: items) {
        std::cout << "*" << kv.second << " ^" << kv.first - 1 << std::endl;
    }
    return (std::string)"";
}

std::string buildItem(const std::pair<int, int>& item) {

}
