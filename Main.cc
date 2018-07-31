#include <iostream>
#include "interpolador.cc"

using namespace std;

int main(){
  vector<double> v1 = {-4,2,-5,1};
  vector<double> v2 = {8,7,3};
  Polinomio<double> num(v1);
  Polinomio<double> den(v2);
  Polinomio<double> V1(0);
  
  double N=10; // numero de intervalos 
  double a=-5; // valor inicial de intervalo
  //Funciones que hacen puntos.
  double b=5;
  ofstream datos;
  datos.open("datos.dat");
  puntos_equiespacio(N,a,b,num,den);
  //puntos_Chebyshev(N,a,num,den);
  datos.close();


  ifstream datos1;
  datos1.open("datos.dat");
  splines_cubicos(datos1);


  //ifstream datos2;
  //datos2.open("datos_Chebyshev.dat");
  //cout<<lagrange(datos1)<<endl;
  //cout<<lagrange(datos2)<<endl;
  datos1.close();
  //V1=den;
  //cout << num <<endl;
  //cout << (4.0-num).get_grado()<<endl;
  
   return 0;
   
}
