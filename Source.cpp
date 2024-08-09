#include <iostream>
#include "Source.h"

Source::Source(std::string const& path)
  : data(""),
    file(new std::ifstream(path))
{
}

Source::~Source()
{
}

bool  Source::read() {
  if( this->fail() )
    return false;

  std::string line;

  while( std::getline(*this->file, line) )
    this->data += line + '\n';

  return true;
}
