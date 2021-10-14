#include <iostream>
#include <vector>
#include <array>

namespace iteration_mode
{
	inline unsigned offset_length_mode(unsigned offset, unsigned length)
	{
		return offset + length;
	}

	inline unsigned bound_bound_mode(unsigned, unsigned bound)
	{
		return bound + 1;
	}
}

constexpr char NUMBER_START_OFFSET_ASCII = 48;
constexpr char NUMBER_END_OFFSET_ASCII = 57;
constexpr char UPPER_CASE_ALPHABET_START_OFFSET_ASCII = 65;
constexpr char UPPER_CASE_ALPHABET_END_OFFSET_ASCII = 90;
constexpr char LOWER_CASE_ALPHABET_START_OFFSET_ASCII = 97;
constexpr char LOWER_CASE_ALPHABET_END_OFFSET_ASCII = 122;
constexpr char LOWER_CASE_UPPER_CASE_OFFSET = LOWER_CASE_ALPHABET_START_OFFSET_ASCII - UPPER_CASE_ALPHABET_START_OFFSET_ASCII;

class dstring
{
	char* m_string;
	unsigned m_length;
	unsigned m_max_capacity;

	void resize(const char* str)
	{
		this->~dstring();
		unsigned index = 0;
		while (str[index] != '\0')
			index++;
		m_length = index;
		m_max_capacity = m_length;
		m_string = new char[m_length];
		for (unsigned i = 0; i < m_length; i++)
			m_string[i] = str[i];
	}


	void resize(char* str, unsigned size)
	{
		this->~dstring();
		m_string = new char[size];
		unsigned index = 0;
		while (str[index] != '\0')
			index++;
		m_length = index;
		m_max_capacity = size;
		for (unsigned i = 0; i < m_length; i++)
			m_string[i] = str[i];
	}

	void resize(unsigned size)
	{
		this->~dstring();
		m_string = new char[size];
		m_length = 0;
		m_max_capacity = size;
	}

public:
	dstring();
	dstring(const char* str);
	dstring(const char* str, unsigned size);
	dstring(unsigned size);
	dstring(const dstring& dstr);
	dstring(dstring&& dstr) noexcept;

