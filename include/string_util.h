#pragma once

/*
 * @author WardenAllen
 * @date   2020/09/11 10:23:30
 * @brief  
 */

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <string.h>

#include "define.h"

namespace pluto
{
namespace util
{

/**
* @brief  Check if an ASCII character is alphanumeric.  We can't use ctype's
*		  isalnum() because it is affected by locale.  This function is applied
*		  to identifiers in the protocol buffer language, not to natural-language
*		  strings, so locale should not be taken into account.
*/
inline bool ascii_isalnum(char c) {
	return ('a' <= c && c <= 'z') ||
		   ('A' <= c && c <= 'Z') ||
		   ('0' <= c && c <= '9');
}

inline bool ascii_isdigit(char c) {
	return ('0' <= c && c <= '9');
}

inline bool ascii_isspace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || 
		c == '\v' || c == '\f' || c == '\r';
}

inline bool ascii_isupper(char c) {
	return c >= 'A' && c <= 'Z';
}

inline bool ascii_islower(char c) {
	return c >= 'a' && c <= 'z';
}

inline char ascii_toupper(char c) {
	return ascii_islower(c) ? c - ('a' - 'A') : c;
}

inline char ascii_tolower(char c) {
	return ascii_isupper(c) ? c + ('a' - 'A') : c;
}

inline int hex_digit_to_int(char c) {
	/* Assume ASCII. */
	int x = static_cast<unsigned char>(c);
	if (x > '9') {
		x += 9;
	}
	return x & 0xf;
}

/**
* @brief  Replaces any occurrence of the character 'remove' (or the characters
*		  in 'remove') with the character 'replace'.
*/

void replace_characters(std::string& s, const char* remove, char replace);

void strip_white_space(std::string& str);

/**
* @brief  Replace the "old" pattern with the "new" pattern in a string,
*		  and append the result to "res".  If replace_all is false,
*		  it only replaces the first instance of "old."
*/
void string_replace(const std::string& s, 
					const std::string& oldsub,
					const std::string& newsub, 
					bool replace_all,
					std::string& res);

std::string string_replace(const std::string& s, 
						   const std::string& oldsub,
						   const std::string& newsub, 
						   bool replace_all);

template <class DelimType>
void _split_string(std::string& src, 
				   DelimType delim, 
				   std::vector<std::string>& v)
{
	int pos = (int)src.find(delim);

	while (-1 != pos)
	{
		std::string s = src.substr(0, pos);
		v.emplace_back(s);
		src = src.substr(pos + 1);
		pos = (int)src.find(delim);
	}

	v.emplace_back(src);
}

template <class DelimType, class Ret>
void _split_string_m(std::string& str,
					  DelimType d1,
					  DelimType d2,
					  Ret& ret)
{
	int pos1 = 0;
	pos1 = (int)str.find(d1);
	while (-1 != pos1)
	{
		std::string temp = str.substr(0, pos1);
		if (temp.length() > 0) {
			int pos2 = (int)temp.find(d2);
			if (pos2 != -1) {
				ret[temp.substr(0, pos2)] = temp.substr(pos2 + 1);
			}
			else {
				ret[temp] = "";
			}
		}
		str = str.substr(pos1 + 1);
		pos1 = (int)str.find(d1);
	}

	if (str.length() > 0) {
		int pos2 = (int)str.find(d2);
		if (pos2 != -1) {
			ret[str.substr(0, pos2)] = str.substr(pos2 + 1);
		}
		else {
			ret[str] = "";
		}
	}
}

/* WARNING: source string will be changed after split. */
void split_string(std::string& src, char delim, 
	std::vector<std::string>& v);

void split_string(std::string& src, std::string& delim, 
	std::vector<std::string>& v);

void split_string_unchanged(std::string src, char delim, 
	std::vector<std::string>& v);

void split_string_unchanged(std::string src, 
	std::string& delim, std::vector<std::string>& v);

void split_string_m(std::string& str, char d1, char d2, 
	std::unordered_map<std::string, std::string>& ret);

void split_string_m(std::string& str, std::string d1, std::string d2,
	std::unordered_map<std::string, std::string>& ret);

void split_string_unchanged_m(std::string str, char d1, char d2,
	std::unordered_map<std::string, std::string>& ret);

void split_string_unchanged_m(std::string str, std::string d1, 
	std::string d2, std::unordered_map<std::string, std::string>& ret);

void split_string_m(std::string& str, char d1, char d2,
	std::map<std::string, std::string>& ret);

void split_string_m(std::string& str, std::string d1, std::string d2,
	std::map<std::string, std::string>& ret);

void split_string_unchanged_m(std::string str, char d1, char d2,
	std::map<std::string, std::string>& ret);

void split_string_unchanged_m(std::string str, std::string d1,
	std::string d2, std::map<std::string, std::string>& ret);

} // time
} // pluto
