#include "Nodo.h"

Nodo::Nodo():abajo_(nullptr), arriba_(nullptr), derecha_(nullptr),
izquierda_(nullptr), padre_(nullptr), portal_(nullptr), contenido_(' '),
distanciaGlobal_(0.0), distanciaLocal_(0.0), obstaculo_(0), visitado_(0),
x_(0), y_(0){}

Nodo::Nodo(char c, bool o, bool v, int x, int y):
abajo_(nullptr), arriba_(nullptr), derecha_(nullptr), izquierda_(nullptr),
padre_(nullptr), portal_(nullptr), contenido_(c), distanciaGlobal_(100000.0),
distanciaLocal_(100000.0), obstaculo_(o), visitado_(v), x_(x), y_(y){}

Nodo& Nodo::operator=(const Nodo& otro)
{
	abajo_ = otro.abajo_;
	arriba_ = otro.arriba_;
	derecha_ = otro.derecha_;
	izquierda_ = otro.izquierda_;
	padre_ = otro.padre_;
	portal_ = otro.portal_;
	contenido_ = otro.contenido_;
	distanciaGlobal_ = otro.distanciaGlobal_;
	distanciaLocal_ = otro.distanciaLocal_;
	obstaculo_ = otro.obstaculo_;
	vecinos_ = otro.vecinos_;
	visitado_ = otro.visitado_;
	x_ = otro.x_;
	y_ = otro.y_;
	
	return *this;
}

Nodo::~Nodo()
{
	abajo_ = nullptr;
	arriba_ = nullptr;
	derecha_ = nullptr;
	izquierda_ = nullptr;
	padre_ = nullptr;
	portal_ = nullptr;
	
	delete abajo_;
	delete arriba_;
	delete derecha_;
	delete izquierda_;
	delete padre_;
	delete portal_;
}

// ---------------------------------------------------------------
// GETTERS
// ---------------------------------------------------------------
Nodo* Nodo::Get_Abajo()    { return abajo_; }
Nodo* Nodo::Get_Arriba()   { return arriba_; }
Nodo* Nodo::Get_Derecha()  { return derecha_; }
Nodo* Nodo::Get_Izquierda(){ return izquierda_; }
Nodo* Nodo::Get_Padre()    { return padre_; } 
Nodo* Nodo::Get_Portal()   { return portal_; }
char  Nodo::Get_Contenido(){ return contenido_; }
float Nodo::Get_Global()   { return distanciaGlobal_; }
float Nodo::Get_Local()    { return distanciaLocal_; }
bool  Nodo::Get_Obstaculo(){ return obstaculo_; }
bool  Nodo::Get_Visitado() { return visitado_; }
std::vector<Nodo*> Nodo::Get_Vecinos(){ return vecinos_; } 
int   Nodo::Get_X()        { return x_; }
int   Nodo::Get_Y()        { return y_; }

// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------
void Nodo::Set_Abajo(Nodo* n)     		{ abajo_ = n; }
void Nodo::Set_Arriba(Nodo* n)     		{ arriba_ = n; }
void Nodo::Set_Derecha(Nodo* n)   		{ derecha_ = n; }
void Nodo::Set_Izquierda(Nodo* n) 		{ izquierda_ = n; }
void Nodo::Set_Padre(Nodo* n)      		{ padre_ = n; };
void Nodo::Set_Portal(Nodo* n)          { portal_ = n; }
void Nodo::Set_Contenido(char c)        { contenido_ = c; }
void Nodo::Set_Distancia_Global(float f){ distanciaGlobal_ = f; }
void Nodo::Set_Distancia_Local(float f) { distanciaLocal_ = f; }
void Nodo::Set_Obstaculo(bool b)   	    { obstaculo_ = b; }
void Nodo::Set_Visitado(bool b)   	    { visitado_ = b; }
void Nodo::Set_X(int i)                 { x_ = i; }
void Nodo::Set_Y(int i)		   	        { y_ = i; }

// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
void Nodo::Incluir_Vecino(Nodo* n){ vecinos_.push_back(n); }
void Nodo::Ver_Todo()
{
	if(abajo_)
		std::cout << " Conecta por debajo\n";
	if(arriba_)
		std::cout << " Conecta por arriba\n";
	if(derecha_)
		std::cout << " Conecta por la derecha\n";
	if(izquierda_)
		std::cout << " Conecta por la izquierda\n";
	if(padre_)
		std::cout << " Padre(" << padre_->Get_X() << ", " << padre_->Get_Y() << ")\n";
	else std::cout << " No tiene padre\n";
	if(contenido_ != ' ')
		std::cout << " Contenido = " << contenido_ << "\n";
	else std::cout << " Sin contenido\n";
	std::cout << " Distancia Global = " << distanciaGlobal_ << "\n";
	std::cout << " Distancia Local = " << distanciaLocal_ << "\n";
	if(obstaculo_)
		std::cout << " Es obstaculo\n";
	else std::cout << " No es obstaculo\n";
	if(vecinos_.size() != 0)
	{
		std::cout << " Tiene " << vecinos_.size() << " vecinos\n";
		auto contador = 0;
		for(auto it : vecinos_)
		{
			std::cout << " Vecino " << contador << ".X, Y = " << it->Get_X() << ", " << it->Get_Y() << "\n";
			contador++;
		}
	}
	else std::cout << " No tiene vecinos\n";
	if(visitado_)
		std::cout << " Ya ha sido visitado\n";
	else std::cout << " No ha sido visitado\n";
	std::cout << " X = " << x_ << "\n";
	std::cout << " Y = " << y_ << "\n";
}
