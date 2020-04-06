workspace(name="mcl")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# GTest/GMock
http_archive(
    name="googletest",
    url="https://github.com/google/googletest/archive/release-1.8.0.zip",
    sha256="f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
    build_file="@//:third_party/googletest.BUILD",
    strip_prefix="googletest-release-1.8.0",
)

# YAML CPP
http_archive(
    name = "yaml-cpp",
    url = "https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-0.6.2.tar.gz",
    sha256 = "e4d8560e163c3d875fd5d9e5542b5fd5bec810febdcba61481fe5fc4e6b1fd05",
    build_file = "@//:third_party/yaml-cpp.BUILD",
    strip_prefix = "yaml-cpp-yaml-cpp-0.6.2",
)
