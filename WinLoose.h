#pragma once
#include "GameObjectTriangle.h"
class Ball;
class WinLoose : public GameObjectTriangle
{
public:
	virtual void Init() override;
	virtual void FixedStep() override;
	virtual void OnPause() override;

	Ball* ball;
};

