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
bool coeffIsNegative(std::string item);
std::string buildString(std::map<int, int>& items);
void buildItem(const std::pair<int, int>& item, std::string& result);
void addSignBeforeNumber(const std::pair<int, int> &item, std::string& result);

int main()
{
    std::string line("100*x-20*x");
    eraseSpaces(line);
    std::cout << "Polynome: " << line << std::endl;
    std::cout << "Result: " << derivative(line) << std::endl;
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

void splitToItems(std::string polynome, std::map<int, int>& items) {
    std::regex re("([\+-]?)(([0-9]{0,})(\\*?)x((\\^[0-9]{1,})?)|[0-9]{1,})");
    auto iter = std::sregex_token_iterator (polynome.begin(), polynome.end(), re);
    auto end = std::sregex_token_iterator();
    for (iter; iter != end; ++iter) {
        auto tmp = parseToPair(*iter);
        items[tmp.first] += tmp.second;
    }
}

std::pair<int, int> parseToPair(std::string item) {
    std::string::size_type index;
    int power = 1;
    int coeff = 1;

    index = item.find("x");
    if (index != std::string::npos) {
        int coeffIndex = item.find("*");
        if (coeffIndex == std::string::npos) {
            if (coeffIsNegative(item)) {
                coeff = -1;
            }
        } else {
            coeff = std::stoi(item.substr(0, coeffIndex));
        }

        int powerIndex = item.find("^");
        if (powerIndex != std::string::npos) {
            power = std::stoi(item.substr(powerIndex + 1));
        }
    } else {
        coeff = std::stoi(item);
        power = 0;
    }
    return std::make_pair(power, coeff);
}

bool coeffIsNegative(std::string item) {
    std::string pattern("[\+-]?");
    std::regex re(pattern);
    std::smatch match;
    std::string result("");
    if (std::regex_search(item, match, re)) {
        result = match.str(0);
    }
    if (result == "-") {
        return true;
    }
    return false;
}

void incrementalDerivative(std::map<int, int> &items) {
    for (auto& kv: items) {
        kv.second *= kv.first;
    }
}

std::string buildString(std::map<int, int>& items){
    std::string result;
    auto riter = items.rbegin();
    for (riter; riter != items.rend(); ++riter) {
        buildItem(std::make_pair(riter->first - 1, riter->second), result);
    }
    return result;
}

void buildItem(const std::pair<int, int>& item, std::string& result) {
    std::string itemAsString;
    if (item.first > 0) {
        addSignBeforeNumber(item, result);
        result.append(std::to_string(item.second));
        result.append("*x");
        if (item.first != 1) {
            result.append("^");
            result.append(std::to_string(item.first));
        }
    } else if (item.first == 0) {
        addSignBeforeNumber(item, result);
        result.append(std::to_string(item.second));
    }
}

void addSignBeforeNumber(const std::pair<int, int>& item, std::string& result) {
    if (result.size()) {
        if (item.second > 0 ) {
            result.append("+");
        }
    }
}
