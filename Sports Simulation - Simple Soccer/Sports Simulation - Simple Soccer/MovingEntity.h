#pragma once
#include <iostream>


class MovingEntity
{
public:
	MovingEntity();

	void Update();

	void Render();

	bool HandleMessage(std::string telegram);
};