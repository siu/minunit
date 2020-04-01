#!/usr/bin/env bash
expected_exit_code=18
./minunit_example
ret="$?"
if [ "$ret" -ne $expected_exit_code ]; then
  echo "Unexpected exit code: $expected_exit_code expected but was $ret"
  exit 1
fi
exit 0
