#include "dstring.hpp"


template<typename RT, typename... Ts>
void for_each_char(RT (*func)(char&, Ts...), dstring& str, size_t offset, size_t length, Ts&&... args)
{
	unsigned loop_limit = offset + length;
	for (unsigned i = offset; i < loop_limit; i++)
	{
		func(str[i], std::forward<Ts>(args)...);
	}
}

bool between(double val, double min, double max)
{
	return val >= min && val <= max;
}

dstring::dstring() : m_string{ nullptr }, m_length{ 0 }, m_max_capacity{ 0 } {}


dstring::dstring(const char* str) : m_string{ nullptr }
{
	resize(str);
}

dstring::dstring(const char* str, unsigned size) // unsafe
{
	m_string = new char[size];
	m_length = size;
	m_max_capacity = m_length;
	for (unsigned i = 0; i < size; i++)
		m_string[i] = str[i];
}

dstring::dstring(unsigned size)
{
	resize(size);
}

dstring::dstring(const dstring& dstr)
{
	resize(dstr.get(), dstr.size());
}

dstring::dstring(dstring&& dstr) noexcept : m_string{ nullptr }, m_length{ 0 }
{
	this->m_string = dstr.m_string;
	this->m_length = dstr.m_length;
	this->m_max_capacity = dstr.m_max_capacity;
	dstr.m_string = nullptr;
	dstr.m_length = 0;
	dstr.m_max_capacity = 0;
}

bool dstring::is_lower_case(const char& c)
{
	return between(c, LOWER_CASE_ALPHABET_START_OFFSET_ASCII, LOWER_CASE_ALPHABET_END_OFFSET_ASCII);
}

char& dstring::to_lower_case(char& c)
{
	if (is_upper_case(c))
		c += LOWER_CASE_UPPER_CASE_OFFSET;
	return c;
}

char& dstring::to_upper_case(char& c)
{
	if (is_lower_case(c))
		c -= LOWER_CASE_UPPER_CASE_OFFSET;
	return c;
}

char& dstring::swap_case(char& c)
{
	if (is_upper_case(c)) to_lower_case(c);
	else if (is_lower_case(c)) to_upper_case(c);
	return c;
}

void dstring::print_data() const
{
	std::cout << "content : " << this;
	std::cout << "\n";
	std::cout << "length : " << m_length << "\n";
	std::cout << "byte_size : " << sizeof(m_string) * m_length << "\n";
	std::cout << "bit_size : " << sizeof(m_string) * m_length * 8 << "\n";
}

char& dstring::at(unsigned i) const
{
	if (i < m_length)
		return m_string[i];
	return m_string[m_length - 1];
}

dstring dstring::operator+(const dstring& dstr)
{
	unsigned concat_size = dstr.size() + m_length;
	char* string_concat = new char[concat_size];
	for (unsigned i = 0; i < m_length; i++)
	{
		string_concat[i] = m_string[i];
	}
	for (unsigned i = 0; i < dstr.size(); i++)
	{
		string_concat[m_length + i] = dstr.get()[i];
	}
	return dstring(string_concat, concat_size);
}

dstring& dstring::operator=(const char* str)
{
	resize(str);
	return *this;
}

dstring& dstring::operator=(const dstring& dstr)
{
	resize(dstr.get(), dstr.size());
	return *this;
}

dstring& dstring::operator=(dstring&& dstr) noexcept
{
	if (this != &dstr)
	{
		this->~dstring();
		this->m_length = dstr.m_length;
		this->m_max_capacity = dstr.m_max_capacity;
		this->m_string = dstr.m_string;
		dstr.m_string = nullptr;
		dstr.m_length = 0;
		dstr.m_max_capacity = 0;
	}
	return *this;
}

char& dstring::operator[](unsigned i) 
{ 
	return m_string[i];
}

char* dstring::get() const
{ 
	return this->m_string;
}

const size_t& dstring::size() const
{
	return this->m_length;
}

size_t dstring::max_capacity() const
{
	return m_max_capacity;
}

dstring::~dstring()
{
	if (m_string != nullptr)
	{
		delete[] m_string;
	}
}

