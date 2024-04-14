#include <iostream>
#include <utility>
#include "CTab.h"

CTab::CTab(): s_name(DEFAULT_NAME), size(DEFAULT_SIZE), tab(new int[DEFAULT_SIZE]){
    std::cout << "bezp: '" << s_name << "'" << std::endl;
}

CTab::CTab(std::string sName, unsigned int iTableLen): s_name(std::move(sName)), tab(new int[iTableLen]), size(iTableLen){
    std::cout << "parametr: '" << s_name << "'" << std::endl;
}

CTab::CTab(const CTab& pcOther): s_name(pcOther.s_name + "_copy"), size(pcOther.size), tab(new int[pcOther.size]){
    this -> vCopyTab(pcOther.tab,pcOther.size);
    std::cout << "kopiuj: '" << s_name << "'" << std::endl;
}

CTab::CTab(CTab&& pcOther) noexcept: s_name(std::move(pcOther.s_name + "_move")), tab(pcOther.tab), size(pcOther.size)
{
    pcOther.tab = nullptr;
    pcOther.size = 0;
    pcOther.s_name = "";
    std::cout << "Przenoszenie : '" << s_name << "'" << std::endl;
}

CTab::~CTab(){
    std::cout << "usuwam: '" << s_name << "'" << std::endl;
    if (tab != nullptr) delete[] tab;;
}

unsigned int CTab::getSize(){
    return size;
}


std::string CTab::getName(){
    return s_name;
}

void CTab::vSetName(std::string sName){
    s_name = std::move(sName);
}

bool CTab::bSetNewSize(unsigned int iTableLen){
    if (size == iTableLen){
        std::cout << "Podany nowy rozmiar jest taki sam, jak dotychczas i wynosi " << size << std::endl;
    } else {
        int* newTab = new int[iTableLen];
        for (int i = 0; i < iTableLen; i++){
            newTab[i] = tab[i];
        }
        delete[] tab;
        this -> tab = newTab;
        this -> size = iTableLen;
    }
    return true;
}

CTab* CTab::pcClone(){
    return new CTab(*this);
}

void CTab::vPrint(){
    for(int i = 0; i < size; i++){
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}


void CTab::vSetValueAt(unsigned int iOffset, int iNewValue){
    if(iOffset >= size){
        std::cout << " Podany indeks jest nieprawidlowy!!!" << std::endl;
    } else {
        tab[iOffset] = iNewValue;
    }
}

/** Przed wywołaniem funkcji należy zmienić odpowiednio rozmiar tablicy dla wywoływanego obiektu. */
bool CTab::vCopyTab(const int* otherTab, unsigned int otherTabSize) {
    return vCopyTab(otherTab, 0, otherTabSize);
}

/** Przed wywołaniem funkcji należy zmienić odpowiednio rozmiar tablicy dla wywoływanego obiektu. */
bool CTab::vCopyTab(const int* otherTab, unsigned int beginIndex, unsigned int otherTabSize) {
    if (otherTabSize > 0 && beginIndex+otherTabSize <= this->size) {
        for (int i = beginIndex; i < beginIndex+otherTabSize; i++) {
            tab[i] = otherTab[i-beginIndex];
        }
        return true;
    }
    return false;
}


//CTab CTab::operator=(const CTab& pcOther) {
//    if (this != &pcOther) {
//        s_name = pcOther.s_name;
//        size = pcOther.size;
//        delete[] tab;
//        tab = new int[size];
//        this->vCopyTab(pcOther.tab, pcOther.size);
//    }
//
//    return std::move(*this);
//}
//
//CTab CTab::operator=(CTab&& pcOther) noexcept {
//    if(this != &pcOther){
//        delete[] tab;
//
//        tab = pcOther.tab;
//        size = pcOther.size;
//        s_name = pcOther.s_name;
//
//        pcOther.tab = nullptr;
//        pcOther.size = 0;
//        pcOther.s_name = "";
//    }
//    return std::move(*this);
//}


CTab& CTab::operator=(const CTab& pcOther) {
    if(this != &pcOther) {
        s_name = pcOther.s_name;
        size = pcOther.size;
        delete[] tab;
        tab = new int[size];
        this->vCopyTab(pcOther.tab, pcOther.size);
    }
    return *this;
}

CTab& CTab::operator=(CTab&& pcOther) noexcept {
    if(this != &pcOther){
        delete[] tab;

        tab = pcOther.tab;
        size = pcOther.size;
        s_name = pcOther.s_name;

        pcOther.tab = nullptr;
        pcOther.size = 0;
        pcOther.s_name = "";
    }
    return *this;
}


CTab CTab::operator+(const CTab& pcOther) const {
    CTab result(s_name+ "+" + pcOther.s_name,size + pcOther.size);
    result.vCopyTab(tab, size);
    result.vCopyTab(pcOther.tab, size, pcOther.size);
    return std::move(result);
}

CTab CTab::operator+(CTab&& pcOther) const {
    CTab result(s_name + "+" + pcOther.s_name, size + pcOther.size);
    result.vCopyTab(tab, size);
    result.vCopyTab(pcOther.tab, size, pcOther.size);

    pcOther.tab = nullptr;
    pcOther.size = 0;
    pcOther.s_name = "";

    return std::move(result);
}

CTab CTab::operator+(CTab& pcOther) && {
    CTab result(s_name + "+" + pcOther.s_name, size + pcOther.size);
    result.vCopyTab(tab, size);
    result.vCopyTab(pcOther.tab, size, pcOther.size);

    tab = nullptr;
    size = 0;
    s_name = "";

    return std::move(result);
}
