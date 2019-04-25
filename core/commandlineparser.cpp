#include "commandlineparser.h"
#include "commandlineoption.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>

CommandLineParser::CommandLineParser(const std::string & applicationName)
  : mHelpOption(CommandLineOption(string_vector{"h", "help"}, "Display this help."))
  , mVersionOption(CommandLineOption(string_vector{"v", "version"}, "Displays version information."))
{
  init(applicationName);
}

CommandLineOption CommandLineParser::addHelpOption()
{
  addOption(mHelpOption);
  return mHelpOption;
}

bool CommandLineParser::addOption(const CommandLineOption & option)
{
  if (checkNameEmpty(option))
    return false;

  string_vector names = option.names();
  for (std::size_t i = 0; i < names.size(); i++) {
    const std::string & name = names.at(i);
    if (checkNameConflict(name)) {
      return false;
    }
  }

  mOptions.push_back(option);
  return true;
}

bool CommandLineParser::addOptions(const std::vector<CommandLineOption> &options)
{
  for (std::size_t i = 0; i < options.size(); i++) {
    if (!addOption(options.at(i))) {
      return false;
    }
  }
  return true;
}

void CommandLineParser::addPositionalArgument(const std::string & name, const std::string description, const std::string & syntax)
{
  PositionalArgument argument = {name, description, syntax};
  mPositionArguments.push_back(argument);
}

CommandLineOption CommandLineParser::addVersionOption()
{
  addOption(mVersionOption);
  return mVersionOption;
}

std::string CommandLineParser::applicationDescription() const
{
  return mApplicationDescription;
}

std::string CommandLineParser::applicationVersion() const
{
  return mApplicationVersion;
}

bool CommandLineParser::checkNameConflict(const std::string &name) const
{
  for (std::size_t i = 0; i < mOptions.size(); i++) {
    string_vector names = mOptions.at(i).names();
    for (std::size_t j = 0; j < names.size(); j++) {
      if (names.at(j) == name)
        return true;
    }
  }
  return false;
}

bool CommandLineParser::checkNameEmpty(const CommandLineOption &option) const
{
  string_vector names = option.names();
  if (names.size() == 0) {
    return true;
  }

  for (std::size_t i = 0; i < names.size(); i++) {
    std::string name = names.at(i);
    if (!name.empty())
      return false;
  }

  return true;
}

void CommandLineParser::clearPositionArguments()
{
  mPositionArguments.clear();
}

std::size_t CommandLineParser::computeHelpSpacing() const
{
  std::size_t maxWidth = 0;
  for (std::size_t i = 0; i < mOptions.size(); i++) {
    const CommandLineOption & option = mOptions.at(i);
    string_vector names = option.names();
    std::size_t totalLength = mIndent + 1;
    for (std::size_t j = 0; j < names.size(); j++) {
      const std::string & name = names.at(j);
      totalLength += 1;
      if (name.size() > 1) {
        totalLength += 1;
      }
      totalLength += name.size();
    }

    if (names.size() > 1) {
      totalLength += (2*(names.size()-1)); // Adjust for comma and space
    }

    if (!option.valueName().empty()) {
      totalLength += option.valueName().length() + 2; // Adjust for <value>
    }

    if (i == 0 || totalLength > maxWidth) {
      maxWidth = totalLength;
    }
  }

  for (std::size_t i = 0; i < mPositionArguments.size(); i++) {
    const PositionalArgument & argument = mPositionArguments.at(i);
    std::size_t width = argument.name.length();
    if (width > maxWidth) {
      maxWidth = width;
    }
  }

  // Add number of indent spaces at end of left column
  maxWidth += mIndent;
  return maxWidth;
}

std::string CommandLineParser::errorText() const
{
  return mErrorText;
}

const CommandLineOption * CommandLineParser::findOption(const std::string &name) const
{
  for (std::size_t i = 0; i < mOptions.size(); i++) {
    const CommandLineOption & option = mOptions.at(i);
    std::vector<std::string> optNames = option.names();
    for (std::size_t j = 0; j < optNames.size(); j++) {
      if (name == optNames.at(j)) {
        return &option;
      }
    }
  }

  return nullptr;
}

std::vector<std::string> CommandLineParser::formatArguments(const std::vector<std::string> &arguments) const
{
  std::vector<std::string> newArgs;
  for (std::size_t i = 0; i < arguments.size(); i++) {
    const std::string & arg = arguments.at(i);
    std::size_t index = arg.find_first_of("=");
    if (index != std::string::npos) {
      std::string arg1 = arg.substr(0, index);
      std::string arg2 = arg.substr(index+1);
      newArgs.push_back(arg1);
      newArgs.push_back(arg2);
    }
    else {
      newArgs.push_back(arg);
    }
  }
  return newArgs;
}

