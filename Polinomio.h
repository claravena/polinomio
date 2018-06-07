#ifndef POLINOMIO_H
#define POLINOMIO_H
#include <vector>
#include <iostream>

using namespace std;


template <class T>
class Polinomio{
 private:
  int grado;
  vector<T> pol; 

 public:
  Polinomio(vector<T>);
  ~Polinomio();
  Polinomio(const Polinomio<T> &);
  void set_polinomio(vector<T>);
  int get_grado();
  vector<T> get_pol() const ;
  vector<T> div(Polinomio<T>);
  T Coef(int) const; 
  T operator()(T) const;
  Polinomio<T> derivada();
  Polinomio<T> integral(T);
  Polinomio & operator = (const Polinomio<T> &); 
  
  

};

#endif


/*############################################################ FUNCIONES ##################################################################################*/
//Constructor con default
template <class T>
Polinomio<T>::Polinomio(vector<T> B ){
  pol = B;
  
}
//Destructor
template <class T>
Polinomio<T>::~Polinomio(){
}

//contructor de copia 
template <class T>
Polinomio<T>::Polinomio(const Polinomio<T> & P){
  pol = P.get_pol(); 
}


//funcion entrega el grado del polinomio 
template <class T>
int Polinomio<T>::get_grado(){ 
  return pol.size()-1;
}
//funcion entrega el vector que contiene los coeficiente del polinomio  
template <class T>
vector<T> Polinomio<T>::get_pol() const{
  return pol; 
}

//funcion puede asignar un polinomio a partir de un vector.  
template <class T>
void Polinomio<T>::set_polinomio(vector<T> A){
  pol=A; 
}

//funcion que entrega el coeficiente que se le solicita
template <class T>
T Polinomio<T>::Coef(int i) const{
  return pol[i];
}

//Funcion que deriva el polinomio dado 
template <class T>
Polinomio<T> Polinomio<T>::derivada(){
  vector<T> derivada;
  vector<T> v_X= pol;
  for (int i=1; i<(v_X.size()); ++i){
    derivada.push_back((i)*v_X[i]);
  }
  Polinomio Derivada(derivada); 
  return Derivada;
}
//funcion que integra el polinomio dado, al que se le agrega una constante.Siempre agregar constante inclusive si es cero.  
template <class T>
Polinomio<T> Polinomio<T>::integral(T constante){
  vector<T> integral;
  integral.push_back(constante); 
  vector<T> v_X= pol;
  for (int i=1; i<(v_X.size()+1); ++i){
    integral.push_back(v_X[i-1]/i);
  }
  Polinomio<T> Integral(integral); 
  return Integral;
}

/*########################################## OPERADORES #################################################################################################*/

//operador para evaluar un valor x en el polinomio
template <class T>
T Polinomio<T>::operator()(T x) const
{
  //algoritmo de honner
  int grado = pol.size()-1; 
  T suma = 0;
  for (int i = grado; i > 0; i--){
    suma = x * (pol[i] + suma);
  }
  suma += pol[0];
  return suma;
}

//Operador cout para mostrar un polinomio
template <class T>
ostream & operator << (ostream & os ,Polinomio<T> M){
  int grado=M.get_grado();
  vector<T> pol=M.get_pol();
  
  if (pol[0]!=0){
    os << pol[0]; 
  }
  for (int i=1;i<grado+1;++i){
    if (pol[i]!=0){
      if (pol[i]>0){
	os << "+";
      }
      os << pol[i];
      if(i==0){
	os << "";
      }
      else if(i==1){
	os << "x";
      }
      else {
	os << "x^"<<i; 
	}
    }
    else {
    }    
  }
  os << endl; 
  return os;
}

//--------------------------Operador asignacion------------------------------

template <class T>
Polinomio<T> &Polinomio<T>::operator = (const Polinomio<T> & P){
  vector<T> v_copia=P.get_pol();  
  pol= v_copia;
  return *this; 
}



//Operador Suma
template <class T>
Polinomio<T> operator + (Polinomio<T> X, Polinomio<T> Y){
  vector<T> v_sum;
  vector<T> v_X = X.get_pol();
  vector<T> v_Y = Y.get_pol();
  if (v_X.size()>v_Y.size()){
    for (int i=0; i<v_X.size(); ++i){
      v_sum.push_back(v_X[i]+v_Y[i]);
    }
  }
  else{
    for (int i=0; i< v_Y.size(); ++i){
      v_sum.push_back(v_X[i]+v_Y[i]);
    }
  } 
  Polinomio<T> C(v_sum);
  return C;
}

//Operador Resta
template <class T>
Polinomio<T> operator - (Polinomio<T> X, Polinomio<T> Y){
  vector<T> v_sum;
  vector<T> v_X = X.get_pol();
  vector<T> v_Y = Y.get_pol();
  if (v_X.size()>v_Y.size()){
    for (int i=0; i< v_X.size(); ++i){
      v_sum.push_back(v_X[i]-v_Y[i]);
    }
  }
  else{
    for (int i=0; i< v_Y.size(); ++i){
      v_sum.push_back(v_X[i]-v_Y[i]);
    }
  } 
  Polinomio<T> C(v_sum);
  return C;
}

//Operador multiplicacion
template <class T>
Polinomio<T> operator * (Polinomio<T> X, Polinomio<T> Y){
  vector<T> v_producto;
  int grado= X.get_grado()+Y.get_grado();
  //llenar el nuevo vector polinomio
  for (int k=0; k<grado+1; ++k){
    v_producto.push_back(0.0);
  }
  for (int j=Y.get_grado(); j>=0; --j ){
    for(int i=0; i<=X.get_grado(); ++i){
      v_producto[i+j]=  v_producto[i+j]+(Y.Coef(j)*X.Coef(i));
    }
  }
  Polinomio<T> C(v_producto);
  return C;
}


//Operador multiplicacion por escalar
template <class T>
Polinomio<T> operator * (T x, Polinomio<T> Y){
  vector<T> v_producto;
  vector<T> v_pol = Y.get_pol();
  int grado= Y.get_grado();
  //llenar el nuevo vector polinomio
  for (int k=0; k<grado+1; ++k){
    v_producto.push_back(x*v_pol[k]);
  }
  Polinomio<T> C(v_producto);
  return C;
}
//Funcion que almacena los resultados de la division sintetica tomando como divisor un binomio monico. Se almacena los resultado en un vector donde el v[0]= resto, los demas términos son los coeficientes del polinomio
template <class T>
vector<T> Polinomio<T>::div(Polinomio<T> Y){
  vector<T> v_dividido;
  T numero = -1*Y.Coef(0);
  //cout <<pol.size()<<endl; 
  for(int k=0; k<pol.size(); ++k){
    v_dividido.push_back(0.0);
  }
  for(int i=v_dividido.size(); i>0; --i){
    v_dividido[i-1]=(v_dividido[i]*numero)+pol[i-1]; 
  }
  return v_dividido;
}
//operador division sintetica tomando como divisor monomios mónicos usando funcion "div"
template <class T>
Polinomio<T> operator / (Polinomio<T> X, Polinomio<T> Y){
  vector<T> v_nuevo; 
  vector<T> v_div = X.div(Y);
  for(int k=1; k<X.get_grado()+1; ++k){
    v_nuevo.push_back(v_div[k]);
  }
  Polinomio<T> C(v_nuevo);
  return C;
}

//Operador resto division sintetica usando funcion div 
template <class T>
T operator % (Polinomio<T> X, Polinomio<T> Y){
  return X.div(Y)[0];
}


