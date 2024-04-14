#ifndef TEP_PROJEKT2_CSOLUTION_H
#define TEP_PROJEKT2_CSOLUTION_H

#include <vector>

class CSolution {
public:
    CSolution();
    CSolution(const std::vector<int>& genotype, const double& fitness);
    CSolution(const CSolution& other);
    CSolution(CSolution&& other) noexcept;

    std::vector<int> getGenotype() const;
    double getFitness() const;
    void printSolution() const;

    CSolution& operator=(const CSolution& other);
    CSolution& operator=(CSolution&& other) noexcept;

private:
    std::vector<int> genotype;
    double fitness;

};


#endif //TEP_PROJEKT2_CSOLUTION_H