// TODO: Still need to handle line breaks
std::string CommandLineParser::helpText() const
{
  std::size_t width = computeHelpSpacing();

  std::ostringstream oss;
  oss << "Usage: " << mApplicationName;
  if (mOptions.size() > 0) {
    oss << " [options]";
  }

  for (std::size_t i = 0; i < mPositionArguments.size(); i++) {
    const PositionalArgument & argument = mPositionArguments.at(i);
    std::string text = argument.name;
    if (!argument.syntax.empty()) {
      text = argument.syntax;
    }
    oss << " " << text;
  }
  oss << "\n";

  oss << mApplicationDescription << "\n";
  oss << "\n";
  if (mOptions.size() > 0) {
    oss << "Options:\n";
    for (std::size_t i = 0; i < mOptions.size(); i++) {
      std::ostringstream ossOption;
      for (std::size_t j = 0; j < mIndent; j++) {
        ossOption << " ";
      }

      const CommandLineOption & option = mOptions.at(i);
      string_vector names = option.names();
      for (std::size_t j = 0; j < names.size(); j++) {
        const std::string & name = names.at(j);
        if (j > 0) {
          ossOption << ", ";
        }
        ossOption << "-";
        if (name.size() > 1) {
          ossOption << "-";
        }
        ossOption << names.at(j);
      }
      if (!option.valueName().empty()) {
        ossOption << " <" << option.valueName() << ">";
      }
      oss << std::left << std::setw(width) << ossOption.str();
      oss << option.description() << "\n";
    }
  }

  oss << "\n";
  oss << "Arguments:\n";
  for (std::size_t i = 0; i < mPositionArguments.size(); i++) {
    const PositionalArgument & argument = mPositionArguments.at(i);

    // Add indent
    std::ostringstream ossArg;
    for (std::size_t j = 0; j < mIndent; j++) {
      ossArg << " ";
    }

    ossArg << argument.name;

    oss << std::left << std::setw(width) << ossArg.str();
    oss << argument.description << "\n";
  }
  return oss.str();
}

void CommandLineParser::init(const std::string &applicationName)
{
  mApplicationName = applicationName;
  mLineBreakColumn = 79;
  mArgumentMode = ParseAsOptions;
  mDashMode = ParseAsCompactedShortOptions;
  mIndent = 2;
  mInPositional = false;
}

bool CommandLineParser::isSet(const std::string & name) const
{
  return (std::find(mOptionsSet.begin(), mOptionsSet.end(), name) != mOptionsSet.end());
}

bool CommandLineParser::isSet(const CommandLineOption & option) const
{
  const std::vector<std::string> names = option.names();
  for (std::size_t i = 0; i < names.size(); i++) {
    if (isSet(names.at(i))) {
      return true;
    }
  }
  return false;
}

int CommandLineParser::lineBreakColumn() const
{
  return mLineBreakColumn;
}

std::vector<std::string> CommandLineParser::optionNames() const
{
  return mOptionsSet;
}

bool CommandLineParser::parse(const std::vector<std::string> & arguments)
{
  mInPositional = false;
  mOptionsSet.clear();
  mPositionArgumentsSpecified.clear();
  mUnknownOptions.clear();
  mOptionValues.clear();

  // Format the arguments to remove any '=' signs
  std::vector<std::string> newArgs = formatArguments(arguments);

  bool positionalOverrideSpecified = false;
  for (std::size_t i = 1; i < newArgs.size(); i++) {
    std::string arg = newArgs.at(i);

    // Determine if we've hit an option
    bool isOption = (arg.at(0) == '-');
    bool isLongOption = (arg.size() > 1 && arg.at(1) == '-');

    // Single '-' values
    if (isOption && arg.size() == 1) {
      isOption = false;
      mInPositional = true;
    }

    // Determine if this is the positional override
    bool isPositionalOverride = (isLongOption && arg.size() == 2);
    if (isPositionalOverride) {

      // Can't specify the positional override twice
      if (positionalOverrideSpecified) {
        showHelp(EXIT_FAILURE);
      }
      positionalOverrideSpecified = true;
      continue;
    }

    // Determine if we are in the positional arguments
    if (!isOption) {
      mInPositional = true;
    }

    // Parse the argument
    bool parseAsPositional = (mArgumentMode == ParseAsPositionArguments);
    if (positionalOverrideSpecified || !isOption || (isOption && mInPositional && parseAsPositional)) {
      parsePositionalArgument(arg);
    }
    else {
      if (!parseOption(arg, i, newArgs, isLongOption)) {
        std::cout << mErrorText << "\n";
        return false;
      }
    }
  }

  return true;
}

bool CommandLineParser::parse(int argc, char **argv)
{
  std::vector<std::string> arguments;
  for (int i = 0; i < argc; i++) {
    std::string arg(argv[i]);
    arguments.push_back(arg);
  }
  return parse(arguments);
}

