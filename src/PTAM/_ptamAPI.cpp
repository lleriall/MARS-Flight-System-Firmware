#include"_ptamAPI.h"

uint8_t PTAM::PTAM_ADD_BASE_DOUBLE(std::string baseID,double data){
    DataStore *obj = new DataStore();
    obj -> storeData(baseID,data);
    delete obj;
    return sizeof(data);
}

uint8_t PTAM::PTAM_ADD_BASE_INT(std::string baseID, uint16_t data){
    DataStore *obj = new DataStore();
    obj -> storeData(baseID, data);
    delete obj;
    return sizeof(data);
}

uint8_t PTAM::PTAM_ADD_BASE_CHAR(std::string baseID, std::string data){
    DataStore *obj = new DataStore();
    obj -> storeData(baseID, data);
    delete obj;
    return sizeof(data);
}

std::vector<std::string> PTAM::PTAM_RETRIEVE_BASE_CHAR(std::string baseID){
    DataStore *obj = new DataStore();
    std::vector<std::string> id_data = obj -> getData<std::string>(baseID);
    delete obj;
    //Return the vector
    return id_data;
}

std::vector<int16_t> PTAM::PTAM_RETRIEVE_BASE_INT(std::string baseID){
    DataStore *obj = new DataStore();
    std::vector<int16_t> id_data  = obj -> getData<int16_t>(baseID);
    delete obj;
    //Return the vector
    return id_data;
}

std::vector<double> PTAM::PTAM_RETRIEVE_BASE_DOUBLE(std::string baseID){
    DataStore *obj = new DataStore();
    std::vector<double> id_data = obj -> getData<double>(baseID);
    delete obj;
    //Return the vector
    return id_data;
}

void PTAM::PTAM_CLEAR_ALL(){
    DataStore *obj = new DataStore();
    obj -> clearData();
    delete obj;
}
