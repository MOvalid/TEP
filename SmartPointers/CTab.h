#ifndef TEST5_CTAB_H
#define TEST5_CTAB_H

#include <iostream>

#define DEFAULT_NAME "DEFAULT"
#define DEFAULT_SIZE 16

class CTab{

private:
    std::string s_name;
    int* tab;
    unsigned int size;

    bool vCopyTab(const int* otherTab, unsigned int otherTabSize);
    bool vCopyTab(const int* otherTab, unsigned int beginIndex, unsigned int endIndex);

public:
    CTab();
    CTab(std::string sName, unsigned int iTableLen);
    CTab(const CTab& pcOther);
    CTab(CTab&& pcOther) noexcept;
    ~CTab();
    void vSetName(std::string sName);
    bool bSetNewSize(unsigned int iTableLen);
    std::string getName();
    unsigned int getSize();
    CTab* pcClone();
    void vPrint();
    void vSetValueAt(unsigned int iOffset, int iNewValue);
//    CTab operator=(const CTab& pcOther);
//    CTab operator=(CTab&& pcOther) noexcept;
    CTab& operator=(const CTab& pcOther);
    CTab& operator=(CTab&& pcOther) noexcept;
    CTab operator+(const CTab& pcOther) const;
    CTab operator+(CTab&& pcOther) const;
    CTab operator+(CTab& pcOther) &&;
};


#endif //TEST5_CTAB_H