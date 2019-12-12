#pragma once
#include "GameObjectTriangle.h"

class Border : public GameObjectTriangle
{
	virtual void Init() override;
	virtual void FixedStep() override;
	virtual void OnPause() override;
};

