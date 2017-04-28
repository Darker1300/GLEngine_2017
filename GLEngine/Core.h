#pragma once

class Core
{
public:
	static void Initialize();
	static void Finalize();
	static void Run();

protected:
	Core();
	~Core();
};
