#include "CMySmartPointer.h"

template <class T>
CMySmartPointer<T>::CMySmartPointer(T* pcPointer) {
    pc_pointer = pcPointer;
    refCounter = new CRefCounter();
    refCounter -> iAdd();
}

template <class T>
CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer<T>& other){
    pc_pointer = other.pc_pointer;
    refCounter = other.refCounter;
    refCounter -> iAdd();
}

template <class T>
CMySmartPointer<T>::~CMySmartPointer() {
    if(refCounter -> iDec() == 0) {
        delete pc_pointer;
        delete refCounter;
    }
}

template <class T>
T& CMySmartPointer<T>::operator*() {
    return *pc_pointer;
}

template <class T>
T* CMySmartPointer<T>::operator->() {
    return pc_pointer;
}

template <class T>
CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer<T>& other){
    if (this != &other) {
        if (refCounter->iGet() == 1) {
            delete pc_pointer;
            delete refCounter;
        }
        pc_pointer = other.pc_other;
        refCounter = other.refCounter;
        refCounter->iAdd();
    }
    return *this;
}