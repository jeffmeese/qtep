#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include "pathloss.h"

#include <string>
#include <vector>
#include <map>

#include "commandlineoption.h"

class CommandLineParser
{
public:
  enum SingleDashWordOptionMode
  {
    ParseAsCompactedShortOptions = 0,
    ParseAsLongOptions = 1
  };

  enum OptionsAfterPositionalArgumentsMode
  {
    ParseAsOptions = 0,
    ParseAsPositionArguments = 1
  };

public:
  PATHLOSS_DECLSPEC CommandLineParser(const std::string & applicationName);

public:
  PATHLOSS_DECLSPEC std::string applicationDescription() const;
  PATHLOSS_DECLSPEC std::string applicationName() const;
  PATHLOSS_DECLSPEC std::string applicationVersion() const;
  PATHLOSS_DECLSPEC std::string errorText() const;
  PATHLOSS_DECLSPEC std::string helpText() const;
  PATHLOSS_DECLSPEC int lineBreakColumn() const;
  PATHLOSS_DECLSPEC void setApplicationDescription(const std::string & description);
  PATHLOSS_DECLSPEC void setApplicationName(const std::string & name);
  PATHLOSS_DECLSPEC void setApplicationVersion(const std::string & version);
  PATHLOSS_DECLSPEC void setLineBreakColumn(int column);
  PATHLOSS_DECLSPEC void setOptionsAfterPositionArgumentsMode(OptionsAfterPositionalArgumentsMode parsingMode);
  PATHLOSS_DECLSPEC void setSingleDashWordOptionMode(SingleDashWordOptionMode singleDashWordOptionMode);

public:
  PATHLOSS_DECLSPEC CommandLineOption addHelpOption();
  PATHLOSS_DECLSPEC bool addOption(const CommandLineOption & option);
  PATHLOSS_DECLSPEC bool addOptions(const std::vector<CommandLineOption> & options);
  PATHLOSS_DECLSPEC void addPositionalArgument(const std::string & name, const std::string description, const std::string & syntax = std::string());
  PATHLOSS_DECLSPEC CommandLineOption addVersionOption();
  PATHLOSS_DECLSPEC void clearPositionArguments();
  PATHLOSS_DECLSPEC bool isSet(const std::string & name) const;
  PATHLOSS_DECLSPEC bool isSet(const CommandLineOption & option) const;
  PATHLOSS_DECLSPEC std::vector<std::string> optionNames() const;
  PATHLOSS_DECLSPEC bool parse(const std::vector<std::string> & arguments);
  PATHLOSS_DECLSPEC bool parse(int argc, char ** argv);
  PATHLOSS_DECLSPEC std::vector<std::string> positionalArguments() const;
  PATHLOSS_DECLSPEC void process(std::vector<std::string> & arguments);
  PATHLOSS_DECLSPEC void showHelp(int exitCode = 0);
  PATHLOSS_DECLSPEC void showVersion();
  PATHLOSS_DECLSPEC std::vector<std::string> unknownOptionNames() const;
  PATHLOSS_DECLSPEC std::string value(const std::string & optionName) const;
  PATHLOSS_DECLSPEC std::string value(const CommandLineOption & option) const;
  PATHLOSS_DECLSPEC std::vector<std::string> values(const std::string & optionName) const;
  PATHLOSS_DECLSPEC std::vector<std::string> values(const CommandLineOption & option) const;

private:
  struct PositionalArgument
  {
    std::string name;
    std::string description;
    std::string syntax;
  };

private:
  typedef std::vector<PositionalArgument> ArgumentVector;
  typedef std::vector<CommandLineOption> OptionVector;
  typedef std::vector<std::string> string_vector;
  typedef std::map<std::string, string_vector> OptionValueMap;

private:
  bool checkNameConflict(const std::string & name) const;
  bool checkNameEmpty(const CommandLineOption & option) const;
  std::size_t computeHelpSpacing() const;
  const CommandLineOption * findOption(const std::string & name) const;
  std::vector<std::string> formatArguments(const string_vector & arguments) const;
  void init(const std::string & applicationName);
  bool parseOption(const std::string & arg, std::size_t & index, const string_vector & arguments, bool isLong);
  bool parsePositionalArgument(const std::string & arg);

private:
  bool mInPositional;
  int mLineBreakColumn;
  int mIndent;
  std::string mApplicationDescription;
  std::string mApplicationVersion;
  std::string mHelpText;
  std::string mApplicationName;
  std::string mErrorText;
  CommandLineOption mHelpOption;
  CommandLineOption mVersionOption;
  OptionsAfterPositionalArgumentsMode mArgumentMode;
  SingleDashWordOptionMode mDashMode;
  ArgumentVector mPositionArguments;
  OptionVector mOptions;
  string_vector mOptionsSet;
  string_vector mUnknownOptions;
  OptionValueMap mOptionValues;
  string_vector mPositionArgumentsSpecified;
};

#endif // COMMANDLINEPARSER_H
