#include "jaq/source_file.h"

#include <fstream>
#include <string_view>

#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"

absl::StatusOr<std::unique_ptr<SourceFile>> SourceFile::FromFilename(
    const std::string& filename) {
  std::ifstream t(filename);
  if (!t.is_open()) {
    return absl::NotFoundError(
        absl::StrFormat("Could not find file: %s", filename));
  }
  std::stringstream buffer;
  buffer << t.rdbuf();
  return std::make_unique<SourceFile>(buffer.str());
}

std::string SourceFile::TokenInLineContext(int position, int length) const {
  const int line_start = LineStart(position);
  const int col = position - line_start;

  std::stringstream ss;
  ss << Line(line_start) << "\n";
  ss << std::string(col, ' ') << std::string(length, '^') << "\n";
  return ss.str();
}

int SourceFile::LineStart(int position) const {
  for (int i = position - 1; i > 0; --i) {
    if (source_code_[i] == '\n') {
      return i + 1;
    }
  }
  return 0;
}

std::string_view SourceFile::Line(int start) const {
  int length = 0;
  for (; start + length < source_code_.length() &&
         source_code_[start + length] != '\n';
       ++length) {
  }
  return std::string_view(source_code_.data() + start, std::max(0, length - 1));
}