#pragma once

class Core
{
public:
	static void Initialize();
	static void Run();
	static void Finalize();

protected:
	Core();
	~Core();
};
