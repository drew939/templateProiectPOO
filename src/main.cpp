#include "../headers/meniu.h"

int main() 
{
    Meniu& meniu = Meniu::getInstance();
    meniu.run();
    return 0;
}
