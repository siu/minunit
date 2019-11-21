@echo off
set expected_exit_code=6
minunit_example
IF NOT %errorlevel% == %expected_exit_code% (
  echo Unexpected exit code: %expected_exit_code% expected but was %errorlevel%
  exit /B 1
)
exit /B 0