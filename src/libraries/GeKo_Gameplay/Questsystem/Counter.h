#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

class Counter 
{
public: 
	Counter();
	Counter(float time);
	~Counter();

	void setTime(float time);
	float getTime();

	void start();

	void end();

	void update();

protected:
	float m_time;
	bool m_started;
	bool m_finished;
	int m_frame;
};