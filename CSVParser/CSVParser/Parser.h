#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include "BadFormat.h"
#include "BadLineFormat.h"
#include "BadLineQuotes.h"
#include "BadQuotes.h"
#include "ElementWithUnknownSequence.h"
#include "RecordWithUnknownSequence.h"
#include "UnknownRuleSequence.h"

constexpr char LINE_DELIMITER = '\n';
constexpr char ELEMENT_DELIMITER = ',';
constexpr char SCREEN_GUARD = '"';
const std::unordered_map<std::string, char> RULE_SEQUENCE_MEANING = {
		{"comma", ELEMENT_DELIMITER},
		{"endl", LINE_DELIMITER},
		{"quote", SCREEN_GUARD}
};


inline void RemoveRuleSequences(std::string& line)
{
	int last_changed_screen_guard_index = -1;
	while (line.find(SCREEN_GUARD, last_changed_screen_guard_index + 1) != std::string::npos)
	{
		size_t first_quote_occurrence = line.find(SCREEN_GUARD,
			last_changed_screen_guard_index + 1);
		size_t second_quote_occurrence = line.find(SCREEN_GUARD,
			first_quote_occurrence + 1);
		std::string word_inside_guards = line.substr(first_quote_occurrence + 1,
			second_quote_occurrence - first_quote_occurrence - 1);
		if (second_quote_occurrence == std::string::npos)
		{
			throw std::runtime_error("Wrong rule sequence usage");
		}
		try
		{
			line.replace(first_quote_occurrence,
				second_quote_occurrence - first_quote_occurrence + 1,
				std::string{ RULE_SEQUENCE_MEANING.at(word_inside_guards) });
			last_changed_screen_guard_index = first_quote_occurrence;
		}
		catch(std::out_of_range&)
		{
			throw ElementWithUnknownSequence(word_inside_guards);
		}
	}
}

inline size_t GetLinesAmount(const std::string& file_name)
{
	std::ifstream file_stream(file_name);
	std::string line;
	size_t line_counter = 0;
	while (std::getline(file_stream, line, LINE_DELIMITER))
	{
		line_counter++;
	}
	return line_counter;
}

template<typename T, typename ... Args>
auto& operator<<(std::basic_ostream<char>& output_stream, const std::tuple<T, Args...>& tuple)
{
	auto remove_first_element = [](auto first, auto... args)-> auto
	{
		return std::make_tuple(args...);
	};
	return output_stream << std::get<0>(tuple) << "," << std::apply(remove_first_element, tuple);
}

template<typename T>
auto& operator<<(std::basic_ostream<char>& output_stream, const std::tuple<T>& tuple)
{
	return output_stream << std::get<0>(tuple);
}

template<typename T, typename... Args>
auto& operator>>(std::basic_istream<char>& input_stream, std::tuple<T, Args...>& tuple)
{
	T first_element;
	std::string string_element;
	std::getline(input_stream, string_element, ELEMENT_DELIMITER);
	try
	{
		RemoveRuleSequences(string_element);
	}
	catch(ElementWithUnknownSequence& e)
	{
		throw RecordWithUnknownSequence(sizeof...(Args), e.GetWord());
	}
	catch(std::runtime_error&)
	{
		throw BadLineQuotes(sizeof...(Args));
	}
	std::stringstream char_stream(string_element);
	char_stream >> first_element;
	if(input_stream.fail() ||
		char_stream.fail() ||
		!char_stream.eof())
	{
		throw BadLineFormat(sizeof...(Args));
	}
	std::tuple<Args...> tail;
	input_stream >> tail;
	tuple = std::tuple_cat(std::make_tuple(first_element), tail);
	return input_stream;
}

template<typename T>
auto& operator>>(std::basic_istream<char>& input_stream, std::tuple<T>& tuple)
{
	T element;
	std::string string_element;
	std::getline(input_stream, string_element, LINE_DELIMITER);
	if(string_element.find(ELEMENT_DELIMITER) != std::string::npos)
	{
		throw BadLineFormat(0);
	}
	try
	{
		RemoveRuleSequences(string_element);
	}
	catch (ElementWithUnknownSequence& e)
	{
		throw RecordWithUnknownSequence(0, e.GetWord());
	}
	catch (std::runtime_error&)
	{
		throw BadLineQuotes(0);
	}
	std::stringstream char_stream(string_element);
	char_stream >> element;
	if(input_stream.fail() ||
		char_stream.fail() ||
		!char_stream.eof())
	{
		throw BadLineFormat(0);
	}
	tuple = std::make_tuple(element);
	return input_stream;
}

