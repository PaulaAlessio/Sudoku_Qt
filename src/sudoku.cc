#include "sudoku.h"

const string values="123456789";

Sudoku::Sudoku(){
    create_box();
    get_values();
}

Sudoku::Sudoku(string &data_grid){
    create_box();
    get_values(data_grid);
}

void Sudoku::create_box(){
    for (int i=0;i<N9;i++){
        for (int j = 0;j < N9;j++){
            unitlist[i][j] = j*N9+i;
            unitlist[i+N9][j] = i*N9+j;
            unitlist[i+2*N9][j] = 
                (i/N3)*(N9*N3)+(i%N3)*N3 +j%N3+N9*(j/N3);
        }
    }
    for (int i=0; i<N9*N9; i++){
        int c=0;
        for (int j=0; j<N3*N9; j++){
            for (int k=0; k<N9; k++){
                if (i == unitlist[j][k]){
                    units[i][c] = j;
                    c++;
                }
            }
        }
    }
    for (int i = 0; i< N9*N9; i++){
        int c=0;
        set<int> tmp;
        for (int j = 0 ; j< N3 ; j++){
            for (int k=0; k<N9; k++){
                int elem = unitlist[units[i][j]][k];
                if (i!=elem){
                    tmp.insert(elem );
                    c++;
                }
            }
        }
        int j=0;
        for (auto pos=tmp.begin(); pos!=tmp.end(); ++pos){
            peers[i][j] = *pos;
            j++;
        }
    }

  
}

void  Sudoku::get_values(){
       cout << "Introduce the data as in the following example: " << endl;
       cout << "85...24..72......9..4.........1.7..23.5...9...4...........8..7..17..........36.4." << endl;
       cout << "Note that it must be " << N9*N9 << " characters long" << endl;
       try {
            getline(cin,data_grid);
            int e=data_grid.size();
            if (e!=N9*N9) throw e;
        }
        catch (int e){
            cout << "An exception ocurred: String size should be "<<
                 N9*N9 << ". " << e << "found instead" << endl;
            exit(-1);
        }
        for (int i=0;i<N9*N9;i++){
            if (data_grid[i]!='.'&& data_grid[i]!='0') 
                solution[i]=data_grid[i];
            else solution[i]=values;

        }
}

void  Sudoku::get_values(string &data_grid){
        for (int i=0;i<N9*N9;i++){
            if (data_grid[i]!='.'&& data_grid[i]!='0') 
                solution[i]=data_grid[i];
            else solution[i]=values;

        }
}

int Sudoku::do_cycle(array<string,N9*N9> &sol_tmp){
   for (int i=0; i<N9*N9 ; i++){
        if (sol_tmp[i].size()>1){
            for(int j=0; j<N20; j++){
                if(sol_tmp[peers[i][j]].size()==1){
                    for (unsigned int k=0;k<sol_tmp[i].size();k++){
                       if (sol_tmp[peers[i][j]][0]==(sol_tmp[i][k])){
                            sol_tmp[i].erase(sol_tmp[i].begin()+k);
                        }
                    }
                }
            }
        }
        if (sol_tmp[i].size()==0) return 1;
    }
    for (int i=0;i<N3*N9; i++){
        for (int v=0 ; v< N9 ; v++){
            int c=0;
            int index;
            for (auto s=unitlist[i].begin();s!=unitlist[i].end(); ++s){
                for (unsigned int k=0;k<sol_tmp[*s].size();k++){
                    if(values[v]==sol_tmp[*s][k]){ 
                        c++;
                        index=*s;
                    }
                }
            }
            if (c==1) sol_tmp[index]=values[v]; 
            else if (c==0) return 2;
        }
    }
    return 0;
}


int  Sudoku::simple_algorithm(){
    array<string,N9*N9> solution_tmp=solution;
    try {
      int i=do_cycle(solution_tmp);
      if (i>0) throw i;
    }
    catch (int i){
        cout << "An Exception occured. Sudoku passed is unsolvable." << endl;
        exit(-1);
    }
    if (solution==solution_tmp) return 0;
    else {
        solution=solution_tmp;
        return 1; 
    }
}

