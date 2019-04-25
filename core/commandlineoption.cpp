#include "commandlineoption.h"

#include <algorithm>

CommandLineOption::CommandLineOption(const std::string & name)
{
  init({name}, "");
}

CommandLineOption::CommandLineOption(const std::vector<std::string> & names)
  : mNames(names)
{
  init(names, "");
}

CommandLineOption::CommandLineOption(const std::string & name, const std::string & description,
                                     const std::string & valueName, const std::string & defaultValue)
{
  init(std::vector<std::string>{name}, description, valueName, defaultValue);
}

CommandLineOption::CommandLineOption(const std::vector<std::string> & names, const std::string & description,
                  const std::string & valueName, const std::string & defaultValue)
{
  init(names, description, valueName, defaultValue);
}

CommandLineOption::CommandLineOption(const CommandLineOption & other)
{
  *this = other;
}

CommandLineOption::~CommandLineOption()
{
}

std::vector<std::string> CommandLineOption::defaultValues() const
{
  return mDefaultValues;
}

std::string CommandLineOption::description() const
{
  return mDescription;
}

CommandLineOption::Flags CommandLineOption::flags() const
{
  return mFlags;
}

void CommandLineOption::init(const std::vector<std::string> & names, const std::string & description,
          const std::string & valueName, const std::string & defaultValue)
{
  mNames = names;
  mValueName = valueName;
  mDescription = description;
  mFlags = None;
  if (!defaultValue.empty()) {
    mDefaultValues.push_back(defaultValue);
  }
}

std::vector<std::string> CommandLineOption::names() const
{
  return mNames;
}

void CommandLineOption::setDefaultValue(const std::string & defaultValue)
{
  std::vector<std::string> values;
  values.push_back(defaultValue);
  setDefaultValues(values);
}

void CommandLineOption::setDefaultValues(const std::vector<std::string> & defaultValues)
{
  mDefaultValues = defaultValues;
}

void CommandLineOption::setDescription(const std::string & description)
{
  mDescription = description;
}

void CommandLineOption::setFlags(Flags flags)
{
  mFlags = flags;
}

void CommandLineOption::setValueName(const std::string & valueName)
{
  mValueName = valueName;
}

void CommandLineOption::swap(const CommandLineOption & other)
{
  //std::swap(*this, other);
}

std::string CommandLineOption::valueName() const
{
  return mValueName;
}

CommandLineOption & CommandLineOption::operator =(const CommandLineOption & other)
{
  if (this == &other)
    return *this;

  mNames = other.names();
  mDescription = other.description();
  mDefaultValues = other.defaultValues();
  mFlags = other.flags();
  mValueName = other.valueName();

  return *this;
}

CommandLineOption & CommandLineOption::operator =(CommandLineOption && other)
{
  if (this == &other)
    return *this;

  mNames = other.names();
  mDescription = other.description();
  mDefaultValues = other.defaultValues();
  mFlags = other.flags();
  mValueName = other.valueName();

  return *this;
}