template <typename... Args>
class Parser
{
public:
	class ParserIterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = std::tuple<Args...>;

		explicit ParserIterator(const std::string& file_name, size_t line_number);
		bool operator==(const ParserIterator& other)const;
		bool operator!=(const ParserIterator& other)const;
		ParserIterator& operator++();
		void ReadRecord();
		std::tuple<Args...>& operator*();
		std::tuple<Args...>* operator->();
	private:
		std::tuple<Args...> current_record_;
		std::ifstream file_stream_;
		std::string file_name_;
		size_t current_line_number_;
		bool read_record_;
	};
	explicit Parser(std::string file_name, size_t skip_rows = 0);
	void CheckFile() const;
	ParserIterator begin();
	ParserIterator end();
private:
	std::string csv_file_name_;
	size_t skip_records_;
	
};

template <typename ... Args>
Parser<Args...>::ParserIterator::ParserIterator(const std::string& file_name, const size_t line_number) :
	file_stream_(file_name),
	file_name_(file_name),
	current_line_number_(line_number),
	read_record_(false)
{
	for(int i = 0; i < current_line_number_ - 1; ++i)
	{
		std::string line;
		std::getline(file_stream_, line, LINE_DELIMITER);
	}
}

template <typename ... Args>
bool Parser<Args...>::ParserIterator::operator==(const ParserIterator& other) const
{
	return file_name_ == other.file_name_ && current_line_number_ == other.current_line_number_;
}

template <typename ... Args>
bool Parser<Args...>::ParserIterator::operator!=(const ParserIterator& other) const
{
	return !(*this == other);
}

template <typename ... Args>
typename Parser<Args...>::ParserIterator& Parser<Args...>::ParserIterator::operator++()
{
	ReadRecord();
	current_line_number_++;
	read_record_ = false;
	return *this;
}

template <typename ... Args>
void Parser<Args...>::ParserIterator::ReadRecord()
{
	if(!read_record_)
	{
		std::string string_record;
		std::getline(file_stream_, string_record, LINE_DELIMITER);
		std::stringstream string_stream(string_record);
		try
		{
			string_stream >> current_record_;
		}
		catch (BadLineFormat& e)
		{
			throw BadFormat(current_line_number_, sizeof...(Args) - e.GetElemFromEnd());
		}
		catch(BadLineQuotes& e)
		{
			throw BadQuotes(current_line_number_, sizeof...(Args) - e.GetElemFromEnd());
		}
		catch(RecordWithUnknownSequence& e)
		{
			throw UnknownRuleSequence(current_line_number_, sizeof...(Args) - e.GetElemFromEnd(), e.GetWord());
		}
		read_record_ = true;
	}
}

template <typename ... Args>
std::tuple<Args...>& Parser<Args...>::ParserIterator::operator*()
{
	ReadRecord();
	return current_record_;
}

template <typename ... Args>
std::tuple<Args...>* Parser<Args...>::ParserIterator::operator->()
{
	ReadRecord();
	return &current_record_;
}

template <typename ... Args>
Parser<Args...>::Parser(std::string file_name, const size_t skip_rows) :
	csv_file_name_(std::move(file_name)),
	skip_records_(skip_rows)
{}

template <typename ... Args>
void Parser<Args...>::CheckFile() const
{
	Parser test_parser(csv_file_name_, skip_records_);
	std::tuple<Args...> buffer;
	for (auto& record : test_parser)
	{
		buffer = record;
	}
}

template <typename ... Args>
typename Parser<Args...>::ParserIterator Parser<Args...>::begin()
{
	return ParserIterator(csv_file_name_, skip_records_ + 1);
}

template <typename ... Args>
typename Parser<Args...>::ParserIterator Parser<Args...>::end()
{
	return ParserIterator(csv_file_name_, GetLinesAmount(csv_file_name_) + 1);
}

