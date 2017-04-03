#pragma once

//cocos2d-x 의 Value 클래스의 일부분을 제거하고 long long 데이터를 받을 수 있도록 수정한 클래스

#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include <string>

class Wrapper
{
public:
	/** A predefined Wrapper that has not value. */
	static const Wrapper Null;

	/** Default constructor. */
	Wrapper();

	/** Create a Wrapper by an unsigned char value. */
	explicit Wrapper(unsigned char v);

	/** Create a Wrapper by an integer value. */
	explicit Wrapper(int v);

	/** Create a Wrapper by an unsigned value. */
	explicit Wrapper(unsigned int v);

	/** Create a Wrapper by a float value. */
	explicit Wrapper(float v);

	/** Create a Wrapper by a double value. */
	explicit Wrapper(double v);

	/** Create a Wrapper by a bool value. */
	explicit Wrapper(bool v);

	/** Create a Wrapper by a char pointer. It will copy the chars internally. */
	explicit Wrapper(const char* v);

	/** Create a Wrapper by a long long value. */
	explicit Wrapper(const long long v);

	/** Create a Wrapper by a string. */
	explicit Wrapper(const std::string& v);

	/** Create a Wrapper by another Wrapper object. */
	Wrapper(const Wrapper& other);
	/** Create a Wrapper by a Wrapper object. It will use std::move internally. */
	Wrapper(Wrapper&& other);

	/** Destructor. */
	~Wrapper();

	/** Assignment operator, assign from Wrapper to Wrapper. */
	Wrapper& operator= (const Wrapper& other);
	/** Assignment operator, assign from Wrapper to Wrapper. It will use std::move internally. */
	Wrapper& operator= (Wrapper&& other);

	/** Assignment operator, assign from unsigned char to Wrapper. */
	Wrapper& operator= (unsigned char v);
	/** Assignment operator, assign from integer to Wrapper. */
	Wrapper& operator= (int v);
	/** Assignment operator, assign from integer to Wrapper. */
	Wrapper& operator= (unsigned int v);
	/** Assignment operator, assign from long long to Wrapper. */
	Wrapper& operator= (long long v);
	/** Assignment operator, assign from float to Wrapper. */
	Wrapper& operator= (float v);
	/** Assignment operator, assign from double to Wrapper. */
	Wrapper& operator= (double v);
	/** Assignment operator, assign from bool to Wrapper. */
	Wrapper& operator= (bool v);
	/** Assignment operator, assign from char* to Wrapper. */
	Wrapper& operator= (const char* v);
	/** Assignment operator, assign from string to Wrapper. */
	Wrapper& operator= (const std::string& v);

	/** != operator overloading */
	bool operator!= (const Wrapper& v);
	/** != operator overloading */
	bool operator!= (const Wrapper& v) const;
	/** == operator overloading */
	bool operator== (const Wrapper& v);
	/** == operator overloading */
	bool operator== (const Wrapper& v) const;

	/** Gets as a byte value. Will convert to unsigned char if possible, or will trigger assert error. */
	unsigned char asByte() const;
	/** Gets as an integer value. Will convert to integer if possible, or will trigger assert error. */
	int asInt() const;
	/** Gets as an unsigned value. Will convert to unsigned if possible, or will trigger assert error. */
	unsigned int asUnsignedInt() const;
	/** Gets as an unsigned value. Will convert to long long if possible, or will trigger assert error. */
	long long asLongLong() const;
	/** Gets as a float value. Will convert to float if possible, or will trigger assert error. */
	float asFloat() const;
	/** Gets as a double value. Will convert to double if possible, or will trigger assert error. */
	double asDouble() const;
	/** Gets as a bool value. Will convert to bool if possible, or will trigger assert error. */
	bool asBool() const;
	/** Gets as a string value. Will convert to string if possible, or will trigger assert error. */
	std::string asString() const;

	/**
	* Checks if the Wrapper is null.
	* @return True if the Wrapper is null, false if not.
	*/
	inline bool isNull() const { return _type == Type::NONE; }

	/** Wrapper type wrapped by Wrapper. */
	enum class Type
	{
		/// no value is wrapped, an empty Wrapper
		NONE = 0,
		/// wrap byte
		BYTE,
		/// wrap integer
		INTEGER,
		/// wrap unsigned
		UNSIGNED,
		/// wrap long long
		LONGLONG,
		/// wrap float
		FLOAT,
		/// wrap double
		DOUBLE,
		/// wrap bool
		BOOLEAN,
		/// wrap string
		STRING
	};

	/** Gets the value type. */
	inline Type getType() const { return _type; }

	/** Gets the description of the class. */
	std::string getDescription() const;

private:
	void clear();
	void reset(Type type);

	union
	{
		unsigned char byteVal;
		int intVal;
		unsigned int unsignedVal;
		long long longlongVal;
		float floatVal;
		double doubleVal;
		bool boolVal;

		std::string* strVal;
	}_field;

	Type _type;
};
