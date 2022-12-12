#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

/* some useful constants */

#define INPUT_CHAR ">> "
#define LATERAL "----"
#define HASH 99999989

/* global variables */
int _N, _M;
vector<int> _path;
int _largestSize = 0;
long long res = 0;



/* reads the user's input and saves the values */
void readInput(){
    //cout << INPUT_CHAR;
    cin >> _N;
    //cout << INPUT_CHAR;
    cin >> _M;
    _path.reserve(_N);
    for (int i = 0; i < _N; i++){
        int u;
        //cout << INPUT_CHAR;
        cin >> u;
        if (u > _largestSize){
            if(_N - i >= u)
                _largestSize = u;
            else if(_N - i >= _largestSize)
                _largestSize = _N - i;
        }
        _path.push_back(u);
    }
}

void printArray(vector<int> arr){
    for (int i = 0; i < (int) arr.size(); i++){
        if (i == (int) arr.size() - 1)
            cout << arr[i] << ";";
        else
            cout << arr[i] << ", ";
    }
    cout << endl;
}

bool spaceForSize(vector<int> emptySpaces, vector<int> filledSpaces, int index, int sizeOfSquare){
    if ((int) emptySpaces.size() - index < sizeOfSquare || emptySpaces[index] == 0)
        return false;
    else { 
        if (sizeOfSquare != 1){
            if (sizeOfSquare == 2 && emptySpaces[0] == 2 && emptySpaces[1] == 2 && emptySpaces[2] == 1 && emptySpaces[3] == 1){
                 
            }
            for (int i = index; i < index + sizeOfSquare; i++){//
                if (emptySpaces[i] < sizeOfSquare || filledSpaces[i] > filledSpaces[index])
                    return false;
            }
        }
    }
    return true;
}

vector<int> remove_size(vector<int> arr, int index, int size){
    for (int i = index; i < index + size; i++){
        arr[i] -= size;
    }
    return arr;
}

vector<int> add_size(vector<int> arr, int index, int size){
    for (int i = index; i < index + size; i++){
        arr[i] += size;
    }
    return arr;
}

void printRectangle(vector<int> emptySpaces, vector<int> filledSpaces){
    for (int i = 0; i < (int) emptySpaces.size(); i++){
        for (int j = 0; j < filledSpaces[i]; j++){
            cout << "1\t";
        }
        for (int k = 0; k < emptySpaces[i]; k++){
            cout << "0\t";
        }
        cout << endl;
    }
    cout << endl;//
}

bool canPutSquares(vector<int> emptySpaces, vector<int> filledSpaces){
    for (int i = 0; i < (int) emptySpaces.size() - 1; i++){
        if (emptySpaces[i] == 0 && i == (int) emptySpaces.size() - 2)
            return false;
        else if (emptySpaces[i] <= emptySpaces[i + 1] && filledSpaces[i] >= filledSpaces[i + 1] && emptySpaces[i] > 1)
            return true;
    }
    return false;
}

int getLine(vector<int> emptySpaces, vector<int> filledSpaces){
    auto min = min_element(filledSpaces.begin(), filledSpaces.end());
    int line = (int) distance(filledSpaces.begin(), min);
    if (filledSpaces[line] != 0){
        while (emptySpaces[line] == 0 ){
            line++;
        }
    }
    return line;
}

bool empty(vector<int> emptySpaces){
    for (int i = 0; i < (int) emptySpaces.size(); i++){
        if (emptySpaces[i] != 0)
            return false;
    }
    return true;
}

/* main algorithm */
long long calculate_path(vector<int> emptySpaces, vector<int> filledSpaces, int l){
    long long figs = 0;

    printRectangle(emptySpaces, filledSpaces);

    if (!canPutSquares(emptySpaces, filledSpaces)){
        //cout << " --> nao cabem mais quadrados quando: \n";
        //cout << "  empty spaces: ";
        //printArray(emptySpaces);
        //cout << "  filled spaces: ";
        //printArray(filledSpaces);
        cout << "done;\n\n";
        return 1;
    } else {
        int line = getLine(emptySpaces, filledSpaces);
        //cout << "<< << << << line: " << line + 1 << " >> >> >> >>" << endl;
        //cout << "empty spaces: ";
        //printArray(emptySpaces);
        //cout << "filled spaces: ";
        //printArray(filledSpaces); 

        if (emptySpaces[line] == 0 && filledSpaces[line] == 0){
            //resize vectors
            vector<int> newVector1(emptySpaces.begin() + 1, emptySpaces.end());
            emptySpaces.resize(emptySpaces.size() - 1);
            emptySpaces = newVector1;

            vector<int> newVector2(filledSpaces.begin() + 1, filledSpaces.end());
            filledSpaces.resize(filledSpaces.size() - 1);
            filledSpaces = newVector2;
        }

        for (int size = _largestSize; size > 0; size--){
            if (spaceForSize(emptySpaces, filledSpaces, line, size)){
                vector<int> updatedEmptySpaces = remove_size(emptySpaces, line, size);
                vector<int> updatedFilledSpaces = add_size(filledSpaces, line, size);
                figs += calculate_path(updatedEmptySpaces, updatedFilledSpaces, line);
            }
        }
    }
    return figs;
}

/* main function */
int main(){
    /* reads the user's input */
    readInput();

    /* guideline to show all information when program runs */
    cout << "retângulo de dimensao: " << _N << " x " << _M << endl;
    cout << endl;

    /* the core algorithm */
    cout << endl;
    cout << "->" << "max size: " << _largestSize << endl << endl;
    //cout << "resultado final: ";
    vector<int> emptySpaces(_path);
    vector<int> filledSpaces;
    filledSpaces.resize(emptySpaces.size());
    fill(filledSpaces.begin(), filledSpaces.end(), 0);
    if (empty(emptySpaces))
        cout << 0 << endl;
    else
        cout << calculate_path(emptySpaces, filledSpaces,_largestSize) << endl;

    return 0;
}