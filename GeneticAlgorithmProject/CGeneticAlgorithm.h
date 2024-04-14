#ifndef TEP_PROJEKT2_CGENETICALGORITHM_H
#define TEP_PROJEKT2_CGENETICALGORITHM_H

#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include "CSolution.h"

#define RANDOM_NUMBER_OF_ONES 10101010


class CGeneticAlgorithm {

private:
    CKnapsackProblem cKnapsackProblem;

    int getRandomIndexOfParent(std::vector<CIndividual>& population) const;

    void checkParameters(const double& mutationProb, const double& crossingProb, const double& howManyOnes) const;

    void fillInitialPopulation(std::vector<CIndividual>& population, const unsigned int& sizeOfPopulation, const double& howManyOnes) const;
    void executeCrossing(std::vector<CIndividual>& population, std::vector<CIndividual>& newPopulation) const;
    void executeMutation(std::vector<CIndividual>& population, const double& mutationProb) const;
    void findTheBestCurrentSolution(std::vector<CIndividual>& population, CIndividual& theBestSolution,
                                    double& theBestFitness) const;
    void setKnapsackProblem(const CKnapsackProblem& knapsackProblem);
    CGeneticAlgorithm() = delete;

public:
    explicit CGeneticAlgorithm(const CKnapsackProblem& knapsackProblem);

    ~CGeneticAlgorithm();


    CSolution run(const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb,
                    unsigned int howManyIterations) const;

    CSolution run(const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb,
                    unsigned int howManyIterations, const double& howManyOnes) const;


};


#endif //TEP_PROJEKT2_CGENETICALGORITHM_H