	bool is_lower_case() const;
	bool is_lower_case(int offset) const;
	bool is_lower_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_alphabet() const;
	bool is_alphabet(int offset) const;
	bool is_alphabet(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_digit() const;
	bool is_digit(int offset) const;
	bool is_digit(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_alpha_numeric() const;
	bool is_alpha_numeric(int offset) const;
	bool is_alpha_numeric(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_upper_case() const;
	bool is_upper_case(int offset) const;
	bool is_upper_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_empty() const;
	bool is_empty(int offset) const;
	bool is_empty(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_space() const;
	bool is_space(int offset) const;
	bool is_space(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool is_same() const;
	bool is_same(int offset) const;
	bool is_same(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;

	dstring& capitalize();
	dstring& capitalize_first_letter();
	dstring& capitalize_word();
	dstring& lowerize();
	dstring& lowerize_first_letter();
	dstring& lowerize_word();
	dstring& to_upper_case();
	dstring& to_upper_case(int offset);
	dstring& to_upper_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);
	dstring& to_lower_case();
	dstring& to_lower_case(int offset);
	dstring& to_lower_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);
	dstring& swap_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);
	dstring& swap_case(int offset);
	dstring& swap_case();
	dstring& randomize_case();
	dstring& randomize_case(int offset);
	dstring& randomize_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);
	dstring& change_case();
	dstring& change_case(int offset);
	dstring& change_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);

	bool starts_with(char to_compare,			bool (*comparator)(char, char) = dstring::default_comparator) const;
	bool starts_with(const dstring& to_compare, bool (*comparator)(char, char) = dstring::default_comparator) const;

	bool ends_with(char to_compare,			  bool (*comparator)(char, char) = dstring::default_comparator) const;
	bool ends_with(const dstring& to_compare, bool (*comparator)(char, char) = dstring::default_comparator) const;

	std::vector<dstring> split(char separator);
	std::vector<dstring> split(char separator, size_t max_size);
	std::vector<dstring> split(const dstring& separator);
	std::vector<dstring> split(const dstring& separator, size_t max_split);

	std::array<dstring, 3> partition(const dstring& value);
	std::array<dstring, 3> rpartition(const dstring& value);

	//dstring& insert(const char* to_insert, unsigned pos);
	dstring& insert(const dstring& to_insert, unsigned pos);
	dstring& fill_with(char filler, size_t pos, size_t count);
	dstring& fill_with(dstring& filler, size_t pos, size_t count);
	dstring& remove(char to_remove, size_t max_remove);
	void destroy(); // Call de destructor

	dstring& replace(char to_replace, char replace_by,								 bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(char to_replace, char replace_by, size_t offset,				 bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(char to_replace, char replace_by, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);
	
	dstring& replace(const dstring& to_replace, char replace_by,							   bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(const dstring& to_replace, char replace_by, size_t offset,				   bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(const dstring& to_replace, char replace_by, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);

	dstring& replace(char to_replace, const dstring& replace_by,							   bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(char to_replace, const dstring& replace_by, size_t offset,				   bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(char to_replace, const dstring& replace_by, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);

	dstring& replace(const dstring& to_replace, const dstring& replace_by,								 bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(const dstring& to_replace, const dstring& replace_by, size_t offset,				 bool (*comparator)(char, char) = dstring::default_comparator);
	dstring& replace(const dstring& to_replace, const dstring& replace_by, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode);

	// NTH FIND
	int find(char		    to_search, size_t offset, size_t length, unsigned n, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	int find(char		    to_search, size_t offset,				 unsigned n, bool (*comparator)(char, char) = dstring::default_comparator) const;
	int find(char		    to_search,								 unsigned n, bool (*comparator)(char, char) = dstring::default_comparator) const;
	int find(const dstring& to_search, size_t offset, size_t length, unsigned n, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	int find(const dstring& to_search, size_t offset,				 unsigned n, bool (*comparator)(char, char) = dstring::default_comparator) const;
	int find(const dstring& to_search,								 unsigned n, bool (*comparator)(char, char) = dstring::default_comparator) const;
	// FIRST FIND
	int ffind(char			 to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator,	unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	int ffind(char			 to_search,								  bool (*comparator)(char, char) = dstring::default_comparator) const;
	int ffind(char			 to_search,	size_t offset,				  bool (*comparator)(char, char) = dstring::default_comparator) const;
	int ffind(const dstring& to_search,	size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	int ffind(const dstring& to_search,								  bool (*comparator)(char, char) = dstring::default_comparator) const;
	int ffind(const dstring& to_search, size_t offset,				  bool (*comparator)(char, char) = dstring::default_comparator) const;
	// LAST FIND
	int lfind(char			 to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	int lfind(char			 to_search, size_t offset,				  bool (*comparator)(char, char) = dstring::default_comparator) const;
	int lfind(char			 to_search,								  bool (*comparator)(char, char) = dstring::default_comparator) const;
	int lfind(const dstring& to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	int lfind(const dstring& to_search, size_t offset,				  bool (*comparator)(char, char) = dstring::default_comparator) const;
	int lfind(const dstring& to_search,								  bool (*comparator)(char, char) = dstring::default_comparator) const;

	std::vector<int> indices_of(char		   to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	std::vector<int> indices_of(char		   to_search, size_t offset,				bool (*comparator)(char, char) = dstring::default_comparator) const;
	std::vector<int> indices_of(char		   to_search,							    bool (*comparator)(char, char) = dstring::default_comparator) const;
	std::vector<int> indices_of(const dstring& to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	std::vector<int> indices_of(const dstring& to_search, size_t offset,				bool (*comparator)(char, char) = dstring::default_comparator) const;
	std::vector<int> indices_of(const dstring& to_search,							    bool (*comparator)(char, char) = dstring::default_comparator) const;

	bool contains(char			 to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool contains(char			 to_search, size_t offset,				  bool (*comparator)(char, char) = dstring::default_comparator) const;
	bool contains(char			 to_search,								  bool (*comparator)(char, char) = dstring::default_comparator) const;
	bool contains(const dstring& to_search, size_t offset, size_t length, bool (*comparator)(char, char) = dstring::default_comparator, unsigned (*iteration_mode)(unsigned, unsigned) = dstring::default_iteration_mode) const;
	bool contains(const dstring& to_search, size_t offset,				  bool (*comparator)(char, char) = dstring::default_comparator) const;
	bool contains(const dstring& to_search,								  bool (*comparator)(char, char) = dstring::default_comparator) const;

	static bool equals_case_sensitive(char c1, char c2);
	static bool equals_case_insensitive(char c1, char c2);
	static bool is_alphabet(const char& c);
	static bool is_digit(const char& c);
	static bool is_decimal(const char& c);
	static bool is_alpha_numeric(const char& c);
	static bool is_upper_case(const char& c);
	static bool is_lower_case(const char& c);
	static char& to_lower_case(char& c);
	static char& to_upper_case(char& c);
	static char& swap_case(char& c);
	static char& randomize_case(char& c);

	constexpr static unsigned (*default_iteration_mode)( unsigned, unsigned) = iteration_mode::offset_length_mode;
	constexpr static bool (*default_comparator)(char, char) = dstring::equals_case_sensitive;

	void print_data() const;

	dstring& reverse()
	{
		char temp;
		for (unsigned i = 0; i < m_length / 2; i++)
		{
			temp = m_string[i];
			m_string[i] = m_string[m_length - i - 1];
			m_string[m_length - i - 1] = temp;
		}

		return *this;
	}

	bool contain(const char* str, unsigned size) const
	{
		bool output;
		unsigned loopLimit = m_length - size + 1;
		for (unsigned i = 0; i < loopLimit; i++)
		{
			output = true;
			for (unsigned j = 0; j < size; j++)
			{
				if (m_string[i + j] != str[j])
				{
					output = false;
					break;
				}
			}
			if (output)
				return true;
		}
		return false;
	}

	char& at(unsigned i) const;
	char* get() const;
	const size_t& size() const;
	size_t max_capacity() const;

	dstring operator+(const dstring& dstr);
	dstring& operator=(const char* str);
	dstring& operator=(const dstring& dstr);
	dstring& operator=(dstring&& dstr) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const dstring& dstr);
	friend std::istream& operator>>(std::istream& os, dstring& dstr);
	char& operator[](unsigned i);

	virtual ~dstring();
};