bool CommandLineParser::parseOption(const std::string &arg, std::size_t & index, const string_vector &arguments, bool isLong)
{
  std::string optionName = arg.substr(1);
  if (optionName.at(0) == '-') {
    optionName = optionName.substr(1);
  }

  std::vector<std::string> optionsToParse;
  if (isLong) {
    optionsToParse.push_back(optionName);
  }
  else {
    if (optionName.size() == 1) {
      optionsToParse.push_back(optionName);
    }
    else {
      if (mDashMode == ParseAsCompactedShortOptions) {
        for (std::size_t i = 0; i < optionName.size(); i++) {
          optionsToParse.push_back(optionName.substr(i,i+1));
        }
      }
      else { // ParseAsLongOptions
        std::string firstOptionName = optionName.substr(0,1);
        const CommandLineOption * option = findOption(firstOptionName);
        if (option == nullptr) {
          std::ostringstream oss;
          oss << "Unknown option '" << firstOptionName << "'.";
          mErrorText = oss.str();
          return false;
        }

        // Special exception
        if (option->flags() & CommandLineOption::ShortOptionStyle) {
          std::string value = optionName.substr(1);
          mOptionValues[firstOptionName].push_back(value);
          mOptionsSet.push_back(firstOptionName);
          ++index;
        }
        else {
          optionsToParse.push_back(optionName);
        }
      }
    }
  }

  for (std::size_t i = 0; i < optionsToParse.size(); i++) {
    const std::string & name = optionsToParse.at(i);
    const CommandLineOption * option = findOption(name);
    if (option == nullptr) {
      std::ostringstream oss;
      oss << "Unknown option '" << name << "'.";
      mErrorText = oss.str();
      return false;
    }

    if (!option->valueName().empty()) {
      if (index >= arguments.size()) {
        std::ostringstream oss;
        oss << "Missing value after '" << arg << "'.";
        mErrorText = oss.str();
        return false;
      }

      std::string argValue = arguments.at(index+1);
      mOptionValues[name].push_back(argValue);
      ++index;
    }

    mOptionsSet.push_back(name);
  }

  return true;
}

bool CommandLineParser::parsePositionalArgument(const std::string &arg)
{
  mPositionArgumentsSpecified.push_back(arg);
  return true;
}

std::vector<std::string> CommandLineParser::positionalArguments() const
{
  return mPositionArgumentsSpecified;
}

void CommandLineParser::process(std::vector<std::string> & arguments)
{
  if (!parse(arguments)) {
    std::exit(EXIT_FAILURE);
  }

  // Show the help and exit
  if (isSet(mHelpOption)) {
    showHelp();
  }

  // Show the version and exit
  if (isSet(mVersionOption)) {
    showVersion();
  }
}

void CommandLineParser::setApplicationDescription(const std::string & description)
{
  mApplicationDescription = description;
}

void CommandLineParser::setApplicationVersion(const std::string &version)
{
  mApplicationVersion = version;
}

void CommandLineParser::setOptionsAfterPositionArgumentsMode(OptionsAfterPositionalArgumentsMode parsingMode)
{
  mArgumentMode = parsingMode;
}

void CommandLineParser::setSingleDashWordOptionMode(SingleDashWordOptionMode singleDashWordOptionMode)
{
  mDashMode = singleDashWordOptionMode;
}

void CommandLineParser::showHelp(int exitCode)
{
  std::cout << helpText() << "\n";
  std::exit(exitCode);
}

void CommandLineParser::showVersion()
{
  std::cout << mApplicationVersion << "\n";
  std::exit(EXIT_SUCCESS);
}

std::vector<std::string> CommandLineParser::unknownOptionNames() const
{
  return mUnknownOptions;
}

std::string CommandLineParser::value(const std::string & optionName) const
{
  const CommandLineOption * option = findOption(optionName);
  if (option == nullptr)
    return std::string();

  return value(*option);
}

std::string CommandLineParser::value(const CommandLineOption & option) const
{
  // Determine if any of the names for this option were specified
  string_vector names = option.names();
  for (std::size_t i = 0; i < names.size(); i++) {
    const std::string & name = names.at(i);
    OptionValueMap::const_iterator itr = mOptionValues.find(name);
    if (itr != mOptionValues.end()) {
      return itr->second.at(0);
    }
  }

  if (option.defaultValues().size() > 0) {
    return option.defaultValues().at(0);
  }

  return std::string();
}

std::vector<std::string> CommandLineParser::values(const std::string & optionName) const
{
  const CommandLineOption * option = findOption(optionName);
  if (option == nullptr)
    return std::vector<std::string>();

  return values(*option);
}

std::vector<std::string> CommandLineParser::values(const CommandLineOption & option) const
{
  // Determine if any of the names for this option were specified
  string_vector names = option.names();
  for (std::size_t i = 0; i < names.size(); i++) {
    const std::string & name = names.at(i);
    OptionValueMap::const_iterator itr = mOptionValues.find(name);
    if (itr != mOptionValues.end()) {
      return itr->second;
    }
  }

  // If the option wasn't specified return the default values if available
  if (option.defaultValues().size() > 0) {
    return option.defaultValues();
  }

  return std::vector<std::string>();
}
