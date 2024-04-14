#ifndef LISTA5_TEP_CMYSMARTPOINTER_H
#define LISTA5_TEP_CMYSMARTPOINTER_H


#include "CRefCounter.h"

template <class T>
class CMySmartPointer {

public:

    CMySmartPointer(T* pcPointer);
    CMySmartPointer(const CMySmartPointer<T>& other);
    ~CMySmartPointer();

    T& operator*();
    T* operator->();
    CMySmartPointer<T>& operator=(const CMySmartPointer<T>& other);

private:
    T* pc_pointer;
    CRefCounter* refCounter;
};

#include "CMySmartPointer.tpp"


#endif //LISTA5_TEP_CMYSMARTPOINTER_H
