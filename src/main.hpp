#include <string>
#include <string_view>
#include <vector>


int command_execute(const std::string_view& subcommand,
                    const std::string& arguments,
                    const std::vector<std::string>& packages, 
                    const std::string& potential_error_cause,
                    bool packages_needed = true);

void log_error(const std::string& message); 

void log_debug(const std::string& message);

void log_info(const std::string& message);

std::string join_command_and_packages_and_ignore_packages(const std::string_view& command,
                                                          const std::string& subcommand, 
                                                          const std::vector<std::string>& packages, 
                                                          const std::vector<std::string>& ignore_packages);