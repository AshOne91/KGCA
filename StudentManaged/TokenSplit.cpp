#include "TokenSplit.h"

void Split(const std::string& s, const std::string& delim, LinkedList<std::string>& result)
{
    size_t pos = 0;
    std::string temp = s;
    std::string token;
    while ((pos = temp.find(delim)) != std::string::npos) {
        token = temp.substr(0, pos);
        result.push_back(token);
        temp.erase(0, pos + delim.length());
    }
}