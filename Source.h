#pragma once

#include <string>
#include <fstream>
#include <memory>

class Lexer;
struct Token;
class Source {

  friend class Lexer;
  friend class Token;

public:
  Source() = delete;
  Source(Source&&) = delete;
  Source(Source const&) = delete;

  Source(std::string const& path);
  ~Source();

  bool  fail() const {
    return this->file->fail();
  }

  bool  read();

private:

  std::string   data;
  std::unique_ptr<std::ifstream>  file;

};