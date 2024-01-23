#!/bin/bash

bazel build //jaq:jaq
./bazel-bin/jaq/jaq "$@"
