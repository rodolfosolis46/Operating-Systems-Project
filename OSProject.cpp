

#include <iostream>
#include <string>

#include "auth.h"


using namespace std;

int main()
{
    cout << "Booting up ArtOS..." << endl;

    if (authenticateUser())
    {
        cout << "ArtOS booted successfully!" << endl;
    }
    else
    {
        cout << "Error: Failed to boot ArtOS." << endl;
        return 1;
    }
    return 0;
}



