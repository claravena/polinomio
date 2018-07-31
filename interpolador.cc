#include <iostream>
#include "vector"
#include <fstream>
#include "Polinomio.h"
#include "cmath"


using namespace std;
//n corresponde al numero de puntos
//a corresponde al numero inicial
//b corresponce al numero final

void puntos_equiespacio(double n,double a,double b,Polinomio<double> P1,Polinomio<double> P2){
  ofstream archivo("datos.dat"); 
  double contador = a;
  for (int i=0; i<n;++i){
    ofstream archivo("datos.dat", ios::app);
    double Num= P1(contador);
    double Den= P2(contador);
    //archivo <<contador <<" "<<Num<<endl;
    archivo <<contador <<" "<<cos(exp(Num/Den))<<endl;
    //cout<<contador<<endl;
    contador +=(abs(b-a))/(n-1);
    //contador += (-2*a)/(n-1);
    //cout<<abs(b-a)/(n-1)<<endl;
  }
  archivo.close();
}

void puntos_Chebyshev(double n,double a, Polinomio<double> P1,Polinomio<double> P2){
   //nodos de Chebyshev
  ofstream archivo_Chebyshev("datos_Chebyshev.dat"); 
  for (int i=1; i<(n+1);++i){
    ofstream archivo_Chebyshev("datos_Chebyshev.dat", ios::app);
    double contador = -1*a*cos(((2*i-1)*M_PI)/(2*n)); 
    double Num= P1(contador);
    double Den= P2(contador);
    archivo_Chebyshev <<contador <<" "<<cos(exp(Num/Den))<<endl;
    }
  archivo_Chebyshev.close();
}


//Esta funcion retorna un polinomio, que puede visualizarse en pantalla. 
Polinomio<double> lagrange(ifstream& archivo){
  //Lee una archivo en forma de columna y lo pasa a dos vectores
  vector<double> vx,vy;
  double x,y;
  int i=0;
  while(archivo >> x >> y){
    vx.push_back(x);
    vy.push_back(y);
  }
  //Interpolacion de Lagrange retorna el polinomio en un polinomio llamado interpolado.
  vector<double> v_cero;
  for(int i=0; i<vx.size();++i){
    v_cero.push_back(0.0);
    };
  Polinomio<double> Pol_interpolado(v_cero);
  for(int j=0; j<vx.size(); ++j){
    vector<double> v_uno={1};
    Polinomio<double> Pol_base(v_uno);
    for(int i=0; i<vx.size(); ++i){
      double factor = vx[j]-vx[i];
      if (factor == 0){
      }
      else{
	vector<double> v_base;
	v_base.push_back(-vx[i]/factor);
	v_base.push_back(1/factor);
	Polinomio<double> Poli(v_base);
	Pol_base*=Poli;
      };
    }
    Pol_interpolado += vy[j]*Pol_base;
  }
  //Datos para graficar interpolacion lagrange, se toman 100 puntos en todo el intervalo y luego de evaluarlos en el polinomio se guardan en un archivo "datos.lagrange.dat". Ojo que el si el archivo existe lo sobreescribirá. 
  double contador = vx[0];
  ofstream archivo_lagrange("datos.lagrange.dat");
  for (int j=0; j<100;++j){
    double Num= Pol_interpolado(contador);
    archivo_lagrange <<contador <<" "<<Num<<endl;
    contador  = contador + abs(vx[0]-vx.back())/(100-1);
      
    }
    archivo.close();
  return Pol_interpolado; 

}

