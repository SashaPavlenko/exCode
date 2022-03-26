#pragma once
#include <exception>
#include <string>

// ����� MyFileExceprion, ���������� ��� ������� ����������, ��������� � ���������� ������.
class MyFileExceprion : public std::exception
{
private:
	std::string m_error;

public:
	MyFileExceprion(std::string error): m_error(error) {}

	// ���������� std::string � �������� ����������� ������ C-style
	const char* what() const noexcept { return m_error.c_str(); }
};
