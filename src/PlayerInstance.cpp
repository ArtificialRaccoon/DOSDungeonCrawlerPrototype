#include "PlayerInstance.h"
#include "Character.h"

PlayerInstance::PlayerInstance()
{
    //Character 1
    Character testOne;
    //testOne.Name = "ValueOne";
    testOne.Portrait = 0;
    Party.push_back(testOne);

    //Character 2
    Character testTwo;
    //testTwo.Name = "ValueTwo";
    testTwo.Portrait = 1;
    Party.push_back(testTwo);

    //Character 3
    Character testThree;
    //testThree.Name = "ValueThr";
    testThree.Portrait = 2;
    Party.push_back(testThree);

    //Character 4
    Character testFour;
    //testFour.Name = "ValueFou";
    testFour.Portrait = 3;
    Party.push_back(testFour);
}

PlayerInstance::~PlayerInstance()
{

}