bool dstring::is_lower_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = offset; i < loop_limit; i++)
	{
		if (is_upper_case(this->at(i)) && !is_lower_case(this->at(i)))
		{
			return false;
		}
	}
	return true;
}

bool dstring::is_alphabet() const
{
	return is_alphabet(0, size());
}

bool dstring::is_alphabet(int offset) const
{
	return is_alphabet(offset, size());
}

bool dstring::is_alphabet(size_t offset, size_t length, unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = offset; i < loop_limit; i++)
	{
		if (!is_alphabet(this->at(i)))
		{
			return false;
		}
	}
	return true;
}

bool dstring::is_digit() const
{
	return is_digit(0, size());
}

bool dstring::is_digit(int offset) const
{
	return is_digit(offset, size());
}

bool dstring::is_digit(size_t offset, size_t length, unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = offset; i < loop_limit; i++)
	{
		if (!is_digit(this->at(i)))
		{
			return false;
		}
	}
	return true;
}

bool dstring::is_alpha_numeric() const
{
	return is_alpha_numeric(0, size());
}

bool dstring::is_alpha_numeric(int offset) const
{
	return is_alpha_numeric(offset, size());
}

bool dstring::is_alpha_numeric(size_t offset, size_t length, unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = offset; i < loop_limit; i++)
	{
		if (!is_alpha_numeric(this->at(i)))
		{
			return false;
		}
	}
	return true;
}

bool dstring::is_lower_case(int offset) const
{
	return is_lower_case(offset, size());
}

bool dstring::is_lower_case() const
{
	return is_lower_case(0, size());
}

bool dstring::is_upper_case(const char& c)
{
	return between(c, UPPER_CASE_ALPHABET_START_OFFSET_ASCII, UPPER_CASE_ALPHABET_END_OFFSET_ASCII);
}

bool dstring::is_upper_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = offset; i < loop_limit; i++)
	{
		if (is_lower_case(this->at(i)) && !is_upper_case(this->at(i)))
		{
			return false;
		}
	}
	return true;
}

bool dstring::is_empty() const
{
	return size() == 0;
}

bool dstring::is_upper_case() const
{
	return is_upper_case(0, size());
}

bool dstring::is_upper_case(int offset) const
{
	return is_upper_case(offset, size());
}

dstring& dstring::capitalize()
{
	if (is_lower_case(this->at(0)))
		this->at(0) -= LOWER_CASE_UPPER_CASE_OFFSET;
	return *this;
}

dstring& dstring::lowerize()
{
	if (is_upper_case(this->at(0)))
		this->at(0) -= LOWER_CASE_UPPER_CASE_OFFSET;
	return *this;
}

dstring& dstring::to_upper_case()
{
	for_each_char(to_upper_case, *this, 0, size());
	return *this;
}

dstring& dstring::to_upper_case(int offset)
{
	for_each_char(to_upper_case, *this, offset, size());
	return *this;
}

dstring& dstring::to_upper_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned))
{
	for_each_char(to_upper_case, *this, offset, length);
	return *this;
}

dstring& dstring::to_lower_case()
{
	for_each_char(to_lower_case, *this, 0, size());
	return *this;
}

dstring& dstring::to_lower_case(int offset)
{
	for_each_char(to_lower_case, *this, offset, size());
	return *this;
}

dstring& dstring::to_lower_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned))
{
	for_each_char(to_lower_case, *this, offset, iteration_mode(offset, length));
	return *this;
}

dstring& dstring::swap_case(size_t offset, size_t length, unsigned (*iteration_mode)(unsigned, unsigned))
{
	for_each_char(swap_case, *this, offset, iteration_mode(offset, length));
	return *this;
}

dstring& dstring::swap_case(int offset)
{
	for_each_char(swap_case, *this, offset, size());
	return *this;
}

dstring& dstring::swap_case()
{
	for_each_char(swap_case, *this, 0, size());
	return *this;
}

bool dstring::starts_with(char to_compare, bool(*comparator)(char, char)) const
{
	return comparator(this->at(0), to_compare);
}

bool dstring::starts_with(const dstring& to_compare, bool(*comparator)(char, char)) const
{
	for (unsigned i = 0; i < to_compare.size(); i++)
	{
		if (!comparator(this->at(i), const_cast<dstring&>(to_compare).at(i)))
		{
			return false;
		}
	}
	return true;
}

