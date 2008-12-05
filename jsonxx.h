// Author: Hong Jiang <hong@hjiang.net>

#include <cassert>
#include <iostream>
#include <vector>

namespace jsonxx {

// A JSON Object
class Object {
  public:
    bool parse(std::istream& input);
};

class Value;

class Array {
  public:
    ~Array();
    bool parse(std::istream& input);

    unsigned int size() { return values_.size(); }

    template <typename T>
    bool is(unsigned int i);

    template <typename T>
    T& get(unsigned int i);

  private:
    std::vector<Value*> values_;
};

// A value could be a number, an array, a string, an object, a
// boolean, or null
class Value {
  public:
    class Null {};

    Value();
    ~Value();
    bool parse(std::istream& input);
    template<typename T>
    bool is();
    template<typename T>
    T& get();
  private:
    Value(const Value&);
    Value& operator=(const Value&);
    enum {
        INTEGER_,
        STRING_,
        BOOL_,
        NULL_,
        INVALID_
    } type_;
    union {
        long integer_value_;
        std::string* string_value_;
        bool bool_value_;
    };
};

template <typename T>
bool Array::is(unsigned int i) {
    assert(i < size());
    return values_[i]->is<T>();
}

template <typename T>
T& Array::get(unsigned int i) {
    assert(i < size());
    return values_[i]->get<T>();
}

template<>
inline bool Value::is<Value::Null>() {
    return type_ == NULL_;
}

template<>
inline bool Value::is<bool>() {
    return type_ == BOOL_;
}

template<>
inline bool Value::is<std::string>() {
    return type_ == STRING_;
}

template<>
inline bool Value::is<long>() {
    return type_ == INTEGER_;
}

template<>
inline bool& Value::get<bool>() {
    assert(is<bool>());
    return bool_value_;
}

template<>
inline std::string& Value::get<std::string>() {
    assert(is<std::string>());
    return *string_value_;
}

template<>
inline long& Value::get<long>() {
    assert(is<long>());
    return integer_value_;
}

}  // namespace jsonxx
