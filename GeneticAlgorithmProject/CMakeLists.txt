cmake_minimum_required(VERSION 3.24)
project (TEP_Projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(TEP_Projekt2 main.cpp CGeneticAlgorithm.cpp CGeneticAlgorithm.h CIndividual.cpp CIndividual.h CItem.cpp CItem.h CKnapsackProblem.cpp CKnapsackProblem.h CSolution.cpp CSolution.h CRandomizer.h MyException/UncorrectLoadLineException.h MyException/UncorrectFunctionParameterException.h CHelper.h MyException/InvalidArgumentConstructorException.h)