int  Sudoku::whole_cycle(int &j, int &k, 
     array<string,N9*N9> &tmp1, array<string,N9*N9> &tmp2 ){
     int calls=0;
     while (j==0 && k==0){
         j=do_cycle(tmp2);
         calls++;
         if (tmp2==tmp1) k=1;
         else tmp1=tmp2;
     }
    return calls;
}

void Sudoku::order_sol(array<string,N9*N9> tmp, vector<int> &ord_list){
     for (int i=0;i<N9*N9;i++){
        for(unsigned int s=2; s<N9;s++){
            if (tmp[i].size()==s){
                ord_list.push_back(i);
            }
        }
     }
}

int Sudoku::brute_force(int &calls){
  array<string,N9*N9> sol_tmp1=solution;
  array<string,N9*N9> sol_tmp2=solution;
  array<string,N9*N9> sol_tmp3=solution;
  array<string,N9*N9> aux=solution;
  bool final=false;
  while(!final){
     aux=sol_tmp1;
     vector<int>  ord_list;
     order_sol(aux,ord_list);
     for (auto i=ord_list.begin();i!=ord_list.end();++i){
        for (unsigned int p=0;p<sol_tmp1[*i].size();p++){
            sol_tmp2[*i]=sol_tmp1[*i][p];
            sol_tmp3[*i]=sol_tmp1[*i][p];
            int j1=0,k1=0;
            calls+=whole_cycle(j1,k1,sol_tmp2,sol_tmp3);
            if (j1>0){
                sol_tmp1[*i].erase(sol_tmp1[*i].begin()+p);
                sol_tmp2=sol_tmp1;
                sol_tmp3=sol_tmp1;
                int j2=0,k2=0;
                calls+=whole_cycle(j2,k2,sol_tmp2,sol_tmp3);
                sol_tmp1=sol_tmp2;
                if (j2>0){
                    return 1;
                }
            }
            else{
                sol_tmp2=sol_tmp1;
                sol_tmp3=sol_tmp1;
            }
        }
    } 
     final=true;
     for(int k=0;k<N9*N9;k++){
          if(sol_tmp1[k].size()>1) final=false;
     }
     if (aux==sol_tmp1){
          array<string,N9*N9> save=aux;
          vector<int> list;
          order_sol(aux,list);
          for (auto i=ord_list.begin();i!=ord_list.end();++i){  
             for (unsigned int p=0;p<save[*i].size();p++){
                solution[*i]=solution[*i][p];
                int out=brute_force(calls);
                if (out==1){
                    save[*i].erase(save[*i].begin()+p);
                    solution=save;
                }
                else{
                    save=solution;
                    
                }  
                sol_tmp1=save;
                sol_tmp2=save;
                sol_tmp3=save;
             }
          }
          //exit(-1);
     } 
  }
  solution=sol_tmp1;
  return 0; 
}


void Sudoku::print_solution(){
    for (int i=0;i<N9*N9; i++){
      cout << solution[i] << " " ;
      if(i%N9==N9-1) {
        cout << endl;
      }
      else if (i%N3==N3-1) cout << "| ";
      if (i==N3*N9-1 || i ==2*N3*N9-1 )
         cout << "------+-------+------"<< endl;
    }
}


void Sudoku::print_solution(array<string,N9*N9>&solution){
    for (int i=0;i<N9*N9; i++){
      cout << solution[i] << " " ;
      if(i%N9==N9-1) {
        cout << endl;
      }
      else if (i%N3==N3-1) cout << "| ";
      if (i==N3*N9-1 || i ==2*N3*N9-1 )
         cout << "------+-------+------"<< endl;
    }
}


int Sudoku::solve(){
    int i=1;
    int calls=-1;
    while (i==1){
        calls++;
        i=simple_algorithm();
    }
    brute_force(calls);   
    print_solution();
    return calls;
}

array<string,N9*N9> Sudoku:: get_sol(){
    return solution;

}
