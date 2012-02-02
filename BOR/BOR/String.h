#ifndef STRING_H
#define STRING_H
#include <iostream>

namespace hmw{
class string{
	private:
		class ProxyChar{
			private:
				size_t pos;
				string *s;
			public:
				ProxyChar(string *_str, size_t _pos);
				void operator= (const char c);
				operator char();
		};
		
		class S_Buf{
			public:
			friend class string;
			size_t countRef;
			char *str;
			S_Buf();
			S_Buf(const char* _str, const size_t _size, const size_t _count_repeat);
			S_Buf(S_Buf& _buf);
			~S_Buf();

			void destroy();
		};
			
		S_Buf *buf;
		size_t s_size;
		static string concat(const char* _str1, const char* _str2);
	public:
		class out_of_range{};

		string();
		string(const char c, size_t _count);
		string(const char* _str);
		string(const char* _str, size_t _count);
		string(string &_str);
		~string();

		size_t size();
		void clear();
		bool empty();
		char* c_str();

		ProxyChar operator[] (size_t _pos);

		void operator= (const string &_str);
		void operator= (const char* _str);
		void operator= (const char c);
		friend string operator+ (const string&, const string&);
		friend string operator+	(const char*, const string&);
		friend string operator+	(const string&, const char*);
		
		friend bool operator== (const string&, const string&);
		friend bool operator== (const char*, const string&);
		friend bool operator== (const string&, const char*);
		friend bool operator<= (const string&, const string&);
		friend bool operator<= (const char*, const string&);
		friend bool operator<= (const string&, const char*);
		friend bool operator>= (const string&, const string&);
		friend bool operator>= (const char*, const string&);
		friend bool operator>= (const string&, const char*);
		friend bool operator!= (const string&, const string&);
		friend bool operator!= (const char*, const string&);
		friend bool operator!= (const string&, const char*);
		friend bool operator> (const string&, const string&);
		friend bool operator> (const char*, const string&);
		friend bool operator> (const string&, const char*);
		friend bool operator< (const string&, const string&);
		friend bool operator< (const char*, const string&);
		friend bool operator< (const string&, const char*);
};
};
#endif
