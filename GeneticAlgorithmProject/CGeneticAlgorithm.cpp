#include "CGeneticAlgorithm.h"
#include "CRandomizer.h"
#include "CHelper.h"
#include "MyException/UncorrectFunctionParameterException.h"

CGeneticAlgorithm::CGeneticAlgorithm(const CKnapsackProblem& knapsackProblem){
    this->cKnapsackProblem = knapsackProblem;
}

CGeneticAlgorithm::~CGeneticAlgorithm() = default;

void CGeneticAlgorithm::setKnapsackProblem(const CKnapsackProblem& knapsackProblem){
    this->cKnapsackProblem = knapsackProblem;
}

CSolution CGeneticAlgorithm::run(const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb,
                                   unsigned int howManyIterations) const {
    return run(sizeOfPopulation, mutationProb, crossingProb, howManyIterations, RANDOM_NUMBER_OF_ONES);
}


CSolution CGeneticAlgorithm::run(const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb,
                                   unsigned int howManyIterations, const double& howManyOnes) const {

    if(cKnapsackProblem.getNumberOfItems() == 0) return std::move(CSolution(std::vector<int>(), 0));

    checkParameters(mutationProb, crossingProb, howManyOnes);

    std::vector<CIndividual> population, newPopulation;

    fillInitialPopulation(population, sizeOfPopulation, howManyOnes);

    CIndividual theBestSolution;

    double theBestFitness = 0.0;

    while(howManyIterations > 0){

        while(newPopulation.size() < population.size()) {
            if (CRandomizer::randZeroToOne() < crossingProb) {
                executeCrossing(population, newPopulation);
            } else {
                executeMutation(population, mutationProb);
            }
        }

        CHelper::swapsVectorsAndEraseSecond(population, newPopulation);

        findTheBestCurrentSolution(population, theBestSolution, theBestFitness);

        --howManyIterations;
    }

    theBestSolution.calculateFitness(cKnapsackProblem);

    return std::move(CSolution(theBestSolution.genotype, theBestSolution.getFitness()));
//    return {theBestSolution.genotype, theBestSolution.getFitness()};
}

int CGeneticAlgorithm::getRandomIndexOfParent(std::vector<CIndividual>& population) const {
    int firstCandidate = -1, secondCandidate = -1;
    while (firstCandidate == secondCandidate){
        firstCandidate = CRandomizer::getRandomInt(0,population.size() - 1);
        secondCandidate = CRandomizer::getRandomInt(0,population.size() - 1);
    }
    if(population[firstCandidate].calculateFitness(cKnapsackProblem) >= population[secondCandidate].calculateFitness(cKnapsackProblem)){
        return firstCandidate;
    } else {
        return secondCandidate;
    }
}

void CGeneticAlgorithm::fillInitialPopulation(std::vector<CIndividual>& population, const unsigned int& sizeOfPopulation, const double& howManyOnes) const {
    if (howManyOnes == RANDOM_NUMBER_OF_ONES){
        for (int i = 0; i < sizeOfPopulation; i++) {
            population.emplace_back(cKnapsackProblem.getNumberOfItems());
        }
    } else {
        for (int i = 0; i < sizeOfPopulation; i++) {
            population.emplace_back(cKnapsackProblem.getNumberOfItems(),(unsigned int) (howManyOnes * cKnapsackProblem.getNumberOfItems()));
        }
    }
}

void CGeneticAlgorithm::executeCrossing(std::vector<CIndividual>& population, std::vector<CIndividual>& newPopulation) const {
    int firstParent = -1, secondParent = -1;
    while (firstParent == secondParent) {
        firstParent = getRandomIndexOfParent(population);
        secondParent = getRandomIndexOfParent(population);
    }
    std::pair<CIndividual, CIndividual> newChildren = population[firstParent].makeCrossing(
            population[secondParent]);

    newPopulation.push_back(std::move(newChildren.first));
    if(newPopulation.size() < population.size()) {
        newPopulation.push_back(std::move(newChildren.second));
    }
}

void CGeneticAlgorithm::executeMutation(std::vector<CIndividual>& population, const double& mutationProb) const {
    for(auto &individual : population) {
        for(int indexOfMutation = 0; indexOfMutation < individual.getGenotypeSize(); indexOfMutation++){
            if(CRandomizer::randZeroToOne() < mutationProb){
                individual.makeMutation(indexOfMutation);
            }
        }
    }
}

void CGeneticAlgorithm::findTheBestCurrentSolution(std::vector<CIndividual>& population, CIndividual& theBestSolution, double& theBestFitness) const {
    double currentFitness;
    for(auto &individual : population){
        currentFitness = individual.calculateFitness(cKnapsackProblem);
        if(theBestFitness < currentFitness){
            theBestFitness = currentFitness;
            theBestSolution = individual;
        }
    }
}

void CGeneticAlgorithm::checkParameters(const double& mutationProb, const double& crossingProb,
                                        const double& howManyOnes) const {

    if(mutationProb < 0. || mutationProb > 1.){
        throw UncorrectFunctionParameterException("Invalid argument: MutationProb (" + std::to_string(mutationProb) + ")\n");
    }
    if(crossingProb < 0. || crossingProb > 1.){
        throw UncorrectFunctionParameterException("Invalid argument: CrossingProb (" + std::to_string(crossingProb) + ")\n");
    }
    if(howManyOnes != RANDOM_NUMBER_OF_ONES && (howManyOnes < 0. || howManyOnes > 1.)){
        throw UncorrectFunctionParameterException("Invalid argument: howManyOnes (" + std::to_string(howManyOnes) + ")\n");
    }
}
