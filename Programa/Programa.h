
#ifndef APP_PROCESAMIENTO_PROGRAMA_H
#define APP_PROCESAMIENTO_PROGRAMA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "../Entidades/Paciente.h"
#include "../Entidades/Enfermedad.h"
#include "../json.hpp"


using namespace std;



using json=nlohmann::json ;

class Programa
{
    public:
        Programa();
        void loadPacientes();
        void loadEnfermedades();
        vector<Enfermedad> getEnfermedadesPorPaciente(Paciente paciente);
        void jsonSerializer();
        vector<Paciente>getPacientes();
        vector<Enfermedad>getEnfermedades();

    void setEnfermedadesPorPaciente(int i);

private:
        vector<Paciente> pacientes;
        vector<Enfermedad>enfermedades;

};


#endif //APP_PROCESAMIENTO_PROGRAMA_H
