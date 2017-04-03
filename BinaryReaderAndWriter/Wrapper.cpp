#include "Wrapper.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include "base/ccUtils.h"

using namespace cocos2d;

const Wrapper Wrapper::Null;

Wrapper::Wrapper()
	: _type(Type::NONE)
{
	memset(&_field, 0, sizeof(_field));
}

Wrapper::Wrapper(unsigned char v)
	: _type(Type::BYTE)
{
	_field.byteVal = v;
}

Wrapper::Wrapper(int v)
	: _type(Type::INTEGER)
{
	_field.intVal = v;
}

Wrapper::Wrapper(unsigned int v)
	: _type(Type::UNSIGNED)
{
	_field.unsignedVal = v;
}

Wrapper::Wrapper(float v)
	: _type(Type::FLOAT)
{
	_field.floatVal = v;
}

Wrapper::Wrapper(double v)
	: _type(Type::DOUBLE)
{
	_field.doubleVal = v;
}

Wrapper::Wrapper(bool v)
	: _type(Type::BOOLEAN)
{
	_field.boolVal = v;
}

Wrapper::Wrapper(const char* v)
	: _type(Type::STRING)
{
	_field.strVal = new (std::nothrow) std::string();
	if (v)
	{
		*_field.strVal = v;
	}
}

Wrapper::Wrapper(const long long v)
	: _type(Type::LONGLONG)
{
	_field.longlongVal = v;
}

Wrapper::Wrapper(const std::string& v)
	: _type(Type::STRING)
{
	_field.strVal = new (std::nothrow) std::string();
	*_field.strVal = v;
}

Wrapper::Wrapper(const Wrapper& other)
	: _type(Type::NONE)
{
	*this = other;
}

Wrapper::Wrapper(Wrapper&& other)
	: _type(Type::NONE)
{
	*this = std::move(other);
}

Wrapper::~Wrapper()
{
	clear();
}

Wrapper& Wrapper::operator= (const Wrapper& other)
{
	if (this != &other) {
		reset(other._type);

		switch (other._type) {
		case Type::BYTE:
			_field.byteVal = other._field.byteVal;
			break;
		case Type::INTEGER:
			_field.intVal = other._field.intVal;
			break;
		case Type::UNSIGNED:
			_field.unsignedVal = other._field.unsignedVal;
			break;
		case Type::LONGLONG:
			_field.longlongVal = other._field.longlongVal;
			break;
		case Type::FLOAT:
			_field.floatVal = other._field.floatVal;
			break;
		case Type::DOUBLE:
			_field.doubleVal = other._field.doubleVal;
			break;
		case Type::BOOLEAN:
			_field.boolVal = other._field.boolVal;
			break;
		case Type::STRING:
			if (_field.strVal == nullptr)
			{
				_field.strVal = new std::string();
			}
			*_field.strVal = *other._field.strVal;
			break;
		default:
			break;
		}
	}
	return *this;
}

Wrapper& Wrapper::operator= (Wrapper&& other)
{
	if (this != &other)
	{
		clear();
		switch (other._type)
		{
		case Type::BYTE:
			_field.byteVal = other._field.byteVal;
			break;
		case Type::INTEGER:
			_field.intVal = other._field.intVal;
			break;
		case Type::LONGLONG:
			_field.longlongVal = other._field.longlongVal;
			break;
		case Type::UNSIGNED:
			_field.unsignedVal = other._field.unsignedVal;
			break;
		case Type::FLOAT:
			_field.floatVal = other._field.floatVal;
			break;
		case Type::DOUBLE:
			_field.doubleVal = other._field.doubleVal;
			break;
		case Type::BOOLEAN:
			_field.boolVal = other._field.boolVal;
			break;
		case Type::STRING:
			_field.strVal = other._field.strVal;
			break;
		default:
			break;
		}
		_type = other._type;

		memset(&other._field, 0, sizeof(other._field));
		other._type = Type::NONE;
	}

	return *this;
}