void splines_cubicos(ifstream& archivo){
  vector<double> vx,vy;
  double x,y;
  int i=0;
  while(archivo >> x >> y){
    vx.push_back(x);
    vy.push_back(y);
  }
  double n=vx.size();
  vector<double> vec_h,vec_r,vec_b,vec_c, vec_a, vec_z, vec_d;
  //vector delta x almacenado en vec_h y vector delta y almacena en vec_r
  for(int i=0; i<vx.size(); ++i){
    vec_h.push_back(vx[i+1]-vx[i]);
    vec_r.push_back(vy[i+1]-vy[i]);
  };
  
  /*Reordenar los vectores para hacer algoritmo de thomas. La idea es la diagonal se el el vector b, los elementos bajo la digonal son a y los elementos sobre la diagonal c. El vector d[i] = 6*(delta y[i]/h[i] - delta y[i-1]/h[i-1] ) */
  vec_b.push_back(vec_h[0]);
  vec_c.push_back(vec_h[0]);
  vec_a.push_back(0);
  vec_d.push_back(0);
  for(int i=0; i<vec_h.size()-1; ++i){
    vec_b.push_back(2.0*(vec_h[i+1]+vec_h[i]));
    vec_c.push_back(vec_h[i+1]);
    vec_a.push_back(vec_h[i]);
    vec_d.push_back(6*((vec_r[i+1]/vec_h[i+1])-(vec_r[i]/vec_h[i])));
  };
  /*algoritmo para transformar la matriz triadiagonal en una triangular superior
  c1[i] = c[i]/(b[i]-c1[i]*a[i]) para i= 2,3,...n-1 y c1[i]=c[i]/b[i] para i=1;
  */
  vector <double> vec_c1, vec_d1; 
  vec_c1.push_back(0);
  vec_c1.push_back(vec_c[1]/vec_b[1]);
  vec_d1.push_back(0);
  vec_d1.push_back(vec_d[1]/vec_b[1]);
  for(int i=0; i<vec_c.size()-3; ++i){
    vec_c1.push_back(vec_c[i+2]/(vec_b[i+2]-vec_c1[i+1]*vec_a[i+2]));
    vec_d1.push_back((vec_d[i+2]-vec_d1[i+1]*vec_a[i+2])/(vec_b[i+2]-vec_c1[i+1]*vec_a[i+2]));   
  }

  /*algoritmo inverso para obtener los valor de z
  Z[n]= d1[n]
  z[i]= d1[i] - (c1[i] * z[i+1])
   */
  for(int i=0; i<n; ++i){
    vec_z.push_back(0);
  }
  vec_z[n-2]=vec_d1[n-2];
  for(int i=(n-3); i>0; --i){
    vec_z[i]=vec_d1[i]-(vec_c1[i]*vec_z[i+1]);
  }

  /*Almacena coeficiente construidos para el calculo eficiente de los polinomio
  A1=-h[i]*z[i+1]/6 - h[i]*z[i]/3 + (y[i+1] - y[i])/h[i]
  A2=z[i]/2
  A3=(z[i]+1 z[i])/(6*h[i])*/
  vector<double> vec_A1,vec_A2,vec_A3;
  for(int i=0; i<n-1; ++i){
    vec_A3.push_back((vec_z[i+1]-vec_z[i])/(6*vec_h[i]));  
    vec_A2.push_back(vec_z[i]/2);
    vec_A1.push_back(((-vec_h[i]*vec_z[i+1]/6)-(vec_h[i]*vec_z[i]/3)+(vy[i+1]-vy[i])/vec_h[i]));
  }
  /*Aquí se calculan las evaluaciones finales del polinomio para cada intervalo, se tomo un forma simple de este. Si qk es el polinomio k-esimo entonces
   qk= yk + A3k*Pk+ A2kP*Pk + A3kPk*Pk*Pk donde P=(x-t[k]) */
  int k = 0;
  while(k < (n-1)){
    vector<double> VS = {-vx[k],1};
    Polinomio<double> Pol_VS(VS);
    double contador = vx[k];
    ofstream archivo1("datos.splines.dat", ios::app);
    for (int j=0; j<100;++j){
      double num= Pol_VS(contador);
      archivo1 <<contador <<" "<<(num*num*num*vec_A3[k])+(num*num*vec_A2[k])+(num*vec_A1[k])+vy[k]<<endl;
      contador = contador + (abs(vx[k+1]-vx[k]))/(100-1);
    }
    archivo.close();
    ++k;
  }
   /*Aquí se toman 100 puntos para cada polinomio qk. Se evalua en el polinomio Pk luego se hace el calculo de la ecuacion qk y
      se guarda en un archivo llamado "datos.splines.dat". Cuidado que si el archivo ya está creado este añadirá los nuevos puntos.  */ 









  
  //Esta parte de código tiene un error que no pude entender porque sucede cuando itero la formacion de polinomio, me calcula mal los coeficiente al cuadrado, pero cuando lo hago individualmente lo hace bien. 
  /*vector<double> vS1={vx[j+1],-1};
    vector<double> vS={-vx[j],1};
    Polinomio<double> Pol_S1(vS1);
    Polinomio<double> Pol_S(vS);
    Polinomio<double> Pol_Z(vec_z[j]/6);
    Polinomio<double> Pol_Z1(vec_z[j+1]/6);
    Polinomio<double> Pol_Y(vy[j]);
    Polinomio<double> Pol_Y1(vy[j+1]);
    Polinomio<double> Pol_H(vec_h[j]);
    //cout <<(Pol_Y*Pol_S1/Pol_H)+(Pol_Y1*Pol_S/Pol_H)+ (Pol_Z*(Pol_S1*Pol_S1*Pol_S1/Pol_H)+(-1.0*Pol_S1*Pol_Z))+ (Pol_Z1*(Pol_S*Pol_S*Pol_S/Pol_H)+(-1.0*Pol_S*Pol_Z1))<<endl;
    Polinomio<double> Pol_final(0); 
    //cout <<Pol_S*Pol_S*Pol_S- Pol_S<<endl;
    
    Pol_final = Pol_Z*((Pol_S1*Pol_S1*Pol_S1/Pol_H)+(-1.0*Pol_S1*Pol_H));
    Pol_final = Pol_final + (Pol_Z*(-1.0*Pol_S1*Pol_H));
    Pol_final = Pol_final + Pol_Z1*((Pol_S*Pol_S*Pol_S/Pol_H)+(-1.0*Pol_S*Pol_H)); 
    Pol_final = Pol_final + (Pol_Y1*Pol_S/Pol_H) ;
    Pol_final = Pol_final + (Pol_Y*Pol_S1/Pol_H); 
    cout<<Pol_final<<endl;*/		

}
