#ifndef LISTA5_TEP_CREFCOUNTER_H
#define LISTA5_TEP_CREFCOUNTER_H


class CRefCounter {

public:
    CRefCounter();
    int iAdd();
    int iDec();
    int iGet();

private:
    int i_count;
};


#endif //LISTA5_TEP_CREFCOUNTER_H
