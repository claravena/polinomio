#include <iostream>
#include "Polinomio.h"

using namespace std;

int main(){
  vector<double> v1 = {1,1,1,1,1};
  vector<double> v2 = {1,1,1,1,1};
  Polinomio M(4);
  Polinomio G(4,v1);
  
  M.set_polinomio(v1);
  G.set_polinomio(v2);
  //cout <<M<<endl;
  //cout <<G<<endl;
  cout <<M<<endl;
  //cout <<2*G<<endl;
  


  
   
  return 0;
}

