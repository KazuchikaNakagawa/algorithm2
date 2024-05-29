#ifndef DATA_PROVIDER_H
#define DATA_PROVIDER_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Data {
    std::string word;
    int identifier;
    std::vector<Data*> links;

    int size() const
    {
        return links.size();
    }
    Data() = default;
    friend class DataProvider;
};

class DataProvider {
    std::map<int, Data> data;

public:
    DataProvider(std::string dataDir)
    {
        for (int i = 0; i < 120; i++) {
            std::ifstream file(dataDir + "/vertex" + std::to_string(i) + ".csv");
            if (!file) {
                continue;
            }
            std::string buf;
            std::getline(file, buf, ',');
            data[i].word = buf;
            data[i].identifier = i;
            int linkN;
            std::getline(file, buf, ',');
            // std::cout << i << ".linkN: " << buf << std::endl;
            linkN = std::stoi(buf);
            for (int j = 0; j < linkN; j++) {
                int link;
                std::getline(file, buf, j != linkN - 1 ? ',' : '\n');
                link = std::stoi(buf);
                data[i].links.push_back(&data[link]);
            }
        }
    }

    Data* operator[](int i)
    {
        return &data[i];
    }
};

#endif /* DATA_PROVIDER_H */