#include <iostream>

using namespace std;

class Box{
    public:
        double length;
        double breadth;
        double height;

        double getVolume(void);
        void setLength(double len);
        void setBreadth(double bre);
        void setHeight(double hei);
};

double Box::getVolume(void){
    return length * breadth * height;
}

void Box::setBreadth(double bre){
    breadth = bre;
}

void Box::setHeight(double hei){
    height = hei;
}

void Box::setLength(double len){
    length = len;
}

int main(){
    Box box1;
    double volume = 0;

    box1.setBreadth(3);
    box1.setHeight(23);
    box1.setLength(2);

    volume = box1.getVolume();

    cout << "volumn is : "<<volume << endl;
}