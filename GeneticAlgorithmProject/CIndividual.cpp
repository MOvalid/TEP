#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include "CRandomizer.h"
#include <iostream>

CIndividual::CIndividual() {
    genotype = std::vector<int>();
    fitness = -1.0;
}

CIndividual::CIndividual(const unsigned int& size) {
    this->generateGenotype(size);
    fitness = -1.0;
}

CIndividual::CIndividual(const CIndividual& other): fitness(other.fitness){
    genotype = std::vector<int>();
    std::copy(other.genotype.begin(), other.genotype.end(),
              std::back_inserter(genotype));
}

CIndividual::CIndividual(CIndividual&& other) noexcept: fitness(other.fitness){
    genotype = std::vector<int>();
    genotype.swap(other.genotype);
    other.fitness = 0;
}

CIndividual::CIndividual(const unsigned int& size, const unsigned int& howMuchOnes) {
    if(howMuchOnes > size){
        this->generateGenotype(size, size * CRandomizer::randZeroToOne());
    } else {
        this->generateGenotype(size, howMuchOnes);
    }
    fitness = -1.0;
}


CIndividual::~CIndividual() {
    std::vector<int>().swap(genotype);
}

void CIndividual::generateGenotype(const unsigned int& size) {
    std::vector<int>().swap(this->genotype);
    this->genotype.reserve(size);
    for(int i = 0; i < size; i++){
        genotype.emplace_back(CRandomizer::getRandomInt(0, 1));
    }
}

void CIndividual::generateGenotype(const unsigned int& size, const unsigned int& howMuchOnes) {
    std::vector<int>().swap(this->genotype);
    this->genotype.reserve(size);
    int i = 0;
    for(i; i < howMuchOnes; i++){
        genotype.emplace_back(1);
    }
    for(i; i < size; i++){
        genotype.emplace_back(0);
    }
    CRandomizer::shuffleVector(genotype);
}

void CIndividual::makeMutation(const unsigned int& index) {
    if (index < genotype.size()){
        genotype[index] = (genotype[index] + 1) % 2;
        fitness = -1.0;
    }
}

double CIndividual::getFitness() const {
    return fitness;
}

int CIndividual::getGenotypeSize() const {
    return genotype.size();
}


double CIndividual::calculateFitness(const CKnapsackProblem& knapsackProblem) {
    if (fitness < 0.0) {
        fitness = knapsackProblem.calculateFitness(genotype);
    }
    return fitness;
}


std::pair<CIndividual, CIndividual> CIndividual::makeCrossing(const CIndividual& other) const {
    CIndividual child1, child2;
    child1.genotype.reserve(other.genotype.size());
    child2.genotype.reserve(other.genotype.size());
    unsigned int pivotIndex = (CRandomizer::getRandomInt(0, genotype.size()-1));
    unsigned int i = 0;
    for(i; i <= pivotIndex; i++){
        child1.genotype.emplace_back(this->genotype[i]);
        child2.genotype.emplace_back(other.genotype[i]);
    }
    for(i; i < genotype.size(); i++){
        child1.genotype.emplace_back(other.genotype[i]);
        child2.genotype.emplace_back(this->genotype[i]);
    }
    return std::move(std::make_pair(child1,child2));
}

void CIndividual::printGenotype() const {
    for(int it : genotype){
        std::cout << it << " ";
    }
    std::cout << std::endl;
}


CIndividual& CIndividual::operator=(const CIndividual& other){
    if(this != &other){
        std::vector<int>().swap(this->genotype);
        *this = CIndividual(other);
    }
    return *this;
}

CIndividual& CIndividual::operator=(CIndividual&& other) noexcept {
    if(this != &other){
        std::vector<int>().swap(this->genotype);
        other.genotype.swap(this->genotype);
        this->fitness = other.fitness;
        other.fitness = 0;
    }
    return *this;
}
