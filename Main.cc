#include <iostream>
#include "Polinomio.h"
#include "cmath"
#include <fstream>

using namespace std;

int main(){
  vector<double> v1 = {-4,2,-5,1};
  vector<double> v2 = {8,7,3};
  Polinomio<double> num(v1);
  Polinomio<double> den(v2);
  num = den;

  cout<< num<<endl;

  
  
  //int N=30; 
  /*ofstream archivo("datos.dat"); 
  double contador = -5.0;
  for (int i=0; i<N;++i){
    ofstream archivo("datos.dat", ios::app);
    double Num= num(contador);
    double Den= den(contador); 
    archivo <<contador <<" "<<cos(exp(Num/Den))<<endl;
    //cout<<contador<<endl;
    contador += (10./(N-1));
  }
  archivo.close();

  //nodos de Chebyshev
  ofstream archivo_Chebyshev("datos_Chebyshev.dat"); 
  for (int i=1; i<(N+1);++i){
    ofstream archivo_Chebyshev("datos_Chebyshev.dat", ios::app);
    double contador = 5*cos(((2*i-1)*M_PI)/(2*N)); 
    double Num= num(contador);
    double Den= den(contador);
    archivo_Chebyshev <<contador <<" "<<cos(exp(Num/Den))<<endl;
    }
  archivo_Chebyshev.close();
  */
 return 0;
}

