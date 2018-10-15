//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_XMLREADER_H
#define PROJECT_SWA_XMLREADER_H
#include <iostream>
#include <string>
#include <memory>
#include "tinyxml2.h"
#include "MyDocument.h"

using namespace tinyxml2;

class XMLReader
{
private:
    void ReadRecursively(XMLElement & elem, MyNode& parent);
public:
    XMLReader();
    ~XMLReader();

    std::unique_ptr<MyDocument> LoadFile(string file_name);
    std::unique_ptr<MyDocument> ReadXMLFile(XMLDocument& doc);
};
#endif //PROJECT_SWA_XMLREADER_H