#ifndef SUDOKU
#define SUDOKU
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <array>
#include <sstream>

#define N9  9
#define N3  3
#define N20 20

using namespace std; 

extern const string values;
class Sudoku{
    array< array<int,N3>,N9*N9 > units;
    array<array<int,N9>, N3*N9> unitlist;
    array<array<int,N20>,N9*N9> peers;
    string data_grid;
    array<string,N9*N9> solution; 
    void create_box();
    void get_values();
    void get_values(string &data_grid);
    int simple_algorithm();
    int brute_force(int &calls);
    int do_cycle(array<string,N9*N9> &tmp);
    int whole_cycle(int &j, int &k, 
         array<string,N9*N9> &tmp1, array<string,N9*N9> &tmp2 );
    void order_sol(array<string,N9*N9> tmp,vector<int> &ord_list);
    public:
        Sudoku();
        Sudoku(string &data_grid);
        int solve();
        void print_solution(); 
        void print_solution(array<string,N9*N9> &tmp);
        array<string,N9*N9> get_sol(); 
}; 
#endif
