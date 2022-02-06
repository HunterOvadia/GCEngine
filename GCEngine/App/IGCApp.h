#pragma once
#include "../Platform/GCPlatform.h"
#include "../Math/Vector2.h"

class GCENGINE_API IGCApp
{
	friend class IGCPlatform;

public:
	IGCApp() = delete;
	explicit IGCApp(const char* ProgramName, int Width, int Height);
	virtual ~IGCApp() = default;

	virtual bool Initialize(IGCPlatform* Platform) = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

protected:
	IGCPlatform* Platform;
	const char* ProgramName;
	Vector2 WindowSize;
};
