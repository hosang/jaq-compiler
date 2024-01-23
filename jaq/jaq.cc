#include <fstream>
#include <iostream>
#include <sstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/status/statusor.h"
#include "jaq/source_file.h"

ABSL_FLAG(std::string, file, "main.jaq", "File containting main().");

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);

  auto source_file_or = SourceFile::FromFilename(absl::GetFlag(FLAGS_file));
  if (!source_file_or.ok()) {
    std::cout << "ERROR: " << source_file_or.status();
    return 1;
  }

  std::cout << "hello world\n";
  std::cout << (*source_file_or)->TokenInLineContext(5, 2);
}