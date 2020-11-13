
#include <algorithm>
#include <sstream>
#include "Programa.h"

Programa::Programa()
{
    this->pacientes= vector<Paciente>();
    this->enfermedades=vector<Enfermedad>();
}

void Programa::loadPacientes()
{
    this->pacientes=vector<Paciente>();
    ifstream archivoPacientes("pacientes.csv");
    int lineas=0;
    for( string linea; getline( archivoPacientes, linea ); )
    {
        if(lineas>0)
        {
            replace(linea.begin(), linea.end(), ',', ' ');
            vector<string> info=vector<string>();
            stringstream ss(linea);
            string temp;
            while (ss >> temp)
                info.push_back(temp);

            this->pacientes.push_back(Paciente(info[0],info[1]+" "+info[2],info[3],info[4],info[5]));
        }
        lineas++;
    }
}

void Programa::loadEnfermedades()
{
    this->enfermedades=vector<Enfermedad>();
    ifstream archivoPacientes("enfermedades.csv");
    int lineas=0;
    for( string linea; getline( archivoPacientes, linea ); )
    {
        if(lineas>0)
        {
            replace(linea.begin(), linea.end(), ' ', ':');
            replace(linea.begin(), linea.end(), ',', ' ');
            vector<string> info=vector<string>();
            stringstream ss(linea);
            string temp;
            while (ss >> temp)
                info.push_back(temp);

            replace(info[0].begin(),info[0].end(),':',' ');
            this->enfermedades.push_back(Enfermedad(info[0],info[1]));
        }
        lineas++;
    }

}

vector<Enfermedad> Programa::getEnfermedadesPorPaciente(Paciente paciente)
{
    vector<Enfermedad>salida=vector<Enfermedad>();
    for(int ind=0;ind<this->enfermedades.size();ind++)
    {
        Enfermedad enfermedad=this->enfermedades[ind];
        int pacienteSecuenciaL=paciente.getSecuencia().length();
        int enfermedadSecuenciaL=enfermedad.getSecuencia().length();

        string secuenciaPaciente=paciente.getSecuencia();
        string secuenciaEnfermedad=enfermedad.getSecuencia();

        for(int ind2=0;ind2<pacienteSecuenciaL;ind2++)
        {
            string fragmento="";

            if(secuenciaPaciente[ind2]==secuenciaEnfermedad[0])
            {
                for (int ind3 = ind2; ind3 < ind2 + enfermedadSecuenciaL; ind3++) {
                    if (ind3 > pacienteSecuenciaL) {
                        break;
                    }
                    fragmento += secuenciaPaciente[ind3];
                }
                if (fragmento.length() != enfermedadSecuenciaL) {
                    break;
                }
                if (fragmento == secuenciaEnfermedad) {
                    for (int ind4 = 0; ind4 < salida.size(); ind4++) {
                        if (fragmento == salida[ind4].getSecuencia()) {
                            salida.erase(salida.begin() + ind4);
                        }
                    }
                    salida.push_back(enfermedad);
                }
            }
        }
    }
    return salida;
}

void Programa::jsonSerializer()
{

    json pacientesJson=json::array();
    for(int ind=0;ind<this->pacientes.size();ind++)
    {

        json enfermedadesJson=json::array();
        for(int ind2=0;ind2<this->pacientes[ind].getEnfermedades().size();ind2++)
        {
            Enfermedad enfermedad=this->pacientes[ind].getEnfermedades()[ind2];
            json enfermedadJson=
                    {
                            {"enfermedad",enfermedad.getEnfermedad()},
                            {"secuencia",enfermedad.getSecuencia()}
                    };
            enfermedadesJson.push_back(enfermedadJson);
        }
        Paciente paciente=this->pacientes[ind];
        json pacienteJson=
                {
                        {"id",paciente.getId()},
                        {"nombre",paciente.getNombre()},
                        {"telefono",paciente.getTelefono()},
                        {"correo",paciente.getCorreo()},
                        {"secuencia",paciente.getSecuencia()},
                        {"enfermedades",enfermedadesJson}
                };
        pacientesJson.push_back(pacienteJson);
    }
    json outPutjson={{"pacientes",pacientesJson}};

    string output=outPutjson.dump(4);
    ofstream outfile;
    outfile.open("datos_geneticos.json");

    outfile <<output<< endl;
    outfile.close();

    cout<<"\nArchivo .json generado correctamente!\n"<<endl;

}

vector<Paciente> Programa::getPacientes()
{
    return this->pacientes;
}

vector<Enfermedad> Programa::getEnfermedades()
{
    return this->enfermedades;
}

void Programa::setEnfermedadesPorPaciente(int i)
{
    this->pacientes[i].setEnfermedades(getEnfermedadesPorPaciente(this->pacientes[i]));
}