std::vector<dstring> dstring::split(char separator)
{
	std::vector<dstring> splitted = std::vector<dstring>();


	return std::vector<dstring>();
}

int dstring::find(char to_search, size_t offset, size_t length, unsigned n, bool(*comparator)(char, char), unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	if (n >= 1)
	{
		unsigned current_occurence_count = 0;
		unsigned loop_limit = iteration_mode(offset, length);
		for (unsigned i = offset; i < loop_limit; i++)
		{
			if (comparator(this->at(i), to_search))
			{
				current_occurence_count++;
			}
			if (current_occurence_count == n)
			{
				return i;
			}
		}
	}
	return -1;
}

int dstring::find(char to_search, size_t offset, unsigned n, bool(*comparator)(char, char)) const
{
	return find(to_search, offset, size() - 1, n, comparator, iteration_mode::bound_bound_mode);
}

int dstring::find(char to_search, unsigned n, bool(*comparator)(char, char)) const
{
	return find(to_search, 0, size(), n, comparator, iteration_mode::offset_length_mode);
}

int dstring::find(const dstring& to_search, size_t offset, size_t length, unsigned n, bool(*comparator)(char, char), unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	if (n >= 1)
	{
		unsigned current_occurence_count = 0;
		bool found_token;
		unsigned loop_limit = iteration_mode(offset, length);
		for (unsigned i = offset; i < loop_limit; i++)
		{
			found_token = true;
			for (unsigned j = 0; j < to_search.size(); j++)
			{
				if (!comparator(this->at(i + j), const_cast<dstring&>(to_search).at(j)))
				{
					found_token = false;
					break;
				}
			}
			if (found_token)
			{
				current_occurence_count++;
			}

			if (current_occurence_count == n)
			{
				return i;
			}
		}
	}
	return -1;
}

int dstring::find(const dstring& to_search, size_t offset, unsigned n, bool(*comparator)(char, char)) const
{
	return find(to_search, offset, size() - 1, n, comparator, iteration_mode::bound_bound_mode);
}

int dstring::find(const dstring& to_search, unsigned n, bool(*comparator)(char, char)) const
{
	return find(to_search, 0, size(), n, comparator, iteration_mode::offset_length_mode);
}

int dstring::ffind(char to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	return find(to_search, offset, length, 1, comparator, iteration_mode);
}

int dstring::ffind(char to_search, bool(*comparator)(char, char)) const
{
	return find(to_search, 0, size(), 1, comparator, iteration_mode::offset_length_mode);
}

int dstring::ffind(char to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return find(to_search, offset, size() - 1, 1, comparator, iteration_mode::bound_bound_mode);
}

int dstring::ffind(const dstring& to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	return find(to_search, offset, length, 1, comparator, iteration_mode);
}

int dstring::ffind(const dstring& to_search, bool(*comparator)(char, char)) const
{
	return find(to_search, 0, size(), 1, comparator, iteration_mode::offset_length_mode);
}

int dstring::ffind(const dstring& to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return find(to_search, offset, size() - 1, 1, comparator, iteration_mode::bound_bound_mode);
}

int dstring::lfind(char to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	unsigned last_occurence_index = -1;
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = offset; i < loop_limit; i++)
	{
		if (comparator(this->at(i), to_search))
		{
			last_occurence_index = i;
		}
	}
	return last_occurence_index;
}

int dstring::lfind(char to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return lfind(to_search, offset, size() - 1, comparator, iteration_mode::bound_bound_mode);
}

int dstring::lfind(char to_search, bool(*comparator)(char, char)) const
{
	return lfind(to_search, 0, size(), comparator, iteration_mode::offset_length_mode);
}

int dstring::lfind(const dstring& to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned (*iteration_mode)(unsigned, unsigned)) const
{
	unsigned last_occurence_index = -1;
	unsigned loop_limit = iteration_mode(offset, length);
	bool found_token;
	for (unsigned i = offset; i < loop_limit; i++)
	{
		found_token = true;
		for (unsigned j = 0; j < to_search.size(); j++)
		{
			if (!comparator(this->at(i + j), const_cast<dstring&>(to_search).at(j)))
			{
				found_token = false;
				break;
			}
		}
		if (found_token)
		{
			last_occurence_index = i;
		}
	}
	return last_occurence_index;
}

