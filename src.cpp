 #include "header.h"
// #include <vector>
// #include <chrono>
// #include <iostream>
// #include "windows.h"
// #include "psapi.h"

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "stdlib.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <sstream>
#include <random>
#include "windows.h"
#include "psapi.h"

void test_push_back(int k);
void test_pop_back();
void test_assign_operator();
void test_size();
void test_empty();

std::chrono::steady_clock::time_point clockStart;
double accumulatedTime;

using namespace std;


int main() {

    test_push_back(10);
    test_pop_back();
    test_assign_operator();
    test_size();
    test_empty();


}




void test_empty() {
    std::cout << "sukuriame nauj1 class Vector tipo kintamaji ir patikriname, ar jis yra tuscias...\n";
    Vector<int> v;
    if(v.empty())
        std::cout << "Vektorius yra tuscias!\n";
    else
        std::cout << "Vektorius nera tuscias!\n";
}


void test_size() {
    std::cout << "Sukuriame nauja class Vektoriaus tipo kintamaji ir panaudojame konstruktoriu, kuris rezervuoja dydi (tarkim 10)...\n";
    Vector<int> v(10);
    std::cout << "Pabandome suzinoti size class Vectoriaus...\n";
    std::cout << v.size() << "\n";
}

void test_assign_operator() {
    std::vector<int> v1, v2;
    Vector<int> v3, v4;
    for(int i = 0; i < 5; i++) {
        v1.push_back(i);
        v3.push_back(i);
    }

    std::cout << "Sukuriami 2 std::vector (v1, v2) ir 2 class Vector (v3, v4): 1 tuscias, 1 uzpildytis nuo 1 iki 5.\n";
    v2 = v1;
    std::cout << "Pabandeme panaudoti v2 = v1 ir ziurime, ar v2 igavo reiksmes: \n";
    std::cout << "{ ";
    for(auto k: v2)
        std::cout << " " << k; 
    std::cout << " } \n";
    v4 = v3;
    std::cout << "Pabandeme panaudoti v3 = v4 ir ziurime, ar v4 igavo reiksmes: \n";
    std::cout << "{ ";
    for(auto k: v4)
        std::cout << " " << k; 
    std::cout << " } \n";
}



void test_pop_back() {
    Vector<int> v1;
    std::cout << "Testuojama pop_back su class Vector...\n";
    for(int i = 0; i < 5; i++) {
        v1.push_back(i);
    }
    cout << "{";
    for(auto n: v1)
        cout << " " << n;
    cout << "}\n";
    v1.pop_back();
    cout << "{";
    for(auto n: v1)
        cout << " " << n;
    cout << "}\n";
    std::cout << "Testuojama pop_back su std::vector...\n";
    std::vector<int> v2;
     for(int i = 0; i < 5; i++) {
        v2.push_back(i);
    }
    cout << "{";
    for(auto n: v2)
        cout << " " << n;
    cout << "}\n";
    v2.pop_back();
    cout << "{";
    for(auto n: v2)
        cout << " " << n;
    cout << "}\n";
}



void test_push_back(int k) {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;  

    auto t1 = std::chrono::steady_clock::now();

    int n = 0;
    Vector<int> vect;
    
    for(int i = 0; i < k; i++)
    {
        vect.push_back(i);
        if(vect.capacity() == vect.size()) n++;
    }
    auto t2 = std::chrono::steady_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;

    double laikas = ms_double.count();
    std::cout << "class Vector push_back su " << k << " elementu truko: " << laikas << " ir ivyko " << n << " atminties perskirstymu. \n" << std::flush;

    ms_double = std::chrono::milliseconds::zero();

    t1 = std::chrono::steady_clock::now();

    std::vector<int> vect2;
    
    for(int i = 0; i < k; i++)
    {
        vect2.push_back(i);
        if(vect2.capacity() == vect2.size()) n++;
    }
    t2 = std::chrono::steady_clock::now();
    ms_double = t2 - t1;

    laikas = ms_double.count();
    std::cout << "std::vector push_back su " << k << " elementu truko: " << laikas << " ir ivyko " << n << " atminties perskirstymu. \n" << std::flush;

}