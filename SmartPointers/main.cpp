#include <iostream>

#include "CTab.h"
#include "CMySmartPointer.h"

int main() {

    //// CMYSMARTPOINTERS EXAMPLES ////
//    int x = 2;
//    CMySmartPointer<int> staticTest(&x);
//    std::cout << *staticTest << std::endl;

    CMySmartPointer<int> pi1(new int(1));
    CMySmartPointer<int> pi2(new int(2));
    CMySmartPointer<int> pi3(new int(3));

    std::cout << "pi1: " << *pi1 << std::endl;
    std::cout << "pi2: " << *pi2 << std::endl;
    std::cout << "pi3: " << *pi3 << std::endl;

    *pi1 = 2;
    *pi2 = 3;
    *pi3 = 1;

    std::cout << std::endl;
    std::cout << "pi1: " << *pi1 << std::endl;
    std::cout << "pi2: " << *pi2 << std::endl;
    std::cout << "pi3: " << *pi3 << std::endl;


    CMySmartPointer<CMySmartPointer<int>> pi4(new CMySmartPointer<int>(new int(4)));
    std::cout << "pi4: " << *(*pi4) << std::endl << std::endl;


    CMySmartPointer<CTab> pi5(new CTab("cTab1", 10));
    CMySmartPointer<CTab> pi6(new CTab("cTab2", 20));
    CMySmartPointer<CTab> pi7(new CTab("cTab3", 30));

    std::cout << std::endl << "pi5 name: " << pi5->getName() << std::endl;
    std::cout << "pi6 size: " << pi6->getSize() << std::endl;

    for(int i = 0; i < pi7->getSize(); i++){
        pi7->vSetValueAt(i, i);
    }

    std::cout  << std::endl << "pi7: ";
    pi7->vPrint();

    CMySmartPointer<CTab> pi8 = pi7;
    std::cout << "pi8: ";
    pi8->vPrint();

    CMySmartPointer<int> pi9(pi3);
    std::cout << "pi3: " << *pi3 << std::endl;
    std::cout << "pi9: " << *pi9 << std::endl;

    CMySmartPointer<CMySmartPointer<CTab>> pi10(new CMySmartPointer<CTab>(new CTab()));
    std::cout << std::endl;
    std::cout << "pi10 name: " << (*pi10)->getName() << std::endl;
    std::cout << "pi10 size: " << (*pi10)->getSize() << std::endl;
    (*pi10)->vPrint();

    std::cout << std::endl << std::endl << "----- CTAB EXAMPLES -----" << std::endl;

    //// CTAB EXAMPLES ////


    CTab c1("C1", 10);
    CTab c2("C2", 10);
    CTab c3;
    std::cout << std::endl;
    CTab c8 = c2;
    std::cout << std::endl;
    CTab c9(c2);
    std::cout << std::endl;


    for(int i = 0; i < c2.getSize(); i++){
        c1.vSetValueAt(i, -i-1);
        c2.vSetValueAt(i, i+1);
        c3.vSetValueAt(i, 2*i + 1);
        c8.vSetValueAt(i, 2*i);
        c9.vSetValueAt(i, 3*i);
    }

    c1.vPrint();
    c2.vPrint();
    c3.vPrint();
    c8.vPrint();
    c9.vPrint();

    std::cout << std::endl;

    CTab c4 = c1 + c2;
    CTab c5 = c2 + c1;

    std::cout << std::endl;

    c4.vPrint();
    c5.vPrint();

    std::cout << std::endl;

    CTab c6;
    c6 = std::move(c1 + c2 + c3);
    CTab c7 = c1 + (c2 + c3);

    std::cout << c6.getSize() << std::endl;
    std::cout << c7.getSize() << std::endl;

    c6.vPrint();
    c7.vPrint();

    CTab c10;
    c10 = c7 = c6;


    std::cout << std::endl << c6.getSize() << std::endl;
    std::cout << c7.getSize() << std::endl;
    std::cout << c10.getSize() << std::endl << std::endl;


    c6.vPrint();
    c7.vPrint();
    c10.vPrint();

    c1 = std::move(c2);


    std::cout << std::endl << c1.getSize() << std::endl;
    std::cout << c2.getSize() <<std::endl;

    std::cout << std::endl;
    c1.vPrint();
    c2.vPrint();


    return 0;
}
