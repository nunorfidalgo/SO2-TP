@echo off
echo Iniciar Jogo (Servidor&Gateway)


set arg1=%1
set arg2=%2
shift
shift
fake-command /u %arg1% /p %arg2% %*

REM
REM for %%F in ("Debug\*.exe") do (
REM  start "" "%%F"
REM )
REM