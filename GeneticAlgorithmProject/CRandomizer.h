#ifndef TEP_PROJEKT2_CRANDOMIZER_H
#define TEP_PROJEKT2_CRANDOMIZER_H

#include <random>

class CRandomizer{
public:

    static double randZeroToOne(){
        return getRandomDouble(0.0, 1.0);
    }

//// This function generates a double within the range [min, max]
    static double getRandomDouble(const double& min, const double& max){
        std::uniform_real_distribution<double>dist(min, max);
        return dist(rd);
    }

//// This function generates a integer within the range [min, max]
    static int getRandomInt(const int& min, const int& max){
        std::uniform_int_distribution<int>dist(min,max);
        return dist(rd);
    }

    template<class T>
    static void shuffleVector(std::vector<T>& vector){
        int i, j, size = vector.size();
        for (i = 0; i < size - 1; i++){
            j = i + CRandomizer::getRandomInt(0,size - i - 1);
            std::swap(vector[i], vector[j]);
        }
    }

private:
    inline static std::random_device rd;

};
#endif //TEP_PROJEKT2_CRANDOMIZER_H
