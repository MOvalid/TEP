#ifndef TEP_PROJEKT2_CKNAPSACKPROBLEM_H
#define TEP_PROJEKT2_CKNAPSACKPROBLEM_H

#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <list>
#include "CIndividual.h"
#include "CItem.h"

class CIndividual;

class CKnapsackProblem {

private:

    double knapsackSize;
    std::vector<CItem> items;

    void loadVectorOfItems(std::fstream& sourceFile, std::string& line, std::smatch &matcher,
                      std::vector<CItem>& loadedItems) const;
    void loadItem(std::smatch& matcher, std::string& line, std::vector<CItem>& loadedValues) const;

    unsigned int loadPositiveInteger(std::smatch& matcher, std::string& line) const;
    double loadPositiveDouble(std::smatch& matcher, std::string& line) const;
    double calculateFitness(const std::vector<int>& genotype) const;
    bool setNewValues(const double& newKnapsackSize, const std::vector<CItem>& newItems);
    bool loadProblem(const std::string& filePath);
    bool setItems(const std::vector<CItem>& newItems);
    bool setItems(const std::vector<double>& values, const std::vector<double>& weights);
//    bool setItems(std::list<double>& values, std::list<double>& weights);
//    bool setItems(const double* values, const double* weights, const unsigned int& size);
    bool setKnapsackSize(const double& newKnapsackSize);
    CKnapsackProblem();

public:
    CKnapsackProblem(const double& newKnapsackSize, const std::vector<double>& values, const std::vector<double>& weights);
//    CKnapsackProblem(double newKnapsackSize, std::list<double>& values, std::list<double>& weights);
//    CKnapsackProblem(double newKnapsackSize, double* values, double* weights, unsigned int sizeOfItems);
    CKnapsackProblem(const double& newKnapsackSize, const std::vector<CItem>& items);
    explicit CKnapsackProblem(const std::string& filePath);
    ~CKnapsackProblem();

    double getKnapsackSize() const;
    unsigned int getNumberOfItems() const;

    friend class CIndividual;
    friend class CGeneticAlgorithm;


};



#endif //TEP_PROJEKT2_CKNAPSACKPROBLEM_H
