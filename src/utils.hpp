#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

namespace Utils {
	template <typename T>
	T lerp(T x, T y, float t) {
		return x * (1.0f - t) + y * t;
	}

	template <typename T>
	T tween(const T &from, const T &to, float speed, double dt) {
		return lerp(from, to, std::fmin(dt * speed, 1.0));
	}
}

#endif
