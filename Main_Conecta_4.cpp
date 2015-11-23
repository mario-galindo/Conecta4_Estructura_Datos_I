#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <sstream>
//Mario Galindo - 61311453


using namespace std;

class Nodo{
           public:
               
              int valor;
              Nodo *derecha;
              Nodo *izquierda;
              Nodo *arriba;
              Nodo *abajo;
   
     Nodo(int val)
     {
        valor = val;
        arriba = 0;          
        abajo = 0;
        derecha = 0;
        izquierda =0; 
        
     }
     
     int getElemento()
     {
       return valor;
     }      
           
};

class Lista{
      
     public:
             Nodo *PrimeroPtr; 
             Nodo *UltimoPtr;
             int tamano_rec;
             int tamano;
             
     public:
         
            
            Lista()
            {
              
               PrimeroPtr =  UltimoPtr =0; 
                tamano =0;  
            } 
            
            bool IsEmpty()
            {
               return PrimeroPtr == 0 ;      
            }
            
   
           
        void InsertAtEnd(int val) 
        {
            
            Nodo *nuevoPtr = new Nodo(val);

            if (IsEmpty()) 
            {
                PrimeroPtr = UltimoPtr = nuevoPtr;
                tamano++;
            }
            else 
            {
                UltimoPtr->derecha = nuevoPtr;
                nuevoPtr->izquierda = UltimoPtr;
                UltimoPtr = nuevoPtr;
                UltimoPtr->derecha = PrimeroPtr;  
                PrimeroPtr->izquierda = UltimoPtr;  
                tamano++;
            }
        }
            
        
            
           
            
            //Crea el el cuadro
            void createcuadro(int t) 
            {
                
                for (int i = 1; i <= t*t; i++) 
                {
                    InsertAtEnd(0);//crea la lista
                }

                    Nodo *actual = PrimeroPtr;
                    Nodo *temporal = PrimeroPtr;
                    Nodo *lado = PrimeroPtr;

                        for (int pos = 0; pos<t; pos++)
                        {
                            actual = actual->derecha;
                        }

                            for (int j = 1; j <= t*t; j++) 
                            {
                                temporal->abajo = actual;
                                actual->arriba = temporal;

                                if (j == t*t) {
                                    for (int x = 1; x <= t; x++) {
                                        lado->izquierda = actual;
                                        actual->derecha = lado;
                                        actual = actual->abajo;
                                        lado = lado->abajo;
                                    }
                                }
                                temporal = temporal->derecha;
                                actual = actual->derecha;
                            }
            }
       
       
      
       // Inserta en la ultima posicion 
	Nodo * ubicarUltimo(int tamano, int columna, int jugador) 
	{
		Nodo * Actual = PrimeroPtr;

		for (int i = 1; i <= columna - 1; i++) {
			Actual = Actual->derecha;
		}
		for (int j = 1; j <= tamano - 1; j++) {
			if (Actual->abajo->valor == 0) {
				Actual = Actual->abajo;
			}
		}
		if (jugador == 1) {
			Actual->valor = 1;
		}
		else
			Actual->valor = 2;
		return Actual;
	}

	
       
