#include <iostream>
#include "_ptam.h"

int main() {
    DataStore* obj = new DataStore();
    std::string stateDescript = "ARMED";
    int count = 10;
    double value = 3.14;

    obj->storeData("stateDescript", stateDescript);
    obj->storeData("count", count);
    obj->storeData("value", value);

    std::vector<std::string> stringData = obj->getStringData("stateDescript");
    for (const std::string& element : stringData) {
        std::cout << element << std::endl;
    }

    std::vector<int> intData = obj->getIntData("count");
    auto var = intData.back();
    std::cout << var << std::endl;

    std::vector<double> doubleData = obj->getDoubleData("value");
    for (const double& element : doubleData) {
        std::cout << element << std::endl;
    }

    return 0;
}