int dstring::lfind(const dstring& to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return lfind(to_search, offset, size() - 1, comparator, iteration_mode::bound_bound_mode);
}

int dstring::lfind(const dstring& to_search, bool(*comparator)(char, char)) const
{
	return lfind(to_search, 0, size(), comparator, iteration_mode::offset_length_mode);
}

std::vector<int> dstring::indices_of(char to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	std::vector<int> indices;
	for (unsigned i = offset;i < loop_limit;i++)
	{
		if (comparator(this->at(i), to_search))
		{
			indices.push_back(i);
		}
	}
	return indices;
}

std::vector<int> dstring::indices_of(char to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return indices_of(to_search, offset, size() - 1, comparator, iteration_mode::bound_bound_mode);
}

std::vector<int> dstring::indices_of(char to_search, bool(*comparator)(char, char)) const
{
	return indices_of(to_search, 0, size(), comparator, iteration_mode::offset_length_mode);
}

std::vector<int> dstring::indices_of(const dstring& to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	unsigned loop_limit = iteration_mode(offset, length);
	std::vector<int> indices;
	bool is_valid;
	for (unsigned i = offset; i < loop_limit; i++)
	{
		bool is_valid = true;
		for (unsigned j = offset;j < to_search.size();j++)
		{
			if (!comparator(this->at(i + j), const_cast<dstring&>(to_search).at(j)))
			{
				is_valid = false;
				break;
			}
		}
		if (is_valid)
		{
			indices.push_back(i);
		}
	}
	return indices;
}

std::vector<int> dstring::indices_of(const dstring& to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return indices_of(to_search, offset, size() - 1, comparator, iteration_mode::bound_bound_mode);
}

std::vector<int> dstring::indices_of(const dstring& to_search, bool(*comparator)(char, char)) const
{
	return indices_of(to_search, 0, size(), comparator, iteration_mode::offset_length_mode);
}


bool dstring::contains(char to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	return find(to_search, offset, length, 1, comparator, iteration_mode) != -1;
}

bool dstring::contains(char to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return find(to_search, offset, size() - 1, 1, comparator, iteration_mode::bound_bound_mode) != -1;
}

bool dstring::contains(char to_search, bool(*comparator)(char, char)) const
{
	return find(to_search, 0, size(), 1, comparator, iteration_mode::offset_length_mode) != -1;
}

bool dstring::contains(const dstring& to_search, size_t offset, size_t length, bool(*comparator)(char, char), unsigned(*iteration_mode)(unsigned, unsigned)) const
{
	return find(to_search, offset, length, 1, comparator, iteration_mode) != -1;
}

bool dstring::contains(const dstring& to_search, size_t offset, bool(*comparator)(char, char)) const
{
	return find(to_search, offset, size() - 1, 1, comparator, iteration_mode::bound_bound_mode) != -1;
}

bool dstring::contains(const dstring& to_search, bool(*comparator)(char, char)) const
{
	return find(to_search, 0, size(), 1, comparator, iteration_mode::offset_length_mode) != -1;
}

bool dstring::equals_case_sensitive(char c1, char c2)
{
	return c1 == c2;
}

bool dstring::equals_case_insensitive(char c1, char c2)
{
	return to_upper_case(c1) == to_upper_case(c2) || to_lower_case(c1) == to_lower_case(c2);
}

bool dstring::is_alphabet(const char& c)
{
	return is_lower_case(c) || is_upper_case(c);
}

bool dstring::is_digit(const char& c)
{
	return between(c, NUMBER_START_OFFSET_ASCII, NUMBER_END_OFFSET_ASCII);
}

bool dstring::is_alpha_numeric(const char& c)
{
	return is_alphabet(c) || is_digit(c);
}

std::ostream& operator<<(std::ostream& os, const dstring& dstr)
{
	for (unsigned i = 0; i < dstr.m_length; i++)
		os << dstr.m_string[i];
	return os;
}

std::istream& operator>>(std::istream& is, dstring& dstr)
{
	return is;
}

