package(default_visibility = ["//visibility:public"])

cc_library(
    name = "source_file",
    srcs = ["source_file.cc"],
    hdrs = ["source_file.h"],
    deps = [
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_binary(
    name = "jaq",
    srcs = ["jaq.cc"],
    deps = [
        ":source_file",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/status:statusor",
    ],
)
