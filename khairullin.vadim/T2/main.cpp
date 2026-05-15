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
    std::string expected;
  };

  std::istream & operator>>(std::istream & is, Delimeter && d);
  //std::ostream & operator<<(std::ostream & os, Delimeter d);
  std::istream & operator>>(std::istream & is, IntLL & u);
  std::ostream & operator<<(std::ostream & is, IntLL u);
  std::istream & operator>>(std::istream & is, Complex & c);
  std::ostream & operator<<(std::ostream & is, Complex c);
  std::istream & operator>>(std::istream & is, DataStruct & d);
  std::ostream & operator<<(std::ostream & os, DataStruct d);
}

int main()
{
  std::vector< khairullin::IntLL > v;
  using itt_t = std::istream_iterator< khairullin::IntLL >;
  std::copy(itt_t{std::cin}, itt_t{}, std::back_inserter(v));
  using ott_t = std::ostream_iterator< khairullin::IntLL >;
  std::copy(std::begin(v), std::end(v), ott_t{std::cout, "\n"});
}

std::istream & khairullin::operator>>(std::istream & is, Delimeter && d)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  std::string w = "";
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
  return is >> u.u >> Delimeter{"ll"};
}

std::ostream & khairullin::operator<<(std::ostream & os, IntLL u)
{
  std::ostream::sentry s(os);
  if (!s) {
    return os;
  }
  os << u.u << "ll";
  return os;
}

std::istream & khairullin::operator>>(std::istream & is, Complex & c)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  return is >> Delimeter{"#c"} >> c.c;
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