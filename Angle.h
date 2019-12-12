#pragma once
#include "MathBaseInclude.h"

namespace Math
{
	class Angle
	{
	public:
		Angle() {}
		float asRadian() const
		{
			return M_PI * degree / 180.;
		}
		float asDegree() const
		{
			return degree;
		}

		inline float sin() const
		{
			return ::sin(asRadian());
		}
		inline float cos() const
		{
			return ::cos(asRadian());
		}

		void operator+=(Angle other)
		{
			degree += other.degree;
		}
		void operator-=(Angle other)
		{
			degree -= other.degree;
		}

		void operator*=(float other)
		{
			degree *= other;
		}
		void operator/=(float other)
		{
			degree /= other;
		}

		Angle operator+(Angle other)
		{
			return { degree + other.degree };
		}
		Angle operator-(Angle other)
		{
			return { degree - other.degree };
		}

		Angle operator*(float other)
		{
			return { degree * other };
		}
		Angle operator/(float other)
		{
			return { degree / other };
		}

	private:
		Angle(float v) : degree(v) {}
		float degree = 0;
		friend Angle Radian(float v);
		friend Angle Degree(float v);
	};
	inline Angle Radian(float v) { return { (float)(v / M_PI * 180.) }; }
	inline Angle Degree(float v) { return { v }; }
}