Wrapper& Wrapper::operator= (unsigned char v)
{
	reset(Type::BYTE);
	_field.byteVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (int v)
{
	reset(Type::INTEGER);
	_field.intVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (unsigned int v)
{
	reset(Type::UNSIGNED);
	_field.unsignedVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (long long v)
{
	reset(Type::LONGLONG);
	_field.longlongVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (float v)
{
	reset(Type::FLOAT);
	_field.floatVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (double v)
{
	reset(Type::DOUBLE);
	_field.doubleVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (bool v)
{
	reset(Type::BOOLEAN);
	_field.boolVal = v;
	return *this;
}

Wrapper& Wrapper::operator= (const char* v)
{
	reset(Type::STRING);
	*_field.strVal = v ? v : "";
	return *this;
}

Wrapper& Wrapper::operator= (const std::string& v)
{
	reset(Type::STRING);
	*_field.strVal = v;
	return *this;
}

bool Wrapper::operator!= (const Wrapper& v)
{
	return !(*this == v);
}
bool Wrapper::operator!= (const Wrapper& v) const
{
	return !(*this == v);
}

bool Wrapper::operator== (const Wrapper& v)
{
	const auto &t = *this;
	return t == v;
}
bool Wrapper::operator== (const Wrapper& v) const
{
	if (this == &v) return true;
	if (v._type != this->_type) return false;
	if (this->isNull()) return true;
	switch (_type)
	{
	case Type::BYTE:    return v._field.byteVal == this->_field.byteVal;
	case Type::INTEGER: return v._field.intVal == this->_field.intVal;
	case Type::UNSIGNED:return v._field.unsignedVal == this->_field.unsignedVal;
	case Type::LONGLONG:return v._field.longlongVal == this->_field.longlongVal;
	case Type::BOOLEAN: return v._field.boolVal == this->_field.boolVal;
	case Type::STRING:  return *v._field.strVal == *this->_field.strVal;
	case Type::FLOAT:   return std::abs(v._field.floatVal - this->_field.floatVal) <= FLT_EPSILON;
	case Type::DOUBLE:  return std::abs(v._field.doubleVal - this->_field.doubleVal) <= DBL_EPSILON;
	default:
		break;
	};

	return false;
}

/// Convert value to a specified type
unsigned char Wrapper::asByte() const
{
	if (_type == Type::BYTE)
	{
		return _field.byteVal;
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<unsigned char>(_field.intVal);
	}

	if (_type == Type::UNSIGNED)
	{
		return static_cast<unsigned char>(_field.unsignedVal);
	}

	if (_type == Type::LONGLONG)
	{
		return static_cast<unsigned char>(_field.longlongVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<unsigned char>(atoi(_field.strVal->c_str()));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned char>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned char>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1 : 0;
	}

	return 0;
}

int Wrapper::asInt() const
{
	if (_type == Type::INTEGER)
	{
		return _field.intVal;
	}

	if (_type == Type::UNSIGNED)
	{
		CCASSERT(_field.unsignedVal < INT_MAX, "Can only convert values < INT_MAX");
		return (int)_field.unsignedVal;
	}

	if (_type == Type::UNSIGNED)
	{
		CCASSERT(_field.longlongVal < INT_MAX, "Can only convert values < INT_MAX");
		return (int)_field.longlongVal;
	}

	if (_type == Type::BYTE)
	{
		return _field.byteVal;
	}

	if (_type == Type::STRING)
	{
		return atoi(_field.strVal->c_str());
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<int>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<int>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1 : 0;
	}

	return 0;
}


unsigned int Wrapper::asUnsignedInt() const
{
	if (_type == Type::UNSIGNED)
	{
		return _field.unsignedVal;
	}

	if (_type == Type::LONGLONG)
	{
		CCASSERT(_field.longlongVal >= 0, "Only values >= 0 can be converted to unsigned");
		return static_cast<unsigned int>(_field.longlongVal);
	}

	if (_type == Type::INTEGER)
	{
		CCASSERT(_field.intVal >= 0, "Only values >= 0 can be converted to unsigned");
		return static_cast<unsigned int>(_field.intVal);
	}

	if (_type == Type::BYTE)
	{
		return static_cast<unsigned int>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		// NOTE: strtoul is required (need to augment on unsupported platforms)
		return static_cast<unsigned int>(strtoul(_field.strVal->c_str(), nullptr, 10));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned int>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned int>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1u : 0u;
	}

	return 0u;
}

long long Wrapper::asLongLong() const
{
	if (_type == Type::LONGLONG)
	{
		return _field.longlongVal;
	}

	if (_type == Type::INTEGER)
	{
		return _field.intVal;
	}

	if (_type == Type::UNSIGNED)
	{
		return _field.unsignedVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<unsigned long long>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		// NOTE: strtoul is required (need to augment on unsupported platforms)
		return static_cast<unsigned long long>(strtoul(_field.strVal->c_str(), nullptr, 10));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned long long>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned long long>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1u : 0u;
	}

	return 0ll;
}

float Wrapper::asFloat() const
{
	if (_type == Type::FLOAT)
	{
		return _field.floatVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<float>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		return utils::atof(_field.strVal->c_str());
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<float>(_field.intVal);
	}

	if (_type == Type::UNSIGNED)
	{
		return static_cast<float>(_field.unsignedVal);
	}

	if (_type == Type::LONGLONG)
	{
		return static_cast<float>(_field.longlongVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<float>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1.0f : 0.0f;
	}

	return 0.0f;
}

double Wrapper::asDouble() const
{
	if (_type == Type::DOUBLE)
	{
		return _field.doubleVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<double>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<double>(utils::atof(_field.strVal->c_str()));
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<double>(_field.intVal);
	}

	if (_type == Type::UNSIGNED)
	{
		return static_cast<double>(_field.unsignedVal);
	}

	if (_type == Type::LONGLONG)
	{
		return static_cast<double>(_field.longlongVal);
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<double>(_field.floatVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1.0 : 0.0;
	}

	return 0.0;
}

bool Wrapper::asBool() const
{
	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal;
	}

	if (_type == Type::BYTE)
	{
		return _field.byteVal == 0 ? false : true;
	}

	if (_type == Type::STRING)
	{
		return (*_field.strVal == "0" || *_field.strVal == "false") ? false : true;
	}

	if (_type == Type::INTEGER)
	{
		return _field.intVal == 0 ? false : true;
	}

	if (_type == Type::UNSIGNED)
	{
		return _field.unsignedVal == 0 ? false : true;
	}

	if (_type == Type::LONGLONG)
	{
		return _field.longlongVal == 0 ? false : true;
	}

	if (_type == Type::FLOAT)
	{
		return _field.floatVal == 0.0f ? false : true;
	}

	if (_type == Type::DOUBLE)
	{
		return _field.doubleVal == 0.0 ? false : true;
	}

	return false;
}

std::string Wrapper::asString() const
{
	if (_type == Type::STRING)
	{
		return *_field.strVal;
	}

	std::stringstream ret;

	switch (_type)
	{
	case Type::BYTE:
		ret << _field.byteVal;
		break;
	case Type::INTEGER:
		ret << _field.intVal;
		break;
	case Type::UNSIGNED:
		ret << _field.unsignedVal;
		break;
	case Type::LONGLONG:
		ret << _field.longlongVal;
		break;
	case Type::FLOAT:
		ret << std::fixed << std::setprecision(7) << _field.floatVal;
		break;
	case Type::DOUBLE:
		ret << std::fixed << std::setprecision(16) << _field.doubleVal;
		break;
	case Type::BOOLEAN:
		ret << (_field.boolVal ? "true" : "false");
		break;
	default:
		break;
	}
	return ret.str();
}

static std::string getTabs(int depth)
{
	std::string tabWidth;

	for (int i = 0; i < depth; ++i)
	{
		tabWidth += "\t";
	}

	return tabWidth;
}

static std::string visit(const Wrapper& v, int depth);

template <class T>
static std::string visitMap(const T& v, int depth)
{
	std::stringstream ret;

	if (depth > 0)
		ret << "\n";

	ret << getTabs(depth) << "{\n";

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		ret << getTabs(depth + 1) << iter->first << ": ";
		ret << visit(iter->second, depth + 1);
	}

	ret << getTabs(depth) << "}\n";

	return ret.str();
}

static std::string visit(const Wrapper& v, int depth)
{
	std::stringstream ret;

	switch (v.getType())
	{
	case Wrapper::Type::NONE:
	case Wrapper::Type::BYTE:
	case Wrapper::Type::INTEGER:
	case Wrapper::Type::UNSIGNED:
	case Wrapper::Type::LONGLONG:
	case Wrapper::Type::FLOAT:
	case Wrapper::Type::DOUBLE:
	case Wrapper::Type::BOOLEAN:
	case Wrapper::Type::STRING:
		ret << v.asString() << "\n";
		break;
	default:
		CCASSERT(false, "Invalid type!");
		break;
	}

	return ret.str();
}

std::string Wrapper::getDescription() const
{
	std::string ret("\n");
	ret += visit(*this, 0);
	return ret;
}

void Wrapper::clear()
{
	// Free memory the old value allocated
	switch (_type)
	{
	case Type::BYTE:
		_field.byteVal = 0;
		break;
	case Type::INTEGER:
		_field.intVal = 0;
		break;
	case Type::UNSIGNED:
		_field.unsignedVal = 0u;
		break;
	case Type::LONGLONG:
		_field.longlongVal = 0ll;
		break;
	case Type::FLOAT:
		_field.floatVal = 0.0f;
		break;
	case Type::DOUBLE:
		_field.doubleVal = 0.0;
		break;
	case Type::BOOLEAN:
		_field.boolVal = false;
		break;
	case Type::STRING:
		CC_SAFE_DELETE(_field.strVal);
		break;
	default:
		break;
	}

	_type = Type::NONE;
}

void Wrapper::reset(Type type)
{
	if (_type == type)
		return;

	clear();

	// Allocate memory for the new value
	switch (type)
	{
	case Type::STRING:
		_field.strVal = new (std::nothrow) std::string();
		break;
	default:
		break;
	}

	_type = type;
}