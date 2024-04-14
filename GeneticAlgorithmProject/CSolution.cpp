#include <iostream>
#include "CSolution.h"

CSolution::CSolution(const std::vector<int> &genotype, const double& fitness): fitness(fitness) {
    this->genotype = std::vector<int>();
    this->genotype.reserve(genotype.size());
    std::copy(genotype.cbegin(), genotype.cend(),
              std::back_inserter(this->genotype));
}

CSolution::CSolution(): fitness(0), genotype(std::vector<int>()) {}

CSolution::CSolution(const CSolution& other): fitness(other.fitness){
    this->genotype = std::vector<int>();
    this->genotype.reserve(other.genotype.size());
    std::copy(other.genotype.cbegin(), other.genotype.cend(),
              std::back_inserter(this->genotype));
}

CSolution::CSolution(CSolution&& other) noexcept : fitness(other.fitness){
    this->genotype = std::vector<int>();
    genotype.swap(other.genotype);
    other.fitness = 0.0;
}


CSolution& CSolution::operator=(const CSolution& other){
    if(this != &other){
        std::vector<int>().swap(this->genotype);
        std::copy(other.genotype.cbegin(), other.genotype.cend(),
                  std::back_inserter(this->genotype));
        this->fitness = other.fitness;
    }
    return *this;
}

CSolution& CSolution::operator=(CSolution&& other) noexcept {
    if(this != &other){
        std::vector<int>().swap(this->genotype);
        this->genotype.swap(other.genotype);
        this->fitness = other.fitness;
        other.fitness = 0;
    }
    return *this;
}

std::vector<int> CSolution::getGenotype() const {
    std::vector<int> result = std::vector<int>();
    std::copy(genotype.cbegin(), genotype.cend(),
              std::back_inserter(result));
    return std::move(result);
}

double CSolution::getFitness() const {
    return fitness;
}

void CSolution::printSolution() const {
    std::cout << "FITNESS: " << fitness << std::endl;
    for(const auto& it : genotype){
        std::cout << it << " ";
    }
    std::cout << std::endl;
}
