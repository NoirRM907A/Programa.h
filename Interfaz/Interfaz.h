
#ifndef APP_PROCESAMIENTO_INTERFAZ_H
#define APP_PROCESAMIENTO_INTERFAZ_H

#include "../Programa/Programa.h"

using namespace std;

class Interfaz
{
    private:
        Programa programa;
    public:

        Interfaz()
        {
            this->programa=Programa();
            bool corriendo=true;
            cout << "Bienvenido al programa de carga de datos"<<endl;
            while(corriendo)
            {
                int opcion=0;
                cout<<"1. Cargar datos del archivo pacientes.csv\n"
                      "2. Cargar datos del archivo de enfermedades.csv\n"
                      "3. Generar archivo datos_geneticos.json\n"
                      "4. Salir\n"<<endl;
                while(opcion<1 or opcion>4)
                {
                    cout<<"Seleccione una de las opciones anteriores: "<<endl;
                    cin>>opcion;
                    if(cin.fail())
                    {
                        opcion=0;
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                }
                if(opcion==1)
                {
                    this->programa.loadPacientes();
                    cout<<"\nDetalle de la carga:\n"
                          "\t-Archivo: pacientes.csv\n"
                          "\t-registros encontrados:"+to_string(this->programa.getPacientes().size())
                          +"\n\n "<<endl;

                }
                else if(opcion==2)
                {
                    this->programa.loadEnfermedades();
                    cout<<"\nDetalle de la carga:\n"
                          "\t-Archivo: enfermedades.csv\n"
                          "\t-registros encontrados:"+to_string(this->programa.getEnfermedades().size())
                          +"\n\n "<<endl;
                }
                else if(opcion==3)
                {
                    for(int ind=0;ind<this->programa.getPacientes().size();ind++)
                    {
                        this->programa.setEnfermedadesPorPaciente(ind);
                    }
                    this->programa.jsonSerializer();
                }
                else if(opcion==4)
                {
                    cout<<"Saliendo del programa..."<<endl;
                    corriendo=false;
                }

            }
        }

};


#endif //APP_PROCESAMIENTO_INTERFAZ_H
