/*MIT License
Copyright (c) 2023 limitless Aeronautics
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "_ptam.h"

std::unordered_map<std::string, std::vector<void*>>* DataStore::data_map = nullptr;

template<typename T>
void DataStore::storeData(const std::string& id, T data) {
    if (!data_map) {
        data_map = new std::unordered_map<std::string, std::vector<void*>>();
    }
    (*data_map)[id].push_back(new T(data));
}

template<typename T>
std::vector<T> DataStore::getData(const std::string& id) {
    std::vector<T> results;
    if (data_map && data_map->count(id) > 0) {
        for (void* ptr : (*data_map)[id]) {
            T* data_ptr = static_cast<T*>(ptr);
            results.push_back(*data_ptr);
        }
    }
    return results;
}

void DataStore::clearData() {
    if (data_map) {
        for (auto& pair : *data_map) {
            for (void* ptr : pair.second) {
                delete static_cast<int*>(ptr);
            }
        }
        delete data_map;
        data_map = nullptr;
    }
}

DataStore::~DataStore() {
    clearData();
}
