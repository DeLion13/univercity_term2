#pragma once

#include <vector>
#include <string>

#include "optional.h"
#include "language.hpp"
#include "programmers.hpp"

using std::string;
using std::vector;

class Storage {
public:
  virtual bool load() = 0;
  virtual bool save() = 0;
  // Languages
  virtual vector<Language> getAllLanguages(void) = 0;
  virtual optional<Language> getLanguageById(int language_id) = 0;
  virtual bool updateLanguage(const Language & language) = 0;
  virtual bool removeLanguage(int language_id) = 0;
  virtual int insertLanguage(const Language & language) = 0;
  // Programmer
  virtual vector<Programmer> getAllProgrammer(void) = 0;
  virtual optional<Programmer> getProgrammerById(int lprogrammer_id) = 0;
  virtual bool updateProgrammer(const Programmer & programmer) = 0;
  virtual bool removeProgrammer(int programmer_id) = 0;
  virtual int insertProgrammer(const Programmer & programmer) = 0;
};
