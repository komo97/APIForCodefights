#pragma once

class Codefights
{
private:
	Codefights();
	static Codefights* instance;
	void main(int argc, int* args);
	static void checkRam();
	static float		maxUsedRam;
	static bool			programEnded;
	static void*		handle;
public:
	~Codefights();
	static Codefights* getInstance() 
		{ return instance == nullptr ? instance = new Codefights() : instance; }
	void start(const int& exNum);
};

