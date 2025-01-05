#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // a example program for test
    cout << "This is an example program\nThere are " << argc << " args\n";
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << '\n';
    }
    system("pause");
    return 0;
}
