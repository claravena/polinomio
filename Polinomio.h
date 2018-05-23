#include <vector>
#include <iostream>

using namespace std;


class Polinomio{
 private:
  int grado;
  vector<double> pol; 

 public:
  Polinomio(int,vector<double>);
  ~Polinomio();
  void set_polinomio(vector<double>);
  int get_grado();
  vector<double> get_pol(); 

};

//Constructor con default
Polinomio::Polinomio(int a,vector<double> A = {0}) {
  grado=a;
  if (A.size() == (grado+1)){
    pol = A;
    }
  else {
    for (int i=0;i<grado+1;++i)
      {
	pol.push_back(0);
      }
  }
  
}

//Destructor
Polinomio::~Polinomio(){
}

int Polinomio::get_grado(){
  return grado;  
}
vector<double> Polinomio::get_pol(){
  return pol; 
}
  
void Polinomio::set_polinomio(vector<double> A){
  pol=A; 
}

//Para mostrar un polinomio
ostream & operator << (ostream & os ,Polinomio M){
  int grado=M.get_grado();
  string r = "";
  vector<double> pol=M.get_pol(); 
  for (int i=0;i<grado+1;++i){
    
  }
  return os;
}

/*//Operador Suma
Polinomio operator + (Polinomio X, Polinomio Y){
  vector<double> v_sum;
  vector<double> v_X = X.get_pol();
  vector<double> v_Y = Y.get_pol();
  for (int i=0; i< v_X.size(); ++i){
    v_sum.push_back(v_X[i]+v_Y[i]);
  }; 
  Vector C(X.get_dim(),v_sum);
  return C;
}
*/

/*//Operador multiplicacion por escalar
Vector operator * (double x, Vector Y){
  double escalar = x; 
  vector<double> v_mul;
  vector<double> v_Y = Y.get_mt();
  for (int i=0; i< v_Y.size(); ++i){
    v_mul.push_back(escalar*v_Y[i]);
  }; 
  Vector C(Y.get_dim(),v_mul);
  return C;
}


//Producto punto
double operator * (Vector X, Vector Y){
  vector<double> v_mul;
  vector<double> v_X = X.get_mt();
  vector<double> v_Y = Y.get_mt();
  double C=0.0;
  for (int i=0; i< v_Y.size(); ++i){
    C=C+(v_X[i]*v_Y[i]);
  }; 
  return C;
}

*/


