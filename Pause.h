#pragma once
#include "GameObjectTriangle.h"
class Pause : public GameObjectTriangle
{
public:
	virtual void Init() override;
	virtual void FixedStep() override;
	virtual void OnPause() override;

private:
	bool pressed = false;
};

