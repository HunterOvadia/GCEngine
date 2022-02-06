#pragma once

class IGCPlatformInput
{
	friend class IGCPlatform;

public:
	int GetMouseX() { return MouseX; }
	int GetMouseY() { return MouseY; }

private:
	virtual void ProcessMouseInput() = 0;

protected:
	int MouseX;
	int MouseY;
};