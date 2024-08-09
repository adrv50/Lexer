#pragma once

#include <vector>
#include "Source.h"
#include "Token.h"

class Lexer {

public:
  Lexer(Source& source);
  ~Lexer();

  std::vector<Token>  lex();

private:
  bool check() const {
    return this->_position < this->_source.data.length();
  }

  char peek() const {
    return this->_source.data[this->_position];
  }

  void pass_space();
  bool match(std::string_view s);

  void consume(char c);
  void consume(std::string_view s);

  std::string_view trim(size_t len) const;
  std::string_view backtrim(size_t len) const;
  std::string_view backtrim_to(size_t pos) const;
  bool eat_punctuater(std::vector<Token>& vec);

  Source&   _source;
  size_t    _position;

};
