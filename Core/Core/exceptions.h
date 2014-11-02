#pragma once

/* Holds all exceptions for the engine */

#include <exception>
#include <string>

class GenericException : public std::exception
{
	public:
		GenericException(const std::string msg = std::string(""), const std::string iheader = std::string("ERROR: ")) throw() : message(msg), _header(iheader) {};
		virtual const char* what() const throw() { return (_header + message).c_str(); };
		virtual std::string getMessage() const { return message; };
	private:
		std::string message;
		const std::string _header;
};


class DisplayException : public GenericException
{
	public:
		DisplayException(const std::string msg = std::string("")) throw() : GenericException(msg, "DISPLAY ERROR: ") {};
};

class ShaderException : public GenericException
{
	public:
		ShaderException(const std::string msg = std::string("")) throw() : GenericException(msg, "SHADER ERROR: ") {};
};

class ResourceException : public GenericException
{
	public:
		ResourceException(const std::string msg = std::string("")) throw() : GenericException(msg, "RESOURCE ERROR: ") {};
};