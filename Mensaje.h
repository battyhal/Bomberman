#ifndef MENSAJE_H
#define MENSAJE_H

class Mensaje 
{
private:
	int   emisor_;
	long  hora_;
	void* infoExtra_;
	int   receptor_;
protected:
public:
	Mensaje();
	Mensaje(int, long, void*, int);
	~Mensaje();
	
	// ===================================================================================
	// GETTERS
	// ===================================================================================
	int  Get_Emisor()const;
	long Get_Hora()const;
	int  Get_Receptor()const;
	
	// ===================================================================================
	// SETTERS
	// ===================================================================================
	void Set_Emisor(int);
	void Set_Hora(long);
	void Set_Receptor(int);
	
	// ===================================================================================
	// MÉTODOS
	// ===================================================================================
	
	
	
};

#endif

