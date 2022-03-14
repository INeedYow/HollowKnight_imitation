#pragma once

struct iPoint
{
	int x;
	int y;

	iPoint()
	{
		x = 0;
		y = 0;
	}
	iPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

struct fPoint
{
	float x;
	float y;

	fPoint()
	{
		x = 0.f;
		y = 0.f;
	}
	fPoint(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	fPoint& operator=(const fPoint& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	fPoint operator+(fPoint other)
	{
		return fPoint(x + other.x, y + other.y);
	}

	fPoint operator-(fPoint other)
	{
		return fPoint(x - other.x, y - other.y);
	}

	bool operator==(fPoint other)
	{
		return (x == other.x && y == other.y);
	}

	bool operator!=(fPoint other)
	{
		return !(*this == other);
	}

	template <typename T>
	fPoint operator*(T num)
	{
		return fPoint(x * num, y * num);
	}

	template <typename T>
	fPoint operator/(T num)
	{
		assert(0 != num);

		return fPoint(x / num, y / num);
	}

	fPoint& normalize()
	{	// sqrt : Á¦°ö±Ù ÇÔ¼ö
		float length = (float)sqrt((double)x * x + (double)y * y);

		if (0 == length)
		{
			x = 0;
			y = 0;
		}
		else
		{
			x = x / length;
			y = y / length;
		}

		return *this;
	}

	float length()
	{
		return (float)sqrt((double)x * x + (double)y * y);
	}
};

typedef iPoint iVec2;
typedef fPoint fVec2;