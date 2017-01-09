#pragma once
#include <vector>

class Vect2
{
public:
	Vect2();
	Vect2(float p_x, float p_y);
	~Vect2();

	bool operator==(const Vect2& p_other);
	bool operator!=(const Vect2& p_other);
	//bool operator<(const Vect2& p_other);
	//bool operator>(const Vect2& p_other);

	friend bool operator<(const Vect2& l, const Vect2& r);

	Vect2 operator+=(const Vect2& p_other);
	Vect2 operator-=(const Vect2& p_other);
	Vect2 operator+(const Vect2& p_other);
	Vect2 operator-(const Vect2& p_other);

	float x, y;

	static const Vect2 ZERO;

	Vect2 Round() const;
	Vect2 Floor() const;
	Vect2 GetOffset() const;
	Vect2 CorrectTeleport() const;

	void GotoX(float p_x, float p_speed);
	void GotoY(float p_y, float p_speed);

	static const Vect2 UP;
	static const Vect2 DOWN;
	static const Vect2 LEFT;
	static const Vect2 RIGHT;
	static const std::vector<Vect2> ALL_DIRECTIONS;
};

