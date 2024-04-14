#include <string>
#include <iostream>
#include <regex>
#include <list>
#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include "MyException/UncorrectLoadLineException.h"
#include "CHelper.h"
#include "MyException/InvalidArgumentConstructorException.h"


CKnapsackProblem::CKnapsackProblem() = default;

CKnapsackProblem::CKnapsackProblem(const std::string& filePath){
    this->items = std::vector<CItem>();
    this->loadProblem(filePath);
}

CKnapsackProblem::CKnapsackProblem(const double& newKnapsackSize, const std::vector<double>& values, const std::vector<double>& weights){
    if(newKnapsackSize <= 0.0) {
        throw InvalidArgumentConstructorException(
                CHelper::generateErrorMessage("1 positive double (knapsack size)", std::to_string(newKnapsackSize) + "\n"));
    } else if (values.size() != weights.size()){
        throw InvalidArgumentConstructorException(
                CHelper::generateErrorMessage("2 equal integers (vectors sizes)", std::to_string(values.size()) + " " + std::to_string(weights.size()) + "\n"));
    } else {
        this->knapsackSize = newKnapsackSize;
        this->setItems(values, weights);
    }
}

//CKnapsackProblem::CKnapsackProblem(double newKnapsackSize, std::list<double>& values, std::list<double>& weights){
//    if(newKnapsackSize <= 0.0) {
//        throw InvalidArgumentConstructorException(
//                CHelper::generateErrorMessage("1 positive double", std::to_string(newKnapsackSize) + "\n"));
//    } else if (values.size() != weights.size()){
//        throw InvalidArgumentConstructorException(CHelper::generateErrorMessage("2 equal integers", std::to_string(values.size()) + " " + std::to_string(weights.size()) + "\n"));
//    } else {
//        this->knapsackSize = newKnapsackSize;
//        this->setItems(values, weights);
//    }
//}
//
//CKnapsackProblem::CKnapsackProblem(double newKnapsackSize, double* values, double* weights, unsigned int sizeOfItems){
//    if(newKnapsackSize <= 0.0) {
//        throw InvalidArgumentConstructorException(
//                CHelper::generateErrorMessage("1 positive double", std::to_string(newKnapsackSize) + "\n"));
//    } else {
//        this->knapsackSize = newKnapsackSize;
//        this->setItems(values, weights, sizeOfItems);
//    }
//}

CKnapsackProblem::CKnapsackProblem(const double& newKnapsackSize, const std::vector<CItem>& items){
    if(newKnapsackSize <= 0.0) {
        throw InvalidArgumentConstructorException(
                CHelper::generateErrorMessage("1 positive double (knapsack size)", std::to_string(newKnapsackSize) + "\n"));
    } else {
        this->knapsackSize = newKnapsackSize;
        this->items = std::vector<CItem>();
        std::copy(items.cbegin(), items.cend(),
                  std::back_inserter(this->items));
    }
}

CKnapsackProblem::~CKnapsackProblem() {
    std::vector<CItem>().swap(items);
}


bool CKnapsackProblem::setItems(const std::vector<CItem>& newItems){
    if(&(this->items) != &newItems){
        std::vector<CItem>().swap(items);
        std::copy(newItems.cbegin(), newItems.cend(),
                  std::back_inserter(this->items));
        this->items = newItems;
        return true;
    }
    return false;
}


bool CKnapsackProblem::setItems(const std::vector<double>& values, const std::vector<double>& weights){
    if(values.size() == weights.size()) {
        std::vector<CItem>().swap(items);
        auto values_iter = values.cbegin();
        for(const auto& weights_iter : weights){
            this->items.emplace_back(*values_iter, weights_iter);
            values_iter++;
        }
        return true;
    }
    return false;

}

//bool CKnapsackProblem::setItems(const double* values, const double* weights, const unsigned int& size){
//    std::vector<CItem>().swap(items);
//    items.reserve(size);
//    for(int i = 0; i < size; i++){
//        this->items.emplace_back(values[i], weights[i]);
//    }
//    return true;
//}
//
//bool CKnapsackProblem::setItems(std::list<double>& values, std::list<double>& weights){
//    if(values.size() == weights.size()) {
//        std::vector<CItem>().swap(items);
//        items.reserve(values.size());
//        auto values_iter = values.cbegin();
//        for(const auto& weights_iter : weights){
//            this->items.emplace_back(*values_iter, weights_iter);
//            values_iter++;
//        }
//        return true;
//    }
//    return false;
//
//}

