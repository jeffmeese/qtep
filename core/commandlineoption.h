#ifndef COMMANDLINEOPTION_H
#define COMMANDLINEOPTION_H

#include "pathloss.h"

#include <string>
#include <vector>

class CommandLineOption
{
public:
  enum Flags
  {
    None = 0x00,
    HiddenFromHelp = 0x01,
    ShortOptionStyle = 0x02
  };

public:
  PATHLOSS_DECLSPEC CommandLineOption(const std::string & name);
  PATHLOSS_DECLSPEC CommandLineOption(const std::vector<std::string> & names);
  PATHLOSS_DECLSPEC CommandLineOption(const std::string & name, const std::string & description,
                    const std::string & valueName = std::string(), const std::string & defaultValue = std::string());
  PATHLOSS_DECLSPEC CommandLineOption(const std::vector<std::string> & names, const std::string & description,
                    const std::string & valueName = std::string(), const std::string & defaultValue = std::string());

  PATHLOSS_DECLSPEC CommandLineOption(const CommandLineOption & other);
  PATHLOSS_DECLSPEC ~CommandLineOption();

public:
  PATHLOSS_DECLSPEC std::vector<std::string> defaultValues() const;
  PATHLOSS_DECLSPEC std::string description() const;
  PATHLOSS_DECLSPEC Flags flags() const;
  PATHLOSS_DECLSPEC std::vector<std::string> names() const;
  PATHLOSS_DECLSPEC std::string valueName() const;
  PATHLOSS_DECLSPEC void setDefaultValue(const std::string & defaultValue);
  PATHLOSS_DECLSPEC void setDefaultValues(const std::vector<std::string> & defaultValues);
  PATHLOSS_DECLSPEC void setDescription(const std::string & description);
  PATHLOSS_DECLSPEC void setFlags(Flags flags);
  PATHLOSS_DECLSPEC void setValueName(const std::string & valueName);
  PATHLOSS_DECLSPEC void swap(const CommandLineOption & other);

public:
  PATHLOSS_DECLSPEC CommandLineOption & operator=(const CommandLineOption & other);
  PATHLOSS_DECLSPEC CommandLineOption & operator=(CommandLineOption && other);

private:
  void init(const std::vector<std::string> & names, const std::string & description,
            const std::string & valueName = std::string(), const std::string & defaulValue = std::string());
private:
  std::string mDescription;
  std::string mValueName;
  std::vector<std::string> mDefaultValues;
  std::vector<std::string> mNames;
  Flags mFlags;
};

#endif // COMMANDLINEOPTION_H
