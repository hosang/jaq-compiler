#ifndef JAQ_SOURCE_FILE_H
#define JAQ_SOURCE_FILE_H

#include <sstream>
#include <string>
#include <string_view>

#include "absl/status/statusor.h"

class SourceFile {
 public:
  static absl::StatusOr<std::unique_ptr<SourceFile>> FromFilename(
      const std::string& filename);
  SourceFile(std::string source_code) : source_code_(std::move(source_code)) {}

  // Not copyable, so we don't copy it on accident.
  SourceFile& operator=(const SourceFile&) = delete;
  SourceFile(const SourceFile&) = delete;
  SourceFile() = delete;

  std::string_view source_code() const { return source_code_; }
  std::string TokenInLineContext(int position, int length) const;

 private:
  std::string source_code_;

  int LineStart(int position) const;
  std::string_view Line(int start) const;
};

class ErrorBuilder {
 public:
  ErrorBuilder() : str_builder_() {}

  ErrorBuilder& operator<<(std::string_view str) {
    str_builder_ << str << "\n";
    return *this;
  }

 private:
  std::stringstream str_builder_;
};

#endif