#pragma once
#include <string>
class TestString
{
public:
	TestString()
		:data_(new char[1])
	{
		printf("default\n");
		*data_ = '\0';
	}
	TestString(const char* str)
		:data_(new char[strlen(str) + 1])
	{
		printf("char* constructor\n");
		strcpy(data_, str);
	}

	TestString(const TestString& rhs)
		:data_(new char[rhs.size() + 1])
	{
		printf("copy constructor\n");
		strcpy(data_, rhs.c_str());
	}

	TestString& operator=(TestString rhs)
	{
		printf("assign constructor\n");
		swap(rhs);
		return *this;
	}

	//TestString& operator=(TestString&& rhs)
	//{
	//	printf("assign constructor r\n");
	//	swap(rhs);
	//	return *this;
	//}

	TestString(TestString&& rhs) noexcept
		:data_(rhs.data_)
	{
		printf("copy constructor r\n");
		rhs.data_ = nullptr;
	}

	size_t size() const
	{
		return strlen(data_);
	}

	const char* c_str() const
	{
		return data_;
	}

	void swap(TestString& rhs)
	{
		std::swap(data_, rhs.data_);
	}

	~TestString()
	{
		delete[] data_;
	}
private:
	char* data_;
};

