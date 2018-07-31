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
  Polinomio(T);
  Polinomio();
  ~Polinomio();
  Polinomio(const Polinomio<T> &);
  void set_polinomio(vector<T>);
  int get_grado();
  vector<T> get_pol() const ;
  vector<T> div(Polinomio<T>);
  Polinomio<T> div_sintetica(Polinomio<T>);
  T resto_sintetica(Polinomio<T>);
  Polinomio<T> division(Polinomio<T>);
  Polinomio<T> resto(Polinomio<T>);
  T Coef(int) const; 
  T operator()(T) const;
  Polinomio<T> derivada();
  Polinomio<T> integral(T);
  Polinomio & operator = (const Polinomio<T> &);
  void operator +=(const Polinomio<T> & P); 
  void operator -=(const Polinomio<T> & P); 
  Polinomio & operator *=(const Polinomio<T> & P);  
};

#endif


/*############################################################ FUNCIONES ##################################################################################*/
//Constructor sin default
template <class T>
Polinomio<T>::Polinomio(vector<T> B){
  pol = B;
  
}

//Constructor sin default caso Polinomio(T(a))
template <class T>
Polinomio<T>::Polinomio(T b){
  vector<T> B={b};
  //b.push_back(T(0));
  pol = B;
}

//Constructor sin default caso Polinomio()
template <class T>
Polinomio<T>::Polinomio(){
  vector<T> B={T(0),T(0)};
  //b.push_back(T(0));
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

//Funcion que almacena los resultados de la division sintetica tomando como divisor un binomio monico. Se almacena los resultado en un vector donde el v[0]= resto, los demas términos son los coeficientes del polinomio, regla de ruffini. 
template <class T>
vector<T> Polinomio<T>::div(Polinomio<T> Y){
  vector<T> v_dividido;
  T numero = -1*Y.Coef(0);
  for(int k=0; k<pol.size(); ++k){
    v_dividido.push_back(0.0);
  }
  for(int i=v_dividido.size(); i>0; --i){
    v_dividido[i-1]=(v_dividido[i]*numero)+pol[i-1]; 
  }
  return v_dividido;
}

//Funcion division sintetica tomando como divisor monomios mónicos usando funcion "div"
template <class T>
Polinomio<T> Polinomio<T>::div_sintetica(Polinomio<T> Y){
  vector<T> v_nuevo;
  Polinomio<T> X(pol);
  vector<T> v_div = X.div(Y);
  for(int k=1; k<X.get_grado()+1; ++k){
    v_nuevo.push_back(v_div[k]);
  }
  Polinomio<T> C(v_nuevo);
  return C;
  }

//funcion resto division sintetica usando funcion div 
template <class T>
T Polinomio<T>::resto_sintetica(Polinomio<T> Y){
  Polinomio<T> X(pol);
  return X.div(Y)[0];
}

//División de polinomios 
template <class T>
Polinomio<T> Polinomio<T>::division(Polinomio<T> Y){
  Polinomio<T> Pol_num(pol);
  Polinomio<T> Pol_den(1); //polinomio por defecto
  Pol_den=Y; //asigno el polinomio Y a el denominidor, es solo un cambio de nombre.;
  double grado_cuociente = Pol_num.get_grado()-Pol_den.get_grado();
  vector<double> v_cuociente;
  double contador =grado_cuociente;
  if(contador >=0){
    for(int i= 0; i<grado_cuociente+1; ++i){
      v_cuociente.push_back(T(0));
    }
    while(contador >=0){
      vector<double> v_resta;
      double contador1=Pol_num.get_grado()-Pol_den.get_grado();
      for(int i= 0; i<contador1+1; ++i){
	v_resta.push_back(T(0));
      }
      if(Pol_num.get_grado()>=Pol_den.get_grado()){
	double grado_num = Pol_num.get_grado();
	double grado_den = Pol_den.get_grado();
	double cuociente = Pol_num.Coef(grado_num)/Pol_den.Coef(grado_den);
	v_cuociente[contador]=cuociente;
	v_resta[contador1]=cuociente;
	Polinomio<T> Pol_resta(v_resta);
	Pol_num=Pol_num-(Pol_den*Pol_resta); 
	--contador;
	for(int i=0; i<v_resta.size();++i)
	  v_resta.pop_back();
      }        
    }
  }
  Polinomio<T> Pol_cuociente(v_cuociente);
return Pol_cuociente;
}


//Funcion polinomial del resto de una division
template <class T>
Polinomio<T> Polinomio<T>::resto(Polinomio<T> Y){
  Polinomio<T> Pol_num(pol);
  Polinomio<T> Pol_den(1); //polinomio por defecto
  Pol_den=Y; //asigno el polinomio Y a el denominidor, es solo un cambio de nombre.;
  double grado_cuociente = Pol_num.get_grado()-Pol_den.get_grado();
  double contador =grado_cuociente;
  if(contador >=0){
    while(contador >=0){
      vector<double> v_resta;
      double contador1=Pol_num.get_grado()-Pol_den.get_grado();
      for(int i= 0; i<contador1+1; ++i){
	v_resta.push_back(T(0));
      }
      if(Pol_num.get_grado()>=Pol_den.get_grado()){
	double grado_num = Pol_num.get_grado();
	double grado_den = Pol_den.get_grado();
	double cuociente = Pol_num.Coef(grado_num)/Pol_den.Coef(grado_den);
	v_resta[contador1]=cuociente;
	Polinomio<T> Pol_resta(v_resta);
	Pol_num=Pol_num-(Pol_den*Pol_resta); 
	--contador;
	for(int i=0; i<v_resta.size();++i)
	  v_resta.pop_back();
      }        
    }
  }
return Pol_num;
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

//-----------------------Operador += ----------------------------------------
template <class T>
void Polinomio<T>::operator +=(const Polinomio<T> & P){
  vector<T> otro_pol = P.get_pol();
  if (pol.size()>otro_pol.size()){
    for (int i=0; i<pol.size(); ++i){
      pol[i]+=otro_pol[i];
    }
  }
  else{
    for (int i=0; i< otro_pol.size(); ++i){
      pol[i]+=otro_pol[i];
    }
  }
  while(pol.back()==0){
    pol.pop_back();
  }
}

//-----------------------Operador -= ----------------------------------------
template <class T>
void Polinomio<T>::operator -=(const Polinomio<T> & P){
  vector<T> otro_pol = P.get_pol();
  if (pol.size()>otro_pol.size()){
    for (int i=0; i<pol.size(); ++i){
      pol[i]-=otro_pol[i];
    }
  }
  else{
    for (int i=0; i< otro_pol.size(); ++i){
      pol[i]-=otro_pol[i];
    }
  }
  while(pol.back()==0){
    pol.pop_back();
  }
}


//-----------------------Operador *= ----------------------------------------
template <class T>
Polinomio<T> & Polinomio<T>::operator *=(const Polinomio<T> & P){
  vector<T> v_producto;
  vector<T> otro_pol=P.get_pol();
  int grado= pol.size()+otro_pol.size()-1;
  //llenar el nuevo vector polinomio
  for (int k=0; k<grado+1; ++k){
    v_producto.push_back(T(0));
  }
  for (int j=otro_pol.size()-1; j>=0; --j ){
    for(int i=0; i<=pol.size()-1; ++i){
      v_producto[i+j]+=(otro_pol[j]*pol[i]);
    }
  }
  pol = v_producto; 
  return *this;
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
  while(v_sum.back()==0){
    v_sum.pop_back();
  }
  Polinomio<T> C(v_sum);
  return C;
}

//Operador Suma para sumar una constante al polinomio. Ejemplo 2+POLINOMIO.
template <class T>
Polinomio<T> operator + (T y, Polinomio<T> Y){
  vector<T> v_y;
  v_y.push_back(y);
  Polinomio<T> pol_y(v_y);
  Y+=pol_y;
  return Y;
}
//Operador Suma para sumar una constante al polinomio. Ejemplo POLINOMIO+2
template <class T>
Polinomio<T> operator + (Polinomio<T> Y,T y){
  vector<T> v_y;
  v_y.push_back(y);
  Polinomio<T> pol_y(v_y);
  Y+=pol_y;
  return Y;
}

template <class T>
Polinomio<T> operator - (Polinomio<T> X, Polinomio<T> Y){
  return X+(-T(1)*Y);
  }

//Operador resta, para restar una constante al polinomio. Ejemplo T(a)-POLINOMIO.
template <class T>
Polinomio<T> operator - (T y, Polinomio<T> Y){;
  return y+(-T(1)*Y);
  }

//Operador resta, para restar una constante al polinomio. Ejemplo POLINOMIO-T(a).
template <class T>
Polinomio<T> operator - (Polinomio<T> Y,T y){;
  return Y+(-T(1)*y) ;
  }

//Operador multiplicacion de polinomios 
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

//Operador multiplicacion por escalar T(a)*polinomio
template <class T>
Polinomio<T> operator * (T x, Polinomio<T> Y){
  Polinomio<T> X(x);
  return X*Y;
}

//Operador multiplicacion por escalar polinomio*T(a)
template <class T>
Polinomio<T> operator * (Polinomio<T> Y,T x){
  Polinomio<T> X(x);
  return Y*X;
}

// Operador / para la division por polinomios 
template <class T>
Polinomio<T> operator / (Polinomio<T> X, Polinomio<T> Y){
  return X.division(Y);
}

// Operador / para la division por escalar
template <class T>
Polinomio<T> operator / (Polinomio<T> X, T x){
  Polinomio<T> Y(x); 
  return X.division(Y);
}


 //Operador resto division usando funcion resto 
template <class T>
Polinomio<T> operator % (Polinomio<T> X, Polinomio<T> Y){
  return X.resto(Y);
}

