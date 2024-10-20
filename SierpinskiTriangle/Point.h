#pragma once
struct Point
{
    double x;
    double y;

    // Convert Point to olc::vi2d
    inline constexpr olc::vi2d AsVi2d() const {
        return { static_cast<int32_t>(x), static_cast<int32_t>(y) };
    }

    Point operator+(const Point& other) const {
        return { x + other.x, y + other.y };
    }

    Point operator-(const Point& other) const {
        return { x - other.x, y - other.y };
    }

    Point operator*(double scalar) const {
        return { x * scalar, y * scalar };
    }
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
