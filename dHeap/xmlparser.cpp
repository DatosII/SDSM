//#include "xmlparser.h"

///**
// * @brief Constructor
// *
// * Recibe como parametro la ruta del archivo de configuracion
// *
// * @param pPath Ruta del archivo de configuracion
// */
//xmlParser::xmlParser(std::string pPath){
//    _path = pPath;
//    _result= _doc.load_file("/home/diego/Escritorio/xml.xml");
//}


///**
// * @brief Metodo que obtiene los datos de los SDSMMemoryNodes
// *
// * Recorre los nodo del xml donde se encuentran la ip y puerto
// * de las computadoras que comparten memoria
// *
// * @param pList Lista donde se guardan los datos de los SDS
// */
//void xmlParser::getNodes(){
//    for(pugi::xml_node node = _doc.child("SDS").first_child();node;node=node.next_sibling()){
//        std::cout<<(std::string)node.child_value("IP")<<std::endl;
//        std::cout<<(std::string)node.child_value("PUERTO")<<std::endl;
//    }
//}



///**
// * @brief Metodo que obtiene la frecuencia de ejecucion del Garbage Collector
// *
// * @return Frecuencia del GC en nanosegundos
// */
//long xmlParser::getFrecuency(){
//    std::string frecuency = ((std::string)_doc.child("GC").child_value("gc-frecuency"));
//    return atol(frecuency.c_str());
//}



///**
// * @brief Metodo que obtiene la bandera que determina si se muestra informacion de debug
// *
// * @return true si se muestra info, false en caso contrario
// */
//bool xmlParser::getBoolean(){
//    std::string flag = ((std::string)_doc.child("DEBUG").child_value("boolean"));
//    if(flag == "true") return true;
//    else return false;
//}



/////**
//// * @brief Metodo para añadir nuevos SDS al archivo de configuracion
//// *
//// * @param pIp IP de la computadora
//// * @param pPuerto Puerto de la computadora
//// */
////void xmlParser::addNodes(std::string pIp, std::string pPuerto){
////    pugi::xml_node newNode=_doc.child("SDS").append_child("node");
////    pugi::xml_node newIp=newNode.append_child("IP");
////    newIp.append_child(pugi::node_pcdata).set_value(pIp);
////    pugi::xml_node newPort=newNode.append_child("Puerto");
////    newPort.append_child(pugi::node_pcdata).set_value(pPuerto);
////    _doc.save_file(_path);
////}
