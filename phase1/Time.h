#pragma once

class Time
{

	int day;
	float hour;

	// Utility Functions (can be public for testing)


public:

	Time();
	Time(float hours);
	Time(int day, float hours);

	void incrementDay();
	void incrementHour();

	void setDay(int d);
	void setHour(float h);

	int getDay() const;
	int getHour() const;

	int timeInHours() const;

	bool operator == (const Time &other);
	bool operator > (const Time& other);
	bool operator >= (const Time& other);
	bool operator <= (const Time& other);
	bool operator < (const Time& other);
	Time operator + (const Time& other);
	Time operator - (const Time& other);

	void print(bool newLine = true);

	~Time();

};

