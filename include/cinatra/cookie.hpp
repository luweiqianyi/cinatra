#pragma once
#include <string>
#include "utils.hpp"

namespace cinatra {
	// 根据版本号提供Netscape格式和RFC 2109格式的Cookie的字符串格式
	// 主要函数为to_string()
	// 主要参数为name 和 value
	// 其他参数可以添加或者不添加
	class cookie {
	public:
		// C++ 11 使用“=default”可以在有其他自定义的构造函数的前提下告诉编译器生成一个默认构造函数
		cookie() = default;
		cookie(const std::string& name, const std::string& value) : name_(name), value_(value) {

		}

		void set_version(int version) {
			version_ = version;
		}

		void set_name(const std::string& name) {
			name_ = name;
		}

		std::string get_name() const {
			return name_;
		}

		void set_value(const std::string& value) {
			value_ = value;
		}

		std::string get_value() const {
			return value_;
		}

		void set_comment(const std::string& comment) {
			comment_ = comment;
		}

		void set_domain(const std::string& domain) {
			domain_ = domain;
		}

		void set_path(const std::string& path) {
			path_ = path;
		}

		void set_priority(const std::string& priority) {
			priority_ = priority;
		}

		void set_secure(bool secure) {
			secure_ = secure;
		}

		void set_max_age(std::time_t seconds) {
			max_age_ = seconds;
		}

		void set_http_only(bool http_only) {
			http_only_ = http_only;
		}

		// 根据版本号提供Netscape格式和RFC 2109格式的Cookie的字符串转换函数
		std::string to_string() const {
			std::string result;
			result.reserve(256); //确定新分配的最小长度为256
			result.append(name_);
			result.append("=");
			if (version_ == 0)
			{
				// Netscape cookie
				result.append(value_);
				if (!path_.empty())
				{
					result.append("; path=");
					result.append(path_);
				}
				if (!priority_.empty())
				{
					result.append("; Priority=");
					result.append(priority_);
				}
				if (max_age_ != -1)
				{
					result.append("; expires=");
					result.append(get_gmt_time_str(max_age_));
				}
				if (secure_)
				{
					result.append("; secure");
				}
				if (http_only_)
				{
					result.append("; HttpOnly");
				}
			}
			else
			{
				// RFC 2109 cookie
				result.append("\"");
				result.append(value_);
				result.append("\"");
				if (!comment_.empty())
				{
					result.append("; Comment=\"");
					result.append(comment_);
					result.append("\"");
				}
				if (!path_.empty())
				{
					result.append("; Path=\"");
					result.append(path_);
					result.append("\"");
				}
				if (!priority_.empty())
				{
					result.append("; Priority=\"");
					result.append(priority_);
					result.append("\"");
				}

				if (max_age_ != -1)
				{
					result.append("; Max-Age=\"");
					result.append(std::to_string(max_age_));
					result.append("\"");
				}
				if (secure_)
				{
					result.append("; secure");
				}
				if (http_only_)
				{
					result.append("; HttpOnly");
				}
				result.append("; Version=\"1\"");
			}
			return result;
		}

	private:
		int          version_ = 0;
		std::string  name_ = "";
		std::string  value_ = "";
		std::string  comment_ = "";
		std::string  domain_ = "";
		std::string  path_ = "";
		std::string  priority_ = "";
		bool         secure_ = false;
		/*

		typedef long                          __time32_t;
		typedef __int64                       __time64_t;

		#ifndef _CRT_NO_TIME_T
			#ifdef _USE_32BIT_TIME_T
				typedef __time32_t time_t;
			#else
				typedef __time64_t time_t;
			#endif
		#endif
		*/
		std::time_t  max_age_ = -1;
		bool         http_only_ = false;
	};
}
