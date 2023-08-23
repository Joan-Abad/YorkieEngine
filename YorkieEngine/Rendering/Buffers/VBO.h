#pragma once
#include "Buffer.h"
#include <vector>
#include "../../YorkieEngine.h"

class YorkieAPI VBO : public Buffer
{
public:
    //If VAO is overrided with a value, it will bind to that VAO before generating the VBO. 
    VBO(std::vector<float>& data, int layout, unsigned int VAO, unsigned int &layoutIndex);
    

    ~VBO();
};

