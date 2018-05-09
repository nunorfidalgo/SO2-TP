@echo off
for %%F in ("Debug\*.exe") do (
  start "" "%%F"
)