#include "Sierpinski.h"
#include "Point.h"

Sierpinski::Sierpinski(olc::PixelGameEngine* pge, 
	const double zoomSpeed, 
	const double rotationSpeed)
	: _height(0), 
	_pge(pge), 
	_zoomSpeed(zoomSpeed), 
	_rotationSpeed(rotationSpeed) {
	if (pge != nullptr) {
		CreateMaxSizedTriangle();
		InitValues();
	}
}

/// <summary>
/// Adds rotation in rightward direction.
/// </summary>
void Sierpinski::RotateCW() {
	RotateTriangle(_rotationSpeed);
}

/// <summary>
/// Adds rotation in leftward direction.
/// </summary>
void Sierpinski::RotateCCW() {
	RotateTriangle(-_rotationSpeed);
}

/// <summary>
/// Increases magnification.
/// </summary>
void Sierpinski::ZoomIn() {
	ZoomTriangle(1.00 + _zoomSpeed);
}

/// <summary>
/// Decreases magnification.
/// </summary>
void Sierpinski::ZoomOut() {
	ZoomTriangle(1.0 - _zoomSpeed);
}

void Sierpinski::ZoomTriangle(const double zoomFactor) {
	// Now apply zoom relative to the center (_center)
	_top = _center + (_top - _center) * zoomFactor;
	_bottomRight = _center + (_bottomRight - _center) * zoomFactor;
	_bottomLeft = _center + (_bottomLeft - _center) * zoomFactor;
	_height *= zoomFactor;
	_pge->Clear(olc::BLACK);
	Draw();
}

void Sierpinski::RotateTriangle(const double angle) {
	_top = RotatePoint(_top, angle);
	_bottomLeft = RotatePoint(_bottomLeft, angle);
	_bottomRight = RotatePoint(_bottomRight, angle);
	_pge->Clear(olc::BLACK);
	Draw();
}

Point Sierpinski::AsPoint(const olc::vi2d position) const
{
	return { static_cast<double>(position.x), 
		static_cast<double>(position.y) };
}

/// <summary>
/// Lets us set display values after object initialization.
/// </summary>
inline void Sierpinski::InitValues() {
	_center = {
		(_top.x + _bottomLeft.x + _bottomRight.x) / 3,
		(_top.y + _bottomLeft.y + _bottomRight.y) / 3,
	};
}

// Finds midpoint on imaginary line between two coordinates.
inline constexpr olc::vi2d Sierpinski::Mid(const olc::vi2d p1, 
	const olc::vi2d p2)
{
	return p1.lerp(p2, 0.5f);
}

inline constexpr Point Sierpinski::Mid(const Point p1, const Point p2)
{
	return { (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 };
}

// Compute expensive square root function to a constant.
inline constexpr float Sierpinski::TriangleRatio() {
	return std::numbers::sqrt3_v<float> / 2.0f;
}

/// <summary>
/// Fit the largest possible Sierpinski triangle into available space.
/// </summary>
/// <param name="margin">Surrounding blank-space margin, if desired.</param>
inline void Sierpinski::CreateMaxSizedTriangle(const double margin) {
	// Get screen dimensions minus margins
	const double availableHeight = _pge->ScreenHeight() - 2 * margin;
	const double availableWidth = _pge->ScreenWidth() - 2 * margin;

	// In an equilateral triangle, height is (sqrt(3) / 2) * base
	constexpr float heightToBaseRatio = TriangleRatio();

	// Calculate the maximum base and height that fit within the available space
	double maxBase = static_cast<double>(availableWidth);
	double maxHeight = maxBase * heightToBaseRatio;

	// Adjust base if height is too large to fit within screen
	if (maxHeight > availableHeight) {
		maxHeight = availableHeight;
		maxBase = static_cast<int32_t>(maxHeight / heightToBaseRatio);
	}

	// Set the triangle's vertices
	_top = { static_cast<double>(_pge->ScreenWidth() / 2),
		static_cast<double>(margin) }; // Top is centered horizontally

	_bottomLeft = { (_pge->ScreenWidth() - maxBase) / 2, margin + maxHeight };
	_bottomRight = { (_pge->ScreenWidth() + maxBase) / 2, margin + maxHeight };

	// Store height value to end recursion and apply correct color.
	_height = maxHeight;
}

/// <summary>
/// Entrypoint for the DrawSierpinski method.
/// </summary>
void Sierpinski::Draw() {
	DrawSierpinski(_top, 
		_bottomLeft, 
		_bottomRight, 
		_height, 
		1.0, 
		olc::WHITE);
}

/// <summary>
/// Recursive method to compute the Sierpinski triangle (split triangle into four triangles,
/// then run the same method on the three corner triangles, ignoring the center one).
/// </summary>
/// <param name="top">Unambiguous.</param>
/// <param name="bottomLeft">Unambiguous.</param>
/// <param name="bottomRight">Unambiguous.</param>
/// <param name="height">How tall the triangle is, or ought to be.</param>
/// <param name="outlineColor">What color the outline should be in.</param>
void Sierpinski::DrawSierpinski(const Point top, 
	const Point bottomLeft, 
	const Point bottomRight, 
	const double height, 
	const double zoomFactor, 
	const olc::Pixel outlineColor,
	const int iterationCount)
{
	auto fillColor = colorRamp[iterationCount % 16];
	auto heightNextTriangle = height / 2; // Termination clause for recursion.

	// New triangle midpoints (without zoom)
	Point midLeft = Mid(top, bottomLeft);
	Point midRight = Mid(top, bottomRight);
	Point midBottom = Mid(bottomLeft, bottomRight);
	Point center = Mid(midLeft, midRight);

	// Fill middle triangle with background color.
	_pge->FillTriangle(midLeft.AsVi2d(), 
		midRight.AsVi2d(),
		midBottom.AsVi2d(), 
		fillColor);

	// Then draw outlines.
	_pge->DrawLine(top.AsVi2d(), bottomLeft.AsVi2d(), outlineColor);
	_pge->DrawLine(top.AsVi2d(), bottomRight.AsVi2d(), outlineColor);
	_pge->DrawLine(bottomLeft.AsVi2d(), bottomRight.AsVi2d(), outlineColor);

	if (heightNextTriangle > 5) { // How to end recursion.
		DrawSierpinski(top, 
			midLeft, 
			midRight, 
			heightNextTriangle, 
			zoomFactor, 
			outlineColor, 
			iterationCount+1);
		DrawSierpinski(midLeft, 
			bottomLeft, 
			midBottom, 
			heightNextTriangle, 
			zoomFactor, 
			outlineColor, 
			iterationCount+1);
		DrawSierpinski(midRight, 
			midBottom, 
			bottomRight, 
			heightNextTriangle, 
			zoomFactor, 
			outlineColor, 
			iterationCount+1);
	}
}

Point Sierpinski::RotatePoint(Point p, const double angleDegrees) const {
	double angleRadians = angleDegrees * PI / 180.0;
	double s = sin(angleRadians);
	double c = cos(angleRadians);

	// Translate point back to origin
	p.x -= _center.x;
	p.y -= _center.y;

	// Rotate point
	double xnew = p.x * c - p.y * s;
	double ynew = p.x * s + p.y * c;

	// Translate point back
	p.x = xnew + _center.x;
	p.y = ynew + _center.y;

	return p;
}

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
