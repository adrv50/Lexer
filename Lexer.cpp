#include <cctype>
#include "Lexer.h"

static char const* punctuaters[] {
  "<<=", ">>=",   // shift assign
  "->",           // return type specifier (in function definition)
  "<<", ">>",
  "<=", ">=",
  "==", "!=",
  "..",   // immidiately range expr
  "&&", "||",
  "<",
  ">",
  "+",
  "-",
  "/",
  "*",
  "%",
  "=",
  ";",
  ":",
  ",",
  ".",
  "[",
  "]",
  "(",
  ")",
  "{",
  "}",
  "!",
  "?",
  "&",
  "^",
  "|",
};

Lexer::Lexer(Source& source)
  : _source(source),
    _position(0)
{
}

Lexer::~Lexer()
{
}

std::vector<Token>  Lexer::lex() {
  std::vector<Token>  vec;

  this->pass_space();

  while( this->check() ) {

    auto c = this->peek();
    auto pos = this->_position;

    //
    // hexadecimal
    //
    if( this->match("0x") ) {
      while( isxdigit(this->peek()) )
        this->_position++;

      vec.emplace_back(
        Token::Kind::Int, std::string(this->backtrim_to(pos)), pos);
    }

    //
    // decimal
    //
    else if( isdigit(c) ) {
      while( isdigit(this->peek()) )
        this->_position++;

      //
      // float
      if( this->peek() == '.' ) {
        this->_position++;

        while( isdigit(this->peek()) )
          this->_position++;

        this->consume('f');

        vec.emplace_back(
          Token::Kind::Float, std::string(this->backtrim_to(pos)), pos);
      }
      else {
        vec.emplace_back(
          Token::Kind::Int, std::string(this->backtrim_to(pos)), pos);
      }
    }

    //
    // char
    //
    else if( c == '\'' ) {
      
    }


    //
    // punctuaters
    //
    else if( !this->eat_punctuater(vec) ) {
      // Error::fatal_error("invalid token");
      

      /*
       * 無効なトークンが検知された場合の処理をここに記述
       */

      std::exit(1);
    }

    this->pass_space();
  }

  return vec;
}

//
// pass_space:
//   現在位置から空白じゃないとこまで飛ばす
//
void Lexer::pass_space() {
  while( std::isspace(this->peek()) )
    this->_position++;
}

//
// match:
//   現在位置に str と同じ文字列があるかどうか
//
bool Lexer::match(std::string_view str) {
  return this->check() && this->trim(str.length()) == str;
}

void  Lexer::consume(char c) {
  if( this->peek() == c )
    this->_position++;
}

void  Lexer::consume(std::string_view s) {
  if( this->match(s) )
    this->_position += s.length();
}

//
// trim:
//   現在位置から len の文字数だけを切り取って返す
//
std::string_view Lexer::trim(size_t len) const {
  auto iter = this->_source.data.begin() + this->_position;

  return { iter, iter + len };
}

//
// backtrim:
//   現在位置から後方に len の文字数だけを切り取って返す
//
std::string_view Lexer::backtrim(size_t len) const {
  auto iter = this->_source.data.begin() + this->_position;

  return { iter - len, iter };
}

//
// backtrim_to:
//   pos から現在位置までの文字数だけを切り取って返す
//
std::string_view Lexer::backtrim_to(size_t pos) const {
  return { this->_source.data.begin() + pos,
            this->_source.data.begin() + this->_position };
}

//
// eat_punctuater:
//   記号文字列がマッチした場合、引数 vec にトークンとして追加し true を返す
//   そうでないなら false
//
bool Lexer::eat_punctuater(std::vector<Token>& vec) {
  for( std::string_view pu : punctuaters ) {
    if( this->match(pu) ) {
      vec.emplace_back(Token::Kind::Punctuater, std::string(pu), this->_position);
      this->_position += pu.length();
      return true;
    }
  }

  return false;
}