dstring& dstring::replace(char to_replace, char replace_by, bool(*comparator)(char, char))
{
	return replace(to_replace, replace_by, 0, size(), comparator, iteration_mode::offset_length_mode);
}

dstring& dstring::replace(char to_replace, char replace_by, size_t offset, bool(*comparator)(char, char))
{
	return replace(to_replace, replace_by, offset, size() - 1, comparator, iteration_mode::bound_bound_mode);
}

dstring& dstring::replace(char to_replace, char replace_by, size_t offset, size_t length, bool(*comparator)(char, char), unsigned(*iteration_mode)(unsigned, unsigned))
{
	unsigned loop_limit = iteration_mode(offset, length);
	for (unsigned i = 0;i < loop_limit;i++)
	{
		if (comparator(this->at(i), to_replace))
		{
			this->at(i) = replace_by;
		}
	}
	return *this;
}

dstring& dstring::replace(const dstring& to_replace, const dstring& replace_by, bool(*comparator)(char, char))
{
	return replace(to_replace, replace_by, 0, size(), comparator, iteration_mode::offset_length_mode);
}

dstring& dstring::replace(const dstring& to_replace, const dstring& replace_by, size_t offset, bool(*comparator)(char, char))
{
	return replace(to_replace, replace_by, offset, size() - 1, comparator, iteration_mode::bound_bound_mode);
}

dstring& dstring::replace(const dstring& to_replace, const dstring& replace_by, size_t offset, size_t length, bool(*comparator)(char, char), unsigned(*iteration_mode)(unsigned, unsigned))
{
	std::vector<int> indices = indices_of(to_replace, offset, length, comparator, iteration_mode);
	if (indices.size() != 0)
	{
		if (to_replace.size() == replace_by.size())
		{
			for (unsigned i = 0;i < indices.size();i++)
			{
				for (unsigned j = 0; j < replace_by.size(); j++)
				{
					this->at(indices[i] + j) = replace_by.at(j);
				}
			}
		}
		else
		{
			size_t diff_size = replace_by.size() - to_replace.size();
			size_t new_size = size() + indices.size() * diff_size;
			dstring new_string = dstring(new_size);
			size_t offset;
			unsigned next_match_offset;
			unsigned after_match_offset;
			for (unsigned i = 0; i < indices[0]; i++)
			{
				char cp_char = this->at(i);
				new_string.m_string[i] = cp_char;
			}
			for (unsigned j = 0; j < indices.size(); j++)
			{
				unsigned target_pos = j * diff_size + indices[j];
				for (unsigned i = 0; i < replace_by.size(); i++)
				{
					char cp_char = replace_by.at(i);
					new_string.m_string[target_pos + i] = cp_char;
				}
				offset = target_pos + replace_by.size();
				if (j < indices.size() - 1) next_match_offset = indices[j + 1];
				else next_match_offset = size();
				after_match_offset = indices[j] + to_replace.size();
				for (unsigned i = after_match_offset; i < next_match_offset; i++)
				{
					char cp_char = this->at(i);
					new_string.m_string[offset + (i - after_match_offset)] = cp_char;
				}
			}
			new_string.m_length = new_size;
			*this = std::move(new_string);
		}
	}
	return *this;
}

//dstring& dstring::insert(const char* to_insert, unsigned pos)
//{
//	return insert(dstring(to_insert), pos);
//}

dstring& dstring::insert(const dstring& to_insert, unsigned pos)
{
	unsigned total_size = size() + to_insert.size();
	unsigned target_pos = pos + 1;
	dstring new_string = dstring(total_size);
	for (unsigned i = 0;i < target_pos;i++)
	{
		char cp_char = this->at(i);
		new_string.m_string[i] = cp_char;
	}
	for (unsigned i = 0;i < to_insert.size();i++)
	{
		char cp_char = to_insert.at(i);
		new_string.m_string[target_pos + i] = cp_char;
	}
	unsigned offset = target_pos + to_insert.size();
	unsigned loop_limit = size() - target_pos;
	for (unsigned i = 0;i < loop_limit;i++)
	{
		char cp_char = this->at(target_pos + i);
		new_string.m_string[offset + i] = cp_char;
	}
	new_string.m_length = total_size;
	*this = std::move(new_string);
	return *this;
}
