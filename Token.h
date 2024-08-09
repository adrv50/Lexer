#pragma once

#include <string>
#include <memory>

struct Token {
  enum class Kind {
    Int,
    Float,
    Char,
    String,
    Identifier,
    Keyword,
    Punctuater,
    End
  };

  Kind          kind;
  std::string   str;
  size_t        pos;

  bool is_value() const {
    switch( this->kind ) {
      case Kind::Int:
      case Kind::Float:
      case Kind::Char:
      case Kind::String:
        return true;
    }

    return false;
  }

  Token(Kind kind, std::string const& str, size_t pos = 0)
    : kind(kind),
      str(str),
      pos(pos)
  {
  }

  Token(Kind kind)
    : Token(kind, "", 0)
  {
  }
};