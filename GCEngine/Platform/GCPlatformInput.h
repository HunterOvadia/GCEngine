#pragma once

class IGCPlatformInput
{
	friend class IGCPlatform;

public:
	virtual ~IGCPlatformInput() = default;
	int GetMouseX() const { return MouseX; }
	int GetMouseY() const { return MouseY; }

private:
	virtual void ProcessMouseInput() = 0;

protected:
	int MouseX;
	int MouseY;
};