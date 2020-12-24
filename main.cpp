#include <iostream>
#include <iomanip>
#include "Layer.h"

//menu
void mainManu(){
    cout << setw(10)<<"->  " << "WELCOME TO BRICKWORK"<<"  <--"<<setw(10)<<endl;cout << endl;
    cout << "RULES: " <<endl;
    cout << "--> Each brick is 1x2 and it can be put vertical or horizontal" << endl;
    cout << "--> Enter values which are greater than 0 and not exceeding 100 !"<<endl;
    cout << "--> Size of the RECTANGULAR must be NxM where N is number of rows and M is number of columns " << endl;
    cout << "--> N and M must be positive and even numbers and not exceeding 100 ! "<<endl;
    cout << "IMPORTANT RULES : " << "!! ENJOY !!" << endl;cout << endl;

}
int main() {
    mainManu();
    short rows, cols;
    cout << "Please enter ROWS"<<endl;
    cout <<"Rows: " ;cin >> rows;
    cout << "Please enter COLS"<<endl;
    cout <<"Cols: " ;cin >> cols;
    Layer firstLayer(rows, cols);
    Layer secondLayer = firstLayer;
    firstLayer.fillingIn();
    if(secondLayer.solution(firstLayer, secondLayer,0, 0, 0, 0) == 0)
        secondLayer.print();
    else {
        cout << "-1";
    }
    return 0;
}



