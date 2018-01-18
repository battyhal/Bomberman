#include "Mensaje.h"

Mensaje::Mensaje():emisor_(0), hora_(0), infoExtra_(nullptr), receptor_(0) {}
Mensaje::Mensaje(int e, long h, void* in, int r):emisor_(e), hora_(h), infoExtra_(in),
receptor_(r) {}
Mensaje::~Mensaje() { delete infoExtra_; }

// ===================================================================================
// GETTERS
// ===================================================================================
int  Mensaje::Get_Emisor()const   { return emisor_;   }
long Mensaje::Get_Hora()const     { return hora_ ;    }
int  Mensaje::Get_Receptor()const { return receptor_; }

// ===================================================================================
// SETTERS
// ===================================================================================
void Mensaje::Set_Emisor(int e)   { emisor_ = e;   }
void Mensaje::Set_Hora(long h)    { hora_ = h;     }
void Mensaje::Set_Receptor(int r) { receptor_ = r; }

// ===================================================================================
// MÉTODOS
// ===================================================================================
