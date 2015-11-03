#pragma once

enum class message {
	no_input_file = 1,
};

template<class T>
T Error (const int errn, const std::string &s1 = "", const std::string &s2 = "");
