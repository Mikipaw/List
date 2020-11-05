

#include "List.h"


int Interface();

int main() {
    Interface();
    //List<char> lst(5);
    return 0;
}



int Interface(){
    List lst(6);
    lst.Insert(0, 4);
    lst.Insert(1, 3);
    lst.Insert(1, 8);
    lst.Insert(0, 2);
    lst.Dump();
    return 1;
};
