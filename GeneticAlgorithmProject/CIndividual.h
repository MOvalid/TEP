#ifndef TEP_PROJEKT2_CINDIVIDUAL_H
#define TEP_PROJEKT2_CINDIVIDUAL_H

#include <vector>

class CKnapsackProblem;

class CIndividual {

private:
    std::vector<int> genotype;
    double fitness;

    void generateGenotype(const unsigned int& size);
    void generateGenotype(const unsigned int& size, const unsigned int& howMuchOnes);

    void makeMutation(const unsigned int& index);
    std::pair<CIndividual, CIndividual> makeCrossing(const CIndividual& other) const;
    double calculateFitness(const CKnapsackProblem& knapsack);
    CIndividual();

public:
    explicit CIndividual(const unsigned int& size);
    CIndividual(const unsigned int& size, const unsigned int& howMuchOnes);
    CIndividual(const CIndividual& other);
    CIndividual(CIndividual&& other) noexcept ;
    ~CIndividual();
    double getFitness() const ;
    int getGenotypeSize() const ;

    void printGenotype() const;
    CIndividual& operator=(const CIndividual& other);
    CIndividual& operator=(CIndividual&& other) noexcept;

    friend class CKnapsackProblem;
    friend class CGeneticAlgorithm;
};


#endif //TEP_PROJEKT2_CINDIVIDUAL_H
