#pragma once
#include "../Utility/RGBColor.h"
#include <type_traits>
#include <array>

//color
const RGBColor black(0.0);
const RGBColor white(1.0);
const RGBColor red(1.0, 0.0, 0.0);

//math
constexpr double 	PI = 3.1415926535897932384;
constexpr double    TWO_PI = 2 * PI;
constexpr double    INVPI = 0.3183098861837906715;
constexpr double    INVTWOPI = 1 / TWO_PI;
constexpr double    PI_ON_180 = PI / 180;

constexpr double kHugeValue = 1.0E10;
constexpr double kEpsilon = 0.0001;

//for torus
constexpr double EQN_EPS = 1e-9;

template < class T, std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr >
bool IsZero(T x) 
{ 
	return (x > -EQN_EPS) && (x < EQN_EPS);
}

template < class T, std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr >
bool cbrt(T x)
{
	return ((x) > 0.0 ? std::pow(x, 1.0 / 3.0) :
		((x) < 0.0 ? -std::pow(-(x), 1.0 / 3.0) : 0.0));
}

int SolveQuadric(std::array<double, 3> c, std::array<double, 2>& s);
int SolveCubic(std::array<double, 4> c, std::array<double, 3>& s);
int SolveQuartic(std::array<double, 5> c, std::array<double, 4>& s);