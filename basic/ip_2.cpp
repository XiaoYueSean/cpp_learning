#include <iostream>

using namespace std;
const int MAX = 3;

int main(){
    int var[MAX] = {1, 10, 200};
    int *ptr;

    ptr = var;
    for (int i = 0; i < MAX; i++){
        cout << "var[" << i << "]内存地址为: ";
        cout << ptr << endl;

        cout << "var[" << i << "]的值为 ";
        cout << *ptr << endl;

        ptr++;

    }
    return 0;
}