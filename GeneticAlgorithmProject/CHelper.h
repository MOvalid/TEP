#ifndef TEP_PROJEKT2_CHELPER_H
#define TEP_PROJEKT2_CHELPER_H

#include <string>
#include <vector>

class CHelper{
public:
    static std::string generateErrorMessage(const std::string& inquiriedText, const std::string& foundText){
        return std::move("Invalid argument! \nInquiried: " + inquiriedText + "\nFound: " + foundText + "\n");
    }

    template <class T>
    static void swapsVectorsAndEraseSecond(std::vector<T>& first, std::vector<T>& second){
        first.swap(second);
        second.clear();
    }

};
#endif //TEP_PROJEKT2_CHELPER_H
