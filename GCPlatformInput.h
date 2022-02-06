#pragma once

class IGCPlatformInput
{
public:
	virtual void ProcessMouseInput() = 0;

protected:
	int MouseX;
	int MouseY;
};