#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "Pugi/pugiconfig.hpp"
#include "pugixml.hpp"
#include "Pugi/pugixml.cpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file xmlparser.h
 * @brief Clase que lee y escribe el xml
 * @author Gerald Francisco Mora
 * @date 11/9/2015
 */

class xmlParser{
private:
    std::string _path; //Path del archivo de configuracion
    pugi::xml_document _doc; //Documento donde se carga el archivo
    pugi::xml_parse_result _result;
public:
    xmlParser(std::string pPath); //Constructor
    void getNodes(/**LinkedList *pList*/); //Obtiene la lista de SDS Nodes a los que se debe conectar
    long getFrecuency(); //Metodo para obtener la frecuancia de GC
    bool getBoolean(); //Metodo para obtener el estado de la flag para el debug
    void addNodes(std::string pPI, std::string pPuerto); //Metodo para añadir mas SDS nodes
};

#endif // XMLPARSER_H
