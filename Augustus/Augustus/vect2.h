#pragma once
#include <vector>

// thanks Erik Wallin for the idea for the name Vect2,
// even though I read it wrong and it actually said "Vec2"
// also it was a header somewhere, not actually something he did :^)

class Vect2
{
public:
	Vect2();
	Vect2(float p_x, float p_y);
	~Vect2();

	friend bool operator==(const Vect2& p_lhs, const Vect2& p_rhs);
	friend bool operator!=(const Vect2& p_lhs, const Vect2& p_rhs);
	friend bool operator<(const Vect2& p_l, const Vect2& p_r);

	Vect2 operator+=(const Vect2& p_other);
	Vect2 operator-=(const Vect2& p_other);
	Vect2 operator+(const Vect2& p_other);
	Vect2 operator-(const Vect2& p_other);

	float x, y;

	Vect2 Round() const;
	Vect2 Floor() const;
	Vect2 GetOffset() const;
	Vect2 CorrectTeleport() const;

	void GotoX(float p_x, float p_speed);
	void GotoY(float p_y, float p_speed);

	static const Vect2 ZERO;
	static const Vect2 UP;
	static const Vect2 DOWN;
	static const Vect2 LEFT;
	static const Vect2 RIGHT;
	static const std::vector<Vect2> ALL_DIRECTIONS;
};


/*
taken from tutorial
http://en.cppreference.com/w/cpp/utility/hash
*/

namespace std
{
	template<> struct hash<Vect2>
	{
		std::size_t operator()(Vect2 const& p_v) const
		{
			std::size_t const h1(std::hash<float>{}(p_v.x));
			std::size_t const h2(std::hash<float>{}(p_v.y));
			
			return h1 ^ (h2 << 1); // or use boost::hash_combine
		}
	};
}