#pragma once
#include "Buffer.h"
#include "../../YorkieEngine.h"

class Yorkie VAO : Buffer
{
public: 
	VAO();
	void Bind();
	void Unbind();
	inline unsigned int &GetVAO() { return ID; };
private: 
};

