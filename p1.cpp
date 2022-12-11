#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

/* some useful constants */

#define INPUT_CHAR ">> "
#define TRUE 1
#define FALSE 0
#define LATERAL "----"

/* global variables */
int _N, _M;
vector<int> _path;
int _largestSize = 0;
long res = 0;


/*

create 2 arrays: 
    1: array with the occupied spaces;
    2: array with the free spaces;

    iterar todas as linhas e prenche-las a comecar com o maximo tamanho possivel e ver se cabe: 
    se couber, criar mais 2 arrays com o espaco livre e ocupado com o novo quadrado e repetir;

    se nao couber, prencher essa linha com um quadrado 1x1 no array dos ocupados e seguir para a proxima

*/




/* some useful functions */
int min(int v, int k){
    return (v <= k ? v : k);
}

int fact(int num){
    if (num == 1 || num == 0)
        return 1;
    else    
        return num * fact(num - 1);
}

int comb(int v, int k){
    return (fact(v) / (fact(k) * fact(v - k)));
}

int perm(int v, int k){
    return (fact(v) / fact(v - k));
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


int count_combinations(int sizeOfSquare, int length, bool tryAllSizes){
    int res = 0;
    int squares = floor(length / sizeOfSquare);
    int max_squares = squares;
    cout << length << "/" << sizeOfSquare << ": " << squares << endl;
    int spaces = length - squares * sizeOfSquare;
    int possibleLocations = spaces + squares;


    if (tryAllSizes){
        // alter this
        cout << "--------------\nTRY ALL SIZES\n -> empty code\n--------------\n";
    } else {
        cout << "tentar so para 1 tamanho" << endl;
        while (squares != 0){
            cout << "possible locations: " << possibleLocations << "; spaces: " << spaces << endl;
            cout << "squares: " << squares << endl;
            res += comb(possibleLocations, spaces);
            cout << "comb = " << comb(possibleLocations, spaces) << endl;
            squares--;
            possibleLocations--;
            spaces += sizeOfSquare;
            possibleLocations += sizeOfSquare;
        }
    }
    return max_squares * res;
}

bool spaceForSize(vector<int> emptySpaces, vector<int> filledSpaces, int index, int sizeOfSquare){
    if ((int) emptySpaces.size() - index < sizeOfSquare)
        return false;
    else{
        for (int i = index; i < (int) emptySpaces.size(); i++){
            if (emptySpaces[i] < sizeOfSquare && filledSpaces[i] <= filledSpaces[index])
                return false;
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

/*
int test_combinations(vector<int> arr, int l, int index){ 
    int margin;
    int res = count_combinations(l, arr[index] + l, false);
    for (int i = l - 1; i < _N - 1; i++){
        margin = arr[i];
        if (margin != 0){
            res += count_combinations(l, margin, true); 
        }
    }
    return res;
}


int test_square_format(vector<int> emptySpaces, vector<int> filledSpaces, int index){
    int figs = 0;

    for (int i = _largestSize; i > 0; i--){
        if (spaceForSize(emptySpaces, filledSpaces, index, i)){
            if (i == 1){
                //FIXME this might be wrong
                return 0;
            }
            vector<int> updatedEmptySpaces = remove_size(emptySpaces, index, i);
            vector<int> updatedFilledSpaces = add_size(filledSpaces, index, i);
            figs++;
            figs+= test_square_format(updatedEmptySpaces, updatedFilledSpaces, index);
        }
        
    }

    return figs;
}
*/

bool canPutSquares(vector<int> emptySpaces, vector<int> filledSpaces){
    for (int i = 0; i < (int) emptySpaces.size() - 1; i++){
        if (emptySpaces[i] > 1 && emptySpaces[i + 1] - filledSpaces[i] >= emptySpaces[i])
            return true;
    }
    return false;
}


/* main algorithm */
long calculate_path(vector<int> emptySpaces, vector<int> filledSpaces, int l){
    long figs = 0;

    cout << "empty spaces: ";
    printArray(emptySpaces);
    cout << "filledSpaces: ";
    printArray(filledSpaces); 

    if (!canPutSquares(emptySpaces, filledSpaces)){
        cout << "nao cabem mais quadrados\n";
        return 1;
    } else {
        auto min = min_element(filledSpaces.begin(), filledSpaces.end());
        int line = (int) distance(filledSpaces.begin(), min);
        cout << "min element: arr[" << line << "]" <<  endl;
        cout << "\e[1m" << "<< << << << line: " << line + 1 << " >> >> >> >>" << "\e[m" << endl;
        if (emptySpaces[line] == 0 && filledSpaces[line] == 0){
            //resize vectors
            vector<int> newVector1(emptySpaces.begin() + 1, emptySpaces.end());
            emptySpaces.resize(emptySpaces.size() - 1);
            emptySpaces = newVector1;

            vector<int> newVector2(filledSpaces.begin() + 1, filledSpaces.end());
            filledSpaces.resize(filledSpaces.size() - 1);
            filledSpaces = newVector2;
        } else if (emptySpaces[line] == 1){
            emptySpaces[line]--;
            filledSpaces[line]++;
        }
        else if (line == (int) emptySpaces.size() - 1){
            emptySpaces[line]--;
            filledSpaces[line]++;        
        }

        for (int size = _largestSize; size > 0; size--){
            if (spaceForSize(emptySpaces, filledSpaces, line, size)){
                cout << "quadrado tamanho: " << size << endl;
                vector<int> updatedEmptySpaces = remove_size(emptySpaces, line, size);
                vector<int> updatedFilledSpaces = add_size(filledSpaces, line, size);
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
    cout << "max size: " << _largestSize << endl;
    //cout << "resultado final: ";
    vector<int> emptySpaces(_path);
    vector<int> filledSpaces;
    filledSpaces.resize(emptySpaces.size());
    fill(filledSpaces.begin(), filledSpaces.end(), 0);
    cout << calculate_path(emptySpaces, filledSpaces,_largestSize) << endl;

    return 0;
}