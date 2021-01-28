
/*
 * @author WardenAllen
 * @date   2020/09/11 10:23:30
 * @brief
 */

#include "string_util.h"

namespace pluto
{
namespace util
{

void replace_characters(std::string& s, const char* remove, char replace) {
	const char* str_start = s.c_str();
	const char* str = str_start;
	for (str = strpbrk(str, remove);
		str != nullptr;
		str = strpbrk(str + 1, remove)) {
		s[str - str_start] = replace;
	}
}

void strip_white_space(std::string& str) {
	int str_length = (int)str.length();

	// Strip off leading whitespace.
	int first = 0;
	while (first < str_length && ascii_isspace(str.at(first))) {
		++first;
	}
	// If entire string is white space.
	if (first == str_length) {
		str.clear();
		return;
	}

	if (first > 0) {
		str.erase(0, first);
		str_length -= first;
	}

	// Strip off trailing whitespace.
	int last = str_length - 1;
	while (last >= 0 && ascii_isspace(str.at(last))) {
		--last;
	}

	if (last != (str_length - 1) && last >= 0) {
		str.erase(last + 1, std::string::npos);
	}
}

void string_replace(const std::string& s, 
					const std::string& oldsub, 
					const std::string& newsub, 
					bool replace_all, 
					std::string& res) {

	if (oldsub.empty()) {
		// if empty, append the given string.
		res.append(s);
		return;
	}

	std::string::size_type start_pos = 0;
	std::string::size_type pos;
	do {
		pos = s.find(oldsub, start_pos);
		if (pos == std::string::npos) {
			break;
		}
		res.append(s, start_pos, pos - start_pos);
		res.append(newsub);
		start_pos = pos + oldsub.size();
		// start searching again after the "old"
	} while (replace_all);
	res.append(s, start_pos, s.length() - start_pos);
}

std::string string_replace(const std::string& s, 
						   const std::string& oldsub, 
						   const std::string& newsub, 
						   bool replace_all) {
	std::string ret;
	string_replace(s, oldsub, newsub, replace_all, ret);
	return ret;
}

void split_string(std::string& src, char delim, std::vector<std::string>& v)
{
	_split_string<char>(src, delim, v);
}

void split_string(std::string& src, std::string& delim, std::vector<std::string>& v)
{
	_split_string<std::string&>(src, delim, v);
}

void split_string_unchanged(std::string src, char delim, std::vector<std::string>& v)
{
	_split_string<char>(src, delim, v);
}

void split_string_unchanged(std::string src, std::string& delim, std::vector<std::string>& v)
{
	_split_string<std::string&>(src, delim, v);
}

void split_string_m(std::string& str, char d1, char d2, std::unordered_map<std::string, std::string>& ret)
{
	_split_string_m(str, d1, d2, ret);
}

void split_string_m(std::string& str, std::string d1, std::string d2, std::unordered_map<std::string, std::string>& ret)
{
	_split_string_m<std::string&>(str, d1, d2, ret);
}

void split_string_unchanged_m(std::string str, char d1, char d2, std::unordered_map<std::string, std::string>& ret)
{
	_split_string_m(str, d1, d2, ret);
}

void split_string_unchanged_m(std::string str, std::string d1, std::string d2, std::unordered_map<std::string, std::string>& ret)
{
	_split_string_m<std::string &>(str, d1, d2, ret);
}

void split_string_m(std::string& str, char d1, char d2, std::map<std::string, std::string>& ret)
{
	_split_string_m(str, d1, d2, ret);
}

void split_string_m(std::string& str, std::string d1, std::string d2, std::map<std::string, std::string>& ret)
{
	_split_string_m<std::string&>(str, d1, d2, ret);
}

void split_string_unchanged_m(std::string str, char d1, char d2, std::map<std::string, std::string>& ret)
{
	_split_string_m(str, d1, d2, ret);
}

void split_string_unchanged_m(std::string str, std::string d1, std::string d2, std::map<std::string, std::string>& ret)
{
	_split_string_m<std::string&>(str, d1, d2, ret);
}

} // util
} // pluto