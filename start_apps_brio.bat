@echo off
for %%F in ("x64\Debug\*.exe") do (
  start "" "%%F"
)