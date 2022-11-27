#pragma once
#include <chrono>


template <std::size_t FPS>
class FPSHandler {
private:
	std::chrono::duration<int64_t, std::ratio<1, FPS>> delta_;
	std::chrono::time_point<std::chrono::steady_clock, decltype(delta_)> cur_tp_;

public:
	FPSHandler() : delta_{1}, cur_tp_(std::chrono::time_point_cast<decltype(delta_)>(std::chrono::steady_clock::now())) {
	}

	void sleep() {
		cur_tp_ += delta_;
		std::this_thread::sleep_until(cur_tp_);
	}
};
