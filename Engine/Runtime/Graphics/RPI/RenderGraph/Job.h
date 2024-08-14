#pragma once

class Step;

class Job
{
public:
	Job(const Step& s);
	void Execute();
private:
	//const Drawable* const drawable;
	const Step* step;
};