bool CKnapsackProblem::loadProblem(const std::string& filePath) {
    std::fstream sourceFile;
    sourceFile.open(filePath, std::ios::in);

    if(sourceFile.is_open()){
        std::string line;
        if(std::getline(sourceFile, line)){
            std::smatch matcher;
            if(std::regex_match(line, std::regex("[[:blank:]]*[+]?(([[:digit:]]+([.]?[[:digit:]]*)?)|([.][[:digit:]]+))[[:blank:]]*"))) {

                double loadedKnapsackSize = loadPositiveDouble(matcher, line);

                if (loadedKnapsackSize <= 0.0)
                    throw UncorrectLoadLineException(
                            CHelper::generateErrorMessage("1 positive double (loaded knapsack size)", std::to_string(loadedKnapsackSize)));

                std::vector<CItem> loadedItems;

                loadVectorOfItems(sourceFile, line, matcher, loadedItems);
                setNewValues(loadedKnapsackSize, loadedItems);


            } else {
                throw UncorrectLoadLineException(CHelper::generateErrorMessage("1 positive double (loaded knapsack size)", line));
            }
        } else {
            sourceFile.close();
            return false;
        }
        sourceFile.close();
        return true;
    }
    return false;
}

void CKnapsackProblem::loadVectorOfItems(std::fstream& sourceFile, std::string& line, std::smatch& matcher, std::vector<CItem>& loadedItems) const {
    while(std::getline(sourceFile, line)){
        if(std::regex_match(line, std::regex("[[:blank:]]*[+]?(([[:digit:]]+([.]?[[:digit:]]*)?)|([.][[:digit:]]+))[[:blank:]]+[+]?(([[:digit:]]+([.]?[[:digit:]]*)?)|([.][[:digit:]]+))[[:blank:]]*"))){
            loadItem(matcher, line, loadedItems);
        } else if (std::regex_match(line, std::regex("[[:blank:]]*"))){
        } else {
            throw UncorrectLoadLineException(CHelper::generateErrorMessage("2 positive doubles (value weight)", line));
        }
    }
}


void CKnapsackProblem::loadItem(std::smatch& matcher, std::string& line, std::vector<CItem>& loadedItems) const {
    double loadedValue, loadedWeight;

    loadedValue = loadPositiveDouble(matcher, line);

    loadedWeight = loadPositiveDouble(matcher, line);

    loadedItems.emplace_back(loadedValue, loadedWeight);
}


unsigned int CKnapsackProblem::loadPositiveInteger(std::smatch& matcher, std::string& line) const {
    std::regex_search(line, matcher, std::regex("[+]?[[:digit:]]+([.]?[0]*)?"));
    int result = std::stoi(matcher.str(0));
    line = matcher.suffix().str();
    return result;
}


double CKnapsackProblem::loadPositiveDouble(std::smatch& matcher, std::string& line) const {
    std::regex_search(line, matcher, std::regex("[+]?[[:digit:]]+([.]?[[:digit:]]*)?"));
    double result = std::stod(matcher.str(0));
    line = matcher.suffix().str();
    return result;
}



bool CKnapsackProblem::setNewValues(const double& newKnapsackSize, const std::vector<CItem>& newItems){
    if(&newItems != &items) {
        std::vector<CItem>().swap(items);
        std::copy(newItems.cbegin(), newItems.cend(),
                  std::back_inserter(items));
        knapsackSize = newKnapsackSize;
        return true;
    }
    return false;
}

bool CKnapsackProblem::setKnapsackSize(const double& newKnapsackSize){
    if(newKnapsackSize > 0.0){
        this->knapsackSize = newKnapsackSize;
        return true;
    }
    return false;
}

double CKnapsackProblem::getKnapsackSize() const {
    return this->knapsackSize;
}

unsigned int CKnapsackProblem::getNumberOfItems() const {
    return this->items.size();
}

double CKnapsackProblem::calculateFitness(const std::vector<int>& genotype) const {
    double valuesOfItems = 0.0, weightsOfItems = 0.0;
    auto item_Iter = this->items.cbegin();
    for(auto genotype_Iter = genotype.cbegin(); genotype_Iter != genotype.cend(); genotype_Iter++, item_Iter++) {
        valuesOfItems += *genotype_Iter * (*item_Iter).getValue();
        weightsOfItems += *genotype_Iter * (*item_Iter).getWeight();
        if(weightsOfItems > this->knapsackSize){
            return 0.0;
        }
    }
    return valuesOfItems;
}


