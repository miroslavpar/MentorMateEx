//
// Created by Miroslav Parapanov on 2020-12-20.
//

#ifndef MENTORMATETEST_LAYER_H
#define MENTORMATETEST_LAYER_H

using namespace std;

#include <iostream>
#include <sstream>

class Layer {
private:

    short maxBricks; // num of the highest brick --> formula (rows * cols ) ? 2
    bool alreadySetTheMatrix; //if we filled the first wall
    short rows; // rows
    short cols; // columns
    short** rectangular; // wall

private:

    bool isFilledSecondLayer()const; // no zeros in the second wall
    bool validateRowsAndCols(short, short)const; //even, >0 , < 100
    void initRectangular();//all values in the cells are zeros
    bool validateTheBricks(short**)const;//no spanning bricks on 1x3 or 3x1
public:

    Layer() = delete; // not allowed to use default constructor
    Layer(const Layer&);//copy constructor
    Layer(short, short);//constructor with parameters
    ~Layer(); // destructor

public:
    short getRows()const; //getRows
    short getCols()const;// get Cols
    short** getLayer()const;//get the current wall
    void fillingIn();//func to fill the first wall
    void setRowsAndCols(short, short);// setting rows adn cols
    // no need of this just to show that i can overload operators
    friend ostream& operator<<(ostream&, const Layer&); // One way to print the solution

    void print()const; // other way to print the solution

    short solution(Layer&,Layer&,short, short,short,short); // BACKTRACKING
};


#endif //MENTORMATETEST_LAYER_H
