#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <iomanip>
#include <complex>

static const size_t COUNT_OF_KEYS = 3;

namespace khairullin {
  struct IntLL {
    long long int u;
  };

  struct Complex {
    std::complex< double > c;
  };

  struct DataStruct {
    IntLL key1;
    Complex key2;
    std::string key3;

    DataStruct():
      key1(IntLL()),
      key2(Complex()),
      key3("")
    {
    };

    DataStruct(IntLL m, Complex c, std::string s):
      key1(m),
      key2(c),
      key3(s)
    {
    }
  };

  class IOGuard {
    public:
      explicit IOGuard(std::basic_ios< char > & s);
      ~IOGuard();

    private:
      std::basic_ios< char > & s_;
      std::streamsize width_;
      std::streamsize precision_;
      std::basic_ios< char >::fmtflags fmtflags_;
      char fill_;
  };

  struct Delimeter {
    char expected;
  };

  std::istream & operator>>(std::istream & is, Delimeter && d);
  std::istream & operator>>(std::istream & is, IntLL & u);
  std::ostream & operator<<(std::ostream & is, IntLL u);
  std::istream & operator>>(std::istream & is, Complex & c);
  std::ostream & operator<<(std::ostream & is, Complex c);
  std::istream & operator>>(std::istream & is, DataStruct & d);
  std::ostream & operator<<(std::ostream & os, const DataStruct & d);
  bool operator<(const IntLL & a, const IntLL & b);
  bool operator==(const IntLL & a, const IntLL & b);
  bool operator!=(const IntLL & a, const IntLL & b);
  bool operator<(const Complex & a, const Complex & b);
  bool operator==(const Complex & a, const Complex & b);
  bool operator!=(const Complex & a, const Complex & b);
  bool operator==(const DataStruct & a, const DataStruct & b);
  bool myLess(const DataStruct & d1, const DataStruct & d2);
}

int main()
{
  std::vector< khairullin::DataStruct > v;
  using itt_t = std::istream_iterator< khairullin::DataStruct >;
  std::copy(itt_t{std::cin}, itt_t{}, std::back_inserter(v));
  std::sort(v.begin(), v.end(), khairullin::myLess);
  auto it = std::remove(v.begin(), v.end(), khairullin::DataStruct{});
  v.erase(it, v.end());
  using ott_t = std::ostream_iterator< khairullin::DataStruct >;
  std::copy(std::begin(v), std::end(v), ott_t{std::cout, "\n"});
}

std::istream & khairullin::operator>>(std::istream & is, Delimeter && d)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  char w = 0;
  is >> w;
  if (is && d.expected != w) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream & khairullin::operator>>(std::istream & is, IntLL & u)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  return is >> u.u;
}

std::ostream & khairullin::operator<<(std::ostream & os, IntLL u)
{
  std::ostream::sentry s(os);
  if (!s) {
    return os;
  }
  IOGuard guard(os);
  os << u.u;
  return os;
}

std::istream & khairullin::operator>>(std::istream & is, Complex & c)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  return is >> c.c;
}

std::ostream & khairullin::operator<<(std::ostream & os, Complex c)
{
  std::ostream::sentry s(os);
  if (!s) {
    return os;
  }
  IOGuard guard(os);
  return os << c.c;
}

std::istream & khairullin::operator>>(std::istream & is, DataStruct & d)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  DataStruct temp;
  DataStruct null;
  std::string line = "";
  std::getline(is, line);
  std::istringstream iss(line);
  iss >> Delimeter{'('};
  bool isKey1 = false, isKey2 = false, isKey3 = false;
  for (size_t i = 0; i < COUNT_OF_KEYS; i++) {
    std::string key = "";
    if (!iss) {
      d = null;
      return is;
    }
    iss >> key;
    if (iss && (key == ":key1" && !isKey1)) {
      char a = 0, b = 0;
      iss >> std::ws >> temp.key1 >> a >> b;
      if (a != b && (a == 'L' || a == 'l')) {
        d = null;
        return is;
      }
      isKey1 = true;
    } else if (iss && (key == ":key2" && !isKey2)) {
      iss >> std::ws >> Delimeter{'#'} >> Delimeter{'c'} >> temp.key2;
      isKey2 = true;
    } else if (iss && (key == ":key3" && !isKey3)) {
      iss >> std::ws >> std::quoted(temp.key3);
      isKey3 = true;
    } else {
      d = null;
      return is;
    }
  }
  iss >> Delimeter{':'} >> Delimeter{')'};
  if (iss) {
    d = temp;
  }
  else {
    d = null;
  }
  return is;
}

std::ostream & khairullin::operator<<(std::ostream & os, const DataStruct & d)
{
  std::ostream::sentry s(os);
  if (!s) {
    return os;
  }
  IOGuard guard(os);
  os << "(:key1 ";
  os << d.key1 << "ll";
  os << ":key2 " << "#c" << d.key2;
  os << ":key3 \"" << d.key3 << "\":)";
  return os;
}

bool khairullin::myLess(const DataStruct & d1, const DataStruct & d2)
{
  if (d1.key1 != d2.key1) {
    return d1.key1 < d2.key1;
  }
  if (d1.key2 != d2.key2) {
    return d1.key2 < d2.key2;
  }
  return d1.key3 < d2.key3;
}

bool khairullin::operator<(const IntLL & a, const IntLL & b)
{
  return a.u < b.u;
}
bool khairullin::operator==(const IntLL & a, const IntLL & b)
{
  return a.u == b.u;
}
bool khairullin::operator!=(const IntLL & a, const IntLL & b)
{
  return a.u != b.u;
}
bool khairullin::operator<(const Complex & a, const Complex & b)
{
  return abs(a.c) < abs(b.c);
}
bool khairullin::operator==(const Complex & a, const Complex & b)
{
  return a.c == b.c;
}
bool khairullin::operator!=(const Complex & a, const Complex & b)
{
  return a.c != b.c;
}

bool khairullin::operator==(const DataStruct & a, const DataStruct & b)
{
  return (a.key1 == b.key1) && (a.key2 == b.key2) && (a.key3 == b.key3);
}

khairullin::IOGuard::IOGuard(std::basic_ios< char > & s):
  s_(s),
  width_(s.width()),
  precision_(s.precision()),
  fill_(s.fill()),
  fmtflags_(s.flags())
{
}

khairullin::IOGuard::~IOGuard()
{
  s_.width(width_);
  s_.precision(precision_);
  s_.fill(fill_);
  s_.flags(fmtflags_);
}
