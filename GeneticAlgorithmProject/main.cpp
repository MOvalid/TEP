#include <iostream>
#include <vector>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"

template <class T>
void printVector(const std::vector<T>& vector);

void printStatistics(const double& result, const double& optimum);

void printSeparator();

void createAndRun(CKnapsackProblem& cKnapsackProblem, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& howManyOnes, const double& optimum);
void createAndRun(const std::string& filePath, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& howManyOnes, const double& optimum);
void createAndRun(CKnapsackProblem& cKnapsackProblem, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& optimum);
void createAndRun(const std::string& filePath, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& optimum);

int main() {

    double optimum;

    CSolution result;

    std::vector<double> myValues{3,4,5,6};
    std::vector<double> myWeights{2,3,4,5};


    optimum = 9;
    printSeparator();
    try {
        CKnapsackProblem firstProblem(7, myValues, myWeights);
        createAndRun(firstProblem, 10,  0.1, 0.6, 50, optimum);
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }

    printSeparator();

    optimum = 295;
    createAndRun(R"(C:\Users\trine\CLionProjects\TEP_Projekt2\DataSets\test2)", 10, 0.1, 0.6, 50, optimum);

    printSeparator();

    optimum = 9147;


    try {
        CKnapsackProblem thirdProblem(R"(C:\Users\trine\CLionProjects\TEP_Projekt2\DataSets\thardTest)");
        createAndRun(thirdProblem, 100, 0.004, 0.99, 10000, 0.1, optimum);
        printSeparator();
        createAndRun(thirdProblem, 100, 0.004, 0.99, 10000, 0.05, optimum);
        printSeparator();
        createAndRun(thirdProblem, 100, 0.004, 0.99, 10000, 0.07, optimum);
        printSeparator();
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }


    optimum = 1514;

    try {
        CKnapsackProblem fourthProblem(R"(C:\Users\trine\CLionProjects\TEP_Projekt2\DataSets\thardTest2)");
        createAndRun(fourthProblem, 100, 0.004, 0.99, 10000, 0.1, optimum);
        printSeparator();
        createAndRun(fourthProblem, 100, 0.004, 0.99, 10000, 0.05, optimum);
        printSeparator();
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }

    optimum = 2697;

    try{
        CKnapsackProblem fifthProblem(R"(C:\Users\trine\CLionProjects\TEP_Projekt2\DataSets\thardTest3)");
        createAndRun(fifthProblem, 200, 0.004, 0.99, 20000, 0.1, optimum);
        printSeparator();
        createAndRun(fifthProblem, 200, 0.004, 0.99, 20000, 0.05, optimum);
        printSeparator();
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }


    return 0;
}

template <class T>
void printVector(const std::vector<T>& vector){
    for(const auto &it : vector){
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void printStatistics(const double& result, const double& optimum){
    if(result > 0) {
        std::cout << "Result: " << result << "  Optimum: " << optimum << std::endl;
        std::cout << "Percent optimum: " << (double) result / optimum * 100 << "%" << std::endl << std::endl;
    } else {
        std::cout << "NO OPTIMAL SOLUTION FOUND" << std::endl << std::endl;;
    }
}

void printSeparator(){
    std::cout << "-----------------------\n" << std::endl;
}

void createAndRun(CKnapsackProblem& cKnapsackProblem, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& howManyOnes, const double& optimum){
    try {
        CGeneticAlgorithm algorithm(cKnapsackProblem);
        CSolution result = algorithm.run(sizeOfPopulation, mutationProb, crossingProb, howManyIteration, howManyOnes);
        result.printSolution();
        printStatistics(result.getFitness(), optimum);
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
}


void createAndRun(const std::string& filePath, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& howManyOnes, const double& optimum){
    try {
        CKnapsackProblem problem(filePath);
        createAndRun(problem, sizeOfPopulation, mutationProb, crossingProb, howManyIteration, howManyOnes, optimum);
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
}

void createAndRun(CKnapsackProblem& cKnapsackProblem, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& optimum){
    try {
        CGeneticAlgorithm algorithm(cKnapsackProblem);
        CSolution result = algorithm.run(sizeOfPopulation, mutationProb, crossingProb, howManyIteration);
        result.printSolution();
        printStatistics(result.getFitness(), optimum);
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
}


void createAndRun(const std::string& filePath, const unsigned int& sizeOfPopulation, const double& mutationProb, const double& crossingProb, unsigned int howManyIteration, const double& optimum){
    try {
        CKnapsackProblem problem(filePath);
        createAndRun(problem, sizeOfPopulation, mutationProb, crossingProb, howManyIteration,  optimum);
    } catch (std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
}

