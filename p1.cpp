#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

/* global variables */
int _N, _M;
vector<int> _path;
unordered_map<string, unsigned long long> hashmap;
int _largestSize = 0;

struct VectorHasher {
    unsigned long long operator()(const vector<int> &V) const {
        unsigned long long hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

string Stringhash(vector<int> emptySpaces){
    string hash = "";
    for (int i = 0; i < _N; i++){
        hash += to_string(emptySpaces[i]);
    }
    return hash;
}

unsigned long long my_hash(vector<int> emptySpaces){
    unsigned long long hash = 0;
    for (int i = 0; i < _N; i++){
        hash += emptySpaces[i] * pow(10, i);
    }
    return hash;
}

void printArray(vector<int> arr){
    for (int i = 0; i < _N; i++){
        cout << arr[i];
        if (i == _N - 1)
            cout << ";\n";
        else
            cout << ", ";
    }
}

/* reads the user's input and saves the values */
void readInput(){
    cin >> _N;
    cin >> _M;
    int u = 0;
    int j = 0;
    while (u == 0){
        cin >> u;
        if (u == 0)
            j++;
        if (j == _N)
            break;
    }
    _N -= j;
    _path.reserve(_N);
    _path.push_back(u);
    for (int i = 0; i < _N - 1; i++){
        cin >> u;
        _path.push_back(u);
    }
}

bool spaceForSize(vector<int> emptySpaces, int index, int sizeOfSquare){
    if (_N - index < sizeOfSquare || emptySpaces[index] == 0)
        return false;
    else { 
        if (sizeOfSquare != 1){
            for (int i = index; i < index + sizeOfSquare; i++){
                if (emptySpaces[i] < sizeOfSquare || (_path[i] - emptySpaces[i]) > (_path[index] - emptySpaces[index]))
                    return false;
            }
        }
    }
    return true;
}

vector<int> normalize(vector<int> arr){
    if (arr[0] > arr[1]){
        arr[0] = arr[1];
    }
    for (int i = 1; i < _N - 1; i++){
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1])
            arr[i] = max(arr[i - 1], arr[i + 1]);
    }
    if (arr[_N - 1] > arr[_N - 2]){
        arr[_N - 1] = arr[_N - 2];
    }
    return arr;
}

vector<int> remove_size(vector<int> arr, int index, int size){
    for (int i = index; i < index + size; i++){
        arr[i] -= size;
    }
    return arr;
}

void printRectangle(vector<int> emptySpaces){
    for (int i = 0; i < _N; i++){
        for (int j = 0; j < (_path[i] - emptySpaces[i]); j++){
            cout << "1\t";
        }
        for (int k = 0; k < emptySpaces[i]; k++){
            cout << "0\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool canPutSquares(vector<int> emptySpaces){
    for (int i = 0; i < _N - 1; i++){
        if (emptySpaces[i] < 2 && i == _N - 2){
            return false;
        }
        else if (emptySpaces[i] > 1 &&
        _path[i] - (_path[i + 1] - emptySpaces[i + 1]) > 1)
            return true;
    }
    return false;
}

int getLine(vector<int> emptySpaces){
    int min = _M;
    int line = 0;
    for (int i = 0; i < _N; i++){
        if (min > _path[i] - emptySpaces[i] && emptySpaces[i] != 0){
            min = _path[i] - emptySpaces[i];
            line = i;
        }
    }
    return line;
}

bool empty(vector<int> emptySpaces){
    for (int i = 0; i < _N; i++){
        if (emptySpaces[i] != 0)
            return false;
    }
    return true;
}

/* main algorithm */
unsigned long long calculate_path(vector<int> emptySpaces){
    unsigned long long figs = 0;

    string key = Stringhash(emptySpaces);

    if (hashmap.find(key) != hashmap.end()){
        return hashmap[key];
    }
    if (!canPutSquares(emptySpaces)){
        return 1;
    } else {
        int line = getLine(emptySpaces);

        for (int size = 1; size <= emptySpaces[line]; size++){
            if (spaceForSize(emptySpaces, line, size)){
                vector<int> updatedEmptySpaces = remove_size(emptySpaces, line, size);
                figs += calculate_path(updatedEmptySpaces);
            } else
                break;
        }
    }
    hashmap[key] = figs;
    return figs;
}

/* main function */
int main(){
    /* reads the user's input */
    readInput();

    if (empty(_path))
        cout << 0 << endl;
    else
        cout << calculate_path(_path) << endl;
    return 0;
}