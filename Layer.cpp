//
// Created by Miroslav Parapanov on 2020-12-20.
//

#include "Layer.h"

// Validating ROWS and COLS
bool Layer::validateRowsAndCols(short rowsTemp, short colsTemp) const {
    return rowsTemp > 0 && colsTemp > 0
            &&
            rowsTemp % 2 == 0 && colsTemp % 2 == 0
            &&
            rowsTemp < 100 && colsTemp < 100;
}
// Making validation after setting their values (encapsulating the data in private fields)
void Layer::setRowsAndCols(short rowsTemp, short colsTemp) {
    while(!validateRowsAndCols(rowsTemp, colsTemp)){
        cout << "INVALID rows and cols."<<endl;
        cout << "Please enter greater than zero, not exceeding 100 and even numbers for rows and columns"<<endl;
        cout << "Rows: ";cin >> rowsTemp;cout << "Cols: "; cin >> colsTemp;
    }
    // make the wall transposed
    // it is the same
    //////////////////////////
    // 1 1
    // 2 2   -->   1 2 3 4
    // 3 3         1 2 3 4
    // 4 4
    ///////////////////////////
    if (rowsTemp > colsTemp){
        rows = colsTemp;
        cols = rowsTemp;
    }
    else{
         rows = rowsTemp;
         cols = colsTemp;
    }
    maxBricks = (rows * cols) / 2;
}
// initializing the rectangular (the matrix) with zeros
void Layer::initRectangular() {
    for (short i = 0 ; i < rows ; i++){
        for (short j = 0 ; j < cols ; j++)
            rectangular[i][j] = 0;
    }
}
//Layer constructor with parameters
Layer::Layer(short rowsTemp, short colsTemp):rows(rowsTemp), cols(colsTemp) {
    setRowsAndCols(rowsTemp, colsTemp);
    alreadySetTheMatrix = false;
    rectangular = new short*[rowsTemp];
    for (short i = 0; i < rows; i++) {
        rectangular[i] = new short[cols];
    }
    initRectangular();
}
//copy constructor
Layer::Layer(const Layer& otherLayer) {
    rows = otherLayer.rows;
    cols = otherLayer.cols;
    maxBricks = otherLayer.maxBricks;
    rectangular = new short*[rows];
    if (rectangular)
    for(short i = 0 ; i < rows ; i++)
        rectangular[i] = new short [cols];
    for (short i = 0 ; i < rows; i ++){
        for (short j = 0 ; j < cols; j++)
            rectangular[i][j] = otherLayer.getLayer()[i][j];
    }

}
//Getting the rows
short Layer::getRows() const {
    return rows;
}
//Getting the columns
short Layer::getCols() const {
    return cols;
}
// Getting the matrix
short** Layer::getLayer() const {
    return rectangular;
}
//Destructor for my matrix
Layer::~Layer() {
    for (int i = 0; i < rows; i++) {
        delete[] rectangular[i];
    }
    delete[] rectangular;
}
// One way to print the answer is to overload the operator<<
// No need of this one
ostream& operator<<(ostream& os,const Layer& layer){
    short rowsTemp = layer.getRows();
    short colsTemp = layer.getCols();
    for (short i = 0 ; i < rowsTemp ; i++){
        for(short j = 0 ; j < colsTemp ; j++) {
            os << layer.getLayer()[i][j] << " ";
        }
        cout << endl;
    }
}
// Another way is just to print the wall
void Layer::print()const {
    bool flag[rows][cols] ;
    for (short i = 0 ; i < rows  ; i++){
        for (short j = 0 ;j < cols  ; j++) {
            cout << rectangular[i][j] << " ";
        }
        cout << endl;
    }
}

// ONE brick is only 1x2 (Validating the brick)
bool Layer::validateTheBricks(short** rect) const {
    for(short i = 0 ; i < rows ; i++){
        for(short j = 0 ; j < cols ; j++){
            if (i + 2 < rows && rect[i][j] == rect[i+2][j]) {
                cout << "INVALID brick. One brick is Nx1! (where N is > 2)" << endl;
                cout << "Enter again the values of the matrix !" << endl;
                return false;
            }
            else if (j + 2 < cols && rect[i][j] == rect[i][j+2]){
                cout << "INVALID brick. Found a brick that is 1xM (where M is > 2)" << endl;
                cout << "Enter again the values of the matrix !" << endl;
                return false;
            }
        }
    }
    return true;
}

// filling with values the first wall
void Layer::fillingIn() {
    if (alreadySetTheMatrix){
        cout << "It is not allowed to set another wall on the same wall!" <<endl;
        return;
    }
    cout << "Enter the first wall: " << endl;
    do {
        for (short i = 0; i < rows; i++) {
            for (short j = 0; j < cols; j++) {
                cin >> rectangular[i][j];
                // Validating value in cells
                while (rectangular[i][j] <= 0) {
                    cout << "INVALID value in position! " << i << " " << j << endl;
                    cout << "Please enter greater than zero value in cell with positions " << i << " "
                         << j
                         << ". Press ENTER and then continue filling in the wall" << endl;
                    cin >> rectangular[i][j];
                }
            }
        }
    }
    while (!validateTheBricks(rectangular));
    alreadySetTheMatrix = true;
}
//if there is not zeros in the second wall -- > that means we found a solution
bool Layer:: isFilledSecondLayer()const{
    for (short i = 0 ; i < rows ; i++){
        for(short j = 0; j < cols ; j++) {
            if (rectangular[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}
//my solution of the problem
short Layer::solution(Layer& first, Layer& second, short firstRows,
                      short firstCols, short secondRows, short secondCols) {
    // if we filled the second layer ---> it means we are on the last col and last row
    // so we just print the matrix and return 0 for true
    if (secondCols >= cols -1 && secondRows >= rows - 1){
        return 0;
    }
////////////// REGULATIONS FOR FIRST WALL //////////////
    // getting on the next row for my first wall
    if (firstCols >= cols){
        firstRows += 1;
        firstCols = 0;
    }
    //if we already found two different number --> we change the values in their cells in the first wall
    // to be know which value we changed and skip it
    while(first.getLayer()[firstRows][firstCols] == -1){
        firstCols +=1;
        if (firstCols >= cols){
            firstRows += 1;
            firstCols = 0;
        }
    }
////////////////////////////////////////////////////////

////////////// REGULATIONS FOR SECOND WALL //////////////
    while(second.getLayer()[secondRows][secondCols] != 0 || secondCols >= cols || secondRows >= rows) {
        if(secondCols + 1 >= cols){
            secondRows += 1;
            secondCols = 0;
        }
        else
            secondCols+=1;
    }
/////////////////////////////////////////////////////
    if (firstCols + 1 < cols && first.getLayer()[firstRows][firstCols] != first.getLayer()[firstRows][firstCols + 1]) {
        //put the brick on the positions in the second wall
        second.getLayer()[secondRows][secondCols] = maxBricks;
        second.getLayer()[secondRows][secondCols + 1] = maxBricks;
        short temp1 = first.getLayer()[firstRows][firstCols];
        short temp2 = first.getLayer()[firstRows][firstCols + 1];
        //make it -1 because it needs to be skipped i  the n calling of the recursion
        first.getLayer()[firstRows][firstCols] = -1;
        first.getLayer()[firstRows][firstCols + 1] = -1;
        //if solution returns -1 it means that we start going back
        //to find the best solution
        // that's why im reestablishing the old values of the first wall
        //and making the changed values of the second wall again zeros
        maxBricks -= 1;
        if(solution(first, second, firstRows, firstCols + 2, secondRows, secondCols + 2) == -1){
            //return the zeros that i have changed
            second.getLayer()[secondRows][secondCols] = 0;
            second.getLayer()[secondRows][secondCols + 1] = 0;
            //return the values that i have changed
            first.getLayer()[firstRows][firstCols] = temp1;
            first.getLayer()[firstRows][firstCols + 1] = temp2;
            //return the name of the brick again how it was before i got into the backtracking
            maxBricks += 1;
        }

    }
    if (secondRows + 1 < rows && first.getLayer()[firstRows][firstCols] != first.getLayer()[firstRows + 1][firstCols]) {
        second.getLayer()[secondRows][secondCols] = maxBricks;
        second.getLayer()[secondRows + 1][secondCols] = maxBricks;
        short temp1 = first.getLayer()[firstRows][firstCols];
        short temp2 = first.getLayer()[firstRows + 1][firstCols];
        first.getLayer()[firstRows][firstCols] = -1;
        first.getLayer()[firstRows + 1][firstCols] = -1;
        maxBricks -= 1;
        // ---- // ----- same as upper one
        if(solution( first, second, firstRows, firstCols + 1, secondRows, secondCols + 1) == -1){
            second.getLayer()[secondRows][secondCols] = 0;
            second.getLayer()[secondRows][secondCols + 1] = 0;
            first.getLayer()[firstRows][firstCols] = temp1;
            first.getLayer()[firstRows + 1][firstCols] = temp2;
            maxBricks += 1;
        }
    }
    // after backtracking end we check if the second wall has no zeros in it
    //if it has we return -1 for FALSE
    if (second.isFilledSecondLayer()) {
        return 0;
    }
    else {
        return -1;
    }


}
