#pragma once

static std::string ToLowerString(const std::string& str)
{
	std::string lowered(str);
	std::transform(str.begin(), str.end(), lowered.begin(), tolower);

	return lowered;
}