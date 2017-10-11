#include "Codefights.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <Windows.h> 
#include <Psapi.h>

float		Codefights::maxUsedRam = 0;
bool		Codefights::programEnded = false;
Codefights	*Codefights::instance = nullptr;
HANDLE		Codefights::handle;

Codefights::Codefights()
{
}

void Codefights::checkRam()
{
	float currRam, basicVarSize = sizeof(PROCESS_MEMORY_COUNTERS) + (sizeof(float) * 3) +
		sizeof(HANDLE) + sizeof(bool) + sizeof(Codefights*) +
		sizeof(Codefights);
	PROCESS_MEMORY_COUNTERS pmc;
	while (!programEnded)
	{
		GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
		currRam = (((float)pmc.WorkingSetSize - basicVarSize) / 1024.f) / 1024.f;
		if (currRam > maxUsedRam)
			maxUsedRam = currRam;
	}
	std::cout << "\nMaxmimum RAM used during execution in MB: " << maxUsedRam;
}

Codefights::~Codefights()
{
	delete instance;
}

void Codefights::start(const int& exNum)
{
	auto time = std::chrono::system_clock::now();
	handle = GetCurrentProcess();
	std::thread f(checkRam);
	f.detach();
	int random = rand();
	int *randomData = new int[random];
	for (int i = random; i--;)
		randomData[i] = rand();
	main(random, randomData);
	programEnded = true;
	float timeN = (std::chrono::duration<double>(std::chrono::system_clock::now() - time)).count();
	std::cout << std::endl << "\nExecution time was: " << timeN << " seconds." << std::endl;
	system("pause");
}
