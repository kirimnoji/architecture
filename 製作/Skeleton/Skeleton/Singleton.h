#pragma once
class Singleton
{
public:
	static Singleton& Instanse()
	{
		static Singleton instance;
		return instance;
	}
	
	void Out();

private:

	Singleton() {};

	int counter = 0;

	Singleton(const Singleton&) = delete;

};

