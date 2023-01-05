#include <iostream>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


struct style {
	enum type {
		reset		= 0,
		bold		= 1,
		dim			= 2,
		italic		= 3,
		underline	= 4,
		blink		= 5,
		rblink		= 6,
		reversed	= 7,
		conceal		= 8,
		crossed		= 9
	};
};

struct fg {
	enum type {
		black	= 30,
		red		= 31,
		green	= 32,
		yellow	= 33,
		blue	= 34,
		magenta	= 35,
		cyan	= 36,
		white	= 37,
		gray	= 90,
		reset	= 39
	};
};

struct bg {
	enum type {
		black	= 40,
		red		= 41,
		green	= 42,
		yellow	= 43,
		blue	= 44,
		magenta	= 45,
		cyan	= 46,
		white	= 47,
		gray	= 100,
		reset	= 49
	};
};

fg::type	old_fg = fg::reset;
bg::type	old_bg = bg::reset;

inline std::ostream & operator<<(std::ostream &os, style::type const value)
{
	if (value == style::reset)
	{
		old_fg = fg::reset;
		old_bg = bg::reset;
	}
	return os << "\033[" << static_cast<int>(value) << "m";
}

inline std::ostream & operator<<(std::ostream &os, fg::type const value)
{
	old_fg = value;
	return os << "\033[" << static_cast<int>(value) << "m";
}

inline std::ostream & operator<<(std::ostream &os, bg::type const value)
{
	old_bg = value;
	return os << "\033[" << static_cast<int>(value) << "m";
}


struct SetColor {
	std::string	output;

	template <typename T>
	SetColor( T const value, std::string const &str)
	{
		fg::type tmp_fg = old_fg;
		bg::type tmp_bg = old_bg;
		output = SSTR(value);
		output += str;
		output += SSTR(tmp_fg);
		output += SSTR(tmp_bg);
	}

	template <typename T, typename V>
	SetColor( T const value, V const &str)
	{
		fg::type tmp_fg = old_fg;
		bg::type tmp_bg = old_bg;
		output = SSTR(value);
		output += SSTR(str);
		output += SSTR(tmp_fg);
		output += SSTR(tmp_bg);
	}

	operator std::string() const { return output; }

};

std::ostream & operator<<(std::ostream &os, const SetColor & obj)
{
	return os << obj.output;
}