#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <complex>

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
    {};
    DataStruct(IntLL m, Complex c, std::string s):
    key1(m),
    key2(c),
    key3(s)
    {}
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
  //std::ostream & operator<<(std::ostream & os, Delimeter d);
  std::istream & operator>>(std::istream & is, IntLL & u);
  std::ostream & operator<<(std::ostream & is, IntLL u);
  std::istream & operator>>(std::istream & is, Complex & c);
  std::ostream & operator<<(std::ostream & is, Complex c);
  std::istream & operator>>(std::istream & is, DataStruct & d);
  std::ostream & operator<<(std::ostream & os, const DataStruct & d);
}

int main()
{
  /*std::vector< khairullin::DataStruct > v;
  using itt_t = std::istream_iterator< khairullin::DataStruct >;
  std::copy(itt_t{std::cin}, itt_t{}, std::back_inserter(v));
  using ott_t = std::ostream_iterator< khairullin::DataStruct >;
  std::copy(std::begin(v), std::end(v), ott_t{std::cout, "\n"});*/
  khairullin::DataStruct d;
  std::cin >> d;
  std::cout << d;
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
  is >> Delimeter{'('};
  bool isKey1 = false, isKey2 = false, isKey3 = false;
  for (size_t i = 0; i < 3; i++) {
    std::string key = "";
    if (!is) {
      return is;
    }
    is >> key;
    if (key == ":key1" && !isKey1) {
      is >> std::ws >> d.key1 >> Delimeter{'l'} >> Delimeter{'l'};
      isKey1 = true;
    }
    else if (key == ":key2" && !isKey2) {
      is >> std::ws >> Delimeter{'#'} >> Delimeter{'c'} >> d.key2;
      isKey2 = true;
    }
    else if (key == ":key3" && !isKey3) {
      is >> std::ws >> std::quoted(d.key3);
      isKey3 = true;
    }
    else {
      is.setstate(std::ios::failbit);
      return is;
    }
  }
  is >> Delimeter{':'} >> Delimeter{')'};
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

khairullin::IOGuard::IOGuard(std::basic_ios< char > & s):
s_(s),
width_(s.width()),
precision_(s.precision()),
fill_(s.fill()),
fmtflags_(s.flags())
{}

khairullin::IOGuard::~IOGuard()
{
  s_.width(width_);
  s_.precision(precision_);
  s_.fill(fill_);
  s_.flags(fmtflags_);
}