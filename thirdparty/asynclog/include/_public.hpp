#ifndef PUBLIC_HPP
#define PUBLIC_HPP

#include <_include.h>

namespace lxybx
{
	//==============================================<< 字符串操作 >>===============================================//

	template <typename ...Args>
	bool str_format(std::string& dst_str, const char* fmt, Args... args) {
		int len = snprintf(nullptr, 0, fmt, args...);
		if (len < 0) { return false; }
		if (len == 0) { dst_str.clear(); return true; }

		dst_str.resize(len);
		snprintf(&dst_str[0], len + 1, fmt, args...);

		return true;
	}

	template <typename ...Args>
	std::string str_format(const char* fmt, Args... args) {
		std::string result_str;
		str_format(result_str, fmt, args...);
		
		return result_str;
	}

	//==============================================<< 时间操作 >>===============================================//

	std::string& time_to_str_intput(const time_t& src_t_time, std::string& dst_str_time, const std::string& fmt = "yyyy-mm-dd hh24:mi:ss");
	std::string time_to_str_output(const time_t& src_t_time, const std::string& fmt = "yyyy-mm-dd hh24:mi:ss");

	std::string& curr_time_input(std::string& dst_str_time, const std::string& fmt = "yyyy-mm-dd hh24:mi:ss");
	std::string curr_time_output(const std::string& fmt = "yyyy-mm-dd hh24:mi:ss");

	//==============================================<< 目录操作 >>===============================================//
	bool create_dir(const std::string& dirfilename, const bool b_file = true);

} // namespace lxybx


#endif // PUBLIC_HPP