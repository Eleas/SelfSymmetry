#include <numbers>
#include "olcPixelGameEngine.h"
#include "Point.h"

#pragma once
class Sierpinski
{
public:
	Sierpinski(olc::PixelGameEngine* pge = nullptr);
	void InitValues();
	void Draw();
	void RotateCW();
	void RotateCCW();
	void ZoomIn();
	void ZoomOut();

private:
	// Fields and constants.
	const double PI = 3.14159266535;
	Point _top = { 0.0, 0.0 };
	Point _bottomLeft = { 0.0, 0.0 };
	Point _bottomRight = { 0.0, 0.0 };
	Point _center = { 0.0, 0.0 };
	double _height = 0.0;
	olc::Pixel _outlineColor = olc::WHITE;
	olc::PixelGameEngine* _pge;

private:
	// Color ramp.
	olc::Pixel colorRamp[16] = {
	olc::DARK_GREEN,
	olc::VERY_DARK_GREY,
	olc::RED,
	olc::DARK_GREY,
	olc::DARK_RED,
	olc::VERY_DARK_RED,
	olc::DARK_YELLOW,
	olc::VERY_DARK_YELLOW,
	olc::GREEN,
	olc::VERY_DARK_GREEN,
	olc::CYAN,
	olc::DARK_CYAN,
	olc::VERY_DARK_CYAN,
	olc::BLUE,
	olc::VERY_DARK_MAGENTA,
	olc::DARK_CYAN
	};

private:
	// Methods and functions
	inline static constexpr olc::vi2d Mid(const olc::vi2d p1, const olc::vi2d p2);
	inline static constexpr Point Mid(const Point p1, const Point p2);
	void DrawSierpinski (const Point top, const Point bottomLeft, const Point bottomRight, const double height, const double zoomFactor, const olc::Pixel outlineColor = olc::WHITE);
	inline static constexpr float TriangleRatio();
	void CreateMaxSizedTriangle(const double margin = 0);
	void RotateTriangle(const double angle);
	void ZoomTriangle(const double zoomFactor);
	Point AsPoint(const olc::vi2d position) const;
	Point RotatePoint(Point p, const double angleDegrees) const;
};

/*
	Permission is hereby granted, free of charge, to any person obtaining a 
	copy of this software and associated documentation files (the “Software”), 
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense, 
	and/or sell copies of the Software, and to permit persons to whom the 
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included 
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
	DEALINGS IN THE SOFTWARE.

	--

	It's a shame that US legislation saw fit to empower such terrible people.
*/