    //Valida si hay ganador
	bool encontrarGanador(Nodo *Actual,int jugador, int columna) 
	{
		
		
		int acertadosHor = 0;
		int acertadosVer = 0;
		int acertadosDiagDer = 0;
		int acertadosDiagIzq = 0;
		int limitValid = 0;

		Nodo* horizontal = Actual;
		Nodo * horizontal2 = Actual;
		Nodo *vertical = Actual;
		Nodo *vertical2 = Actual;
		Nodo *diag = Actual;
		Nodo *diag2 = Actual;
		Nodo *diagIzq = Actual;
		Nodo * diagIzq2 = Actual;

		//Limite de validacion horizontal en el cuadro circular
		limitValid = (sqrt(tamano)) - columna;
		if (limitValid>3)
			limitValid = 3;

		//Valida que gane en forma horizontal
		for (int i = 1; i <= limitValid; i++) 
        {
			if ((horizontal->derecha->valor == jugador) || (horizontal2->izquierda->valor == jugador))
				acertadosHor++;
			horizontal = horizontal->derecha;
			horizontal2 = horizontal2->izquierda;

			if (acertadosHor == 3)
				return true;
		}

		//Valida de forma vertical
		for (int i = 1; i <= limitValid; i++) 
        {
			if (vertical2->abajo->valor == jugador)
				acertadosVer++;
			vertical2 = vertical2->abajo;

			if (acertadosVer == 3)
				return true;
		}

		//Valida de forma diagonal derecha
		for (int i = 1; i <= 3; i++) 
        {
			if ((diag->derecha->arriba->valor == jugador) || (diag2->izquierda->abajo->valor == jugador))
				acertadosDiagDer++;
			diag = diag->derecha->arriba;
			diag2 = diag2->izquierda->abajo;

			if (acertadosDiagDer == 3)
				return true;
		}

		//Valida de forma diagonal izquierda
		for (int i = 1; i <= 3; i++) 
        {
			if ((diagIzq->izquierda->arriba->valor == jugador) || (diagIzq2->derecha->abajo->valor == jugador))
				acertadosDiagIzq++;
			diagIzq = diagIzq->izquierda->arriba;
			diagIzq2 = diagIzq2->derecha->abajo;

			if (acertadosDiagIzq == 3)
				return true;
		}

		return false;
	}     
            
            
               
                
};

        //Clase Jugador para ir guardando la informacion de los dos jugadores
        class jugador
        {
            public:
                    int puntos;
                    string Nombre;
                    int simbolo;
                    
            jugador(string nombre)
            {
                puntos = 0;
                Nombre = nombre;
                simbolo = 0;
            }
            
        };

       
        //Funcion para imprimir el cuadro
        void mostrarCuadro(int dimension,Lista l)
        {
                int total_lados = ((dimension + pow(dimension,3))/2);
                
                cout << "----Columnas----"<<endl;
                cout << "\n";
                
                Nodo *temp1=l.PrimeroPtr;
                Nodo *temp2=l.PrimeroPtr;
                
                for (int i = 1; i<=dimension; i++)
                {
                            
                    for (int j = 1; j<=dimension; j++)
                    {
                                
                        cout<<temp2->valor<<" ";
                        temp2=temp2->derecha;
                    }
                        cout<<" "<<endl;
                        temp1=temp1->abajo;
                        temp2=temp1;
                }
                        
        }
        
        
        //Solicita el tamano del cuadro de juego
        int Solicita_tamano()
        {
            int tamano_recibido;
            cout << "\nIngrese el tamano del cuadrado"<<endl;
            cin >> tamano_recibido;
            
            return tamano_recibido;
        }
        
        //Solicita la columna en la que va ubicar la posicion de su turno
        int solicita_columna(jugador j)
        {
            int n_columna;
            cout << "\nTurno de: " <<j.Nombre<< endl;
            cout << "Ingrese el numero de columna para conectar:"<<endl;
            cin >> n_columna;
            
            return n_columna;
        }
        
        
        //Solicita el nombre de los dos jugadores
        string solicitar_jugadores()
        {
            string nombre;
            cout << "Ingrese el nombre del jugador: " << endl;
            cin >> nombre;
            return nombre; 
        }
        
        
        
        //Muestar el nombre de los jugadores con el puntaje actual del juego
        void mostrar_puntajes(jugador j1,jugador j2)
        {
            
            cout << "\n-------MARCADOR---------"<<endl;
            cout <<"\nJugador: "<<j1.Nombre<<": "<<j1.puntos << endl;
            cout <<"\nJugador: "<<j2.Nombre<<": "<<j2.puntos << endl;
            cout << "\n------------------------"<<endl;
        }
        
        //Funcion para reiniciar los valores del cuadro despues que alguien gane la partida
        void reiniciarCuadro(int dimension,Lista l)
        {
                Nodo *temp1=l.PrimeroPtr;
                Nodo *temp2=l.PrimeroPtr;
                
                for (int i = 1; i<=dimension; i++)
                {
                            
                    for (int j = 1; j<=dimension; j++)
                    {
                                
                        //cout<<temp2->valor<<" ";
                        temp2->valor = 0;
                        temp2=temp2->derecha;
                    }
                        //cout<<" "<<endl;
                        temp1=temp1->abajo;
                        temp2=temp1;
                }
                        
        }
        
        
        
     
        
        
int main()
{   
    system("Color 3A");
    //Declaramos las instancias de objetos que estaremos usando
    Lista l = Lista();
    jugador j1 = jugador(solicitar_jugadores());
    jugador j2 = jugador(solicitar_jugadores());
    
    
    cout << "\nBIENVENIDO AL JUEGO CONECTA 4"<<endl;
    cout << "----0----0----0----0----0----"<< endl;
    
    int tamano = Solicita_tamano();
    l.createcuadro(tamano);
    mostrarCuadro(tamano,l);   
    
    int conta = 0;
    
    while(conta != tamano * tamano)
    {
        int residuo = conta % 2;
        
        if(residuo == 0)
        {
            Nodo *temp = l.ubicarUltimo(tamano,solicita_columna(j1),1);
            mostrarCuadro(tamano,l);
            
            if(l.encontrarGanador(temp,1,1))
            {
                j1.puntos++;
                reiniciarCuadro(tamano,l);
                mostrarCuadro(tamano,l);
            }
                
                
            mostrar_puntajes(j1,j2);
        }
        else
        {
            Nodo *temp = l.ubicarUltimo(tamano,solicita_columna(j2),2);
            mostrarCuadro(tamano,l);
            
            if(l.encontrarGanador(temp,2,1))
            {
                j2.puntos++;
                reiniciarCuadro(tamano,l);
                mostrarCuadro(tamano,l);
            }
                
            mostrar_puntajes(j1,j2);
            
        
        }
        conta++;
    }
    
    }


