#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

/* some useful constants */

#define INPUT_CHAR ">> "
#define LATERAL "----"

/* global variables */
int _N, _M;
vector<int> _path;
int _largestSize = 0;
long res = 0;

/* some useful functions */
int min(int v, int k){
    return (v <= k ? v : k);
}

/* reads the user's input and saves the values */
void readInput(){
    cout << INPUT_CHAR;
    cin >> _N;
    cout << INPUT_CHAR;
    cin >> _M;
    _path.reserve(_N);
    for (int i = 0; i < _N; i++){
        int u;
        cout << INPUT_CHAR;
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

/* prints the vertical line between squares */
string vertical(int column){
    string res = "|";
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < column; j++){
            res += "    |";
        }

    return res;
}

/* guideline to help visualize the parced rectangle */
void print_rectangle(vector<int> arr){
    cout << "figura:\n\n";
    int size = arr.size();
    for (int i = 0; i < size + 1; i++){
        cout << "|";
        for (int j = 0; j < arr[i]; j++){
            cout << LATERAL;
            cout << "|";
        }

        if (i != (int) arr.size()){
            cout << endl;
            cout << vertical(arr[i]);
            cout << endl;
        }
        else {
            for (int j = 0; j < _M; j++){
                cout << LATERAL;
                cout << "|";
            }
        }
    }
    cout << endl;
}

bool spaceForSize(vector<int> emptySpaces, vector<int> filledSpaces, int index, int sizeOfSquare){
    if ((int) emptySpaces.size() - index < sizeOfSquare)
        return false;
    else { 
        if (sizeOfSquare != 1){
            for (int i = index; i < (int) emptySpaces.size() - 1; i++){
                if (emptySpaces[i] < sizeOfSquare || filledSpaces[i + 1] > filledSpaces[i])
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

bool canPutSquares(vector<int> emptySpaces, vector<int> filledSpaces){
    for (int i = 0; i < (int) emptySpaces.size() - 1; i++){
        if (emptySpaces[i] > 1){
            if (i == 4){
                cout << "free spaces: " << emptySpaces[i] << "\tfilled spaces: " << filledSpaces[i] << endl;
                cout << "free spaces: " << emptySpaces[i + 1] << "\tfilled spaces: " << filledSpaces[i + 1] << endl;
            }
            if (emptySpaces[i + 1] - filledSpaces[i] >= emptySpaces[i])
                return true;
            else if (emptySpaces[i] <= emptySpaces[i + 1] && filledSpaces[i] == filledSpaces[i + 1])
                return true;
        }
    }
    return false;
}


/* main algorithm */
long calculate_path(vector<int> emptySpaces, vector<int> filledSpaces, int l){
    long figs = 0;

    if (!canPutSquares(emptySpaces, filledSpaces)){
        cout << "\e[1m -> nao cabem mais quadrados quando: \e[m\n";
        cout << "empty spaces: ";
        printArray(emptySpaces);
        cout << "filled spaces: ";
        printArray(filledSpaces);
        return 1;
    } else {
        auto min = min_element(filledSpaces.begin(), filledSpaces.end());
        int line = (int) distance(filledSpaces.begin(), min);
        cout << "\e[1m" << "<< << << << line: " << line + 1 << " >> >> >> >>" << "\e[m" << endl;
        cout << "min element: arr[" << line << "]" <<  endl;
        cout << "empty spaces: ";
        printArray(emptySpaces);
        cout << "filled spaces: ";
        printArray(filledSpaces); 

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
                //cout << "quadrado tamanho: " << size << endl;
                figs += calculate_path(updatedEmptySpaces, updatedFilledSpaces, line);
            }    
            else{
                cout << "nao ha espaco para quadrado de tamanho: " << size << endl;
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

    /* prints the rectangle */
    print_rectangle(_path);

    /* the core algorithm */
    cout << endl;
    cout << "\e[1m" << "max size: " << "\e[m" << _largestSize << endl << endl;
    cout << "resultado final: ";
    vector<int> emptySpaces(_path);
    vector<int> filledSpaces;
    filledSpaces.resize(emptySpaces.size());
    fill(filledSpaces.begin(), filledSpaces.end(), 0);
    cout << calculate_path(emptySpaces, filledSpaces,_largestSize) << endl;

    return 0;
}