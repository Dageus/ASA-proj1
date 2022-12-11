#include <vector>
#include <iostream>
#include <cmath>
#include <string>
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
        if (u > _largestSize)
            if(_N - i >= u)
                _largestSize = u;
        _path.push_back(u);
    }
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

        if (i != _N){
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
    if (emptySpaces[index] - filledSpaces[index] >= sizeOfSquare && _N - index >= sizeOfSquare)
        return true;
    else    
        return false;
}

vector<int> remove_size(vector<int> arr, int index, int size){
    for (int i = index; i < _N; i++){
        if (i == index + size)
            break;
        arr[i] -= size;
    }
    return arr;
}

vector<int> add_size(vector<int> arr, int index, int size){
    for (int i = index; i < _N; i++){
        if (i == index + size)
            break;
        arr[i] += size;
    }
    return arr;
}

int test_combinations(vector<int> arr, int l, int index){ /* (tamanho do quadrado que estamos a testar, index onde estamos) */
    int margin;
    int res = count_combinations(l, arr[index] + l, false);
    cout << "\e[1m" << " #" <<  "\e[m" << " testar proximas linhas: \n";
    for (int i = l - 1; i < _N - 1; i++){
        cout << "arr[" << i << "] = " << arr[i] << endl;
        margin = arr[i];
        if (margin != 0){
            cout << "margin: " << margin << endl;
            res += count_combinations(l, margin, true); 
            cout << "cabem quadrados na margem\n";
        }
    }
    cout << "res: " << res << endl;
    return res;
}

int test_square_format(vector<int> emptySpaces, vector<int> filledSpaces, int index){
    int figs = 0;

    for (int i = _largestSize; i > 0; i--){
        if (spaceForSize(emptySpaces, filledSpaces, index, i)){
            vector<int> updatedEmptySpaces = remove_size(emptySpaces, index, i);
            vector<int> updatedFilledSpaces = add_size(filledSpaces, index, i);

        }

    }








    if (size == 1)
        return 1;
    for (int i = 0; i < _N; i++){
        vector<int> temp_arr(_path.begin(), _path.end()); //temp array to count squares
        cout << "--> linha: " << i + 1 << endl; 
        if (i == _N - 1){
            cout << "fim da tentativa para quadrado de tamanho: " << size << endl;
            break;
        }
        if (arr[i] >= size){
            if (_N - i >= size){    
                cout << "cabe um quadrado de tamanho " << size << endl;
                if (arr[i] - size >= 1){
                    // test how many squares fit
                    cout << "cabe quadrados ao lado\n";
                    temp_arr = remove_size(temp_arr, i, size);
                    figs += test_combinations(temp_arr, size, i);
                }
                else{
                    figs++;
                    //temp_arr = remove_lines(temp_arr, i, size);
                    //figs += test_next_square(temp_arr, size, i);
                }
            } else{
                // if it cant fit in this line, it won't fit in the rest
                cout << "fim da tentativa para quadrado de tamanho: " << size << endl;
                break;
            }
        }
        cout << "figs: " << figs << endl;
    }
    return figs;
}

/* main algorithm */
int calculate_path(int l){
    int res = 0;

    vector<int> emptySpaces(_path);
    vector<int> filledSpaces;
    filledSpaces.resize(emptySpaces.size());
    fill(filledSpaces.begin(), filledSpaces.end(), 0);
    

    for (int i = 0; i < _N; i++){
        cout << "\e[1m" << "<< << << << index: " << i << " >> >> >> >>" << "\e[m" << endl;
        res += test_square_format(emptySpaces, filledSpaces, i);
        
    }

    return res;
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
    //cout << "resultado final: ";
    cout << calculate_path(_largestSize) << endl;

    return 0;
}