mkdir %USERPROFILE%\bin\a2s
copy a2s.exe %USERPROFILE%\bin\a2s
copy *.dll %USERPROFILE%\bin\a2s
echo %%~dp0a2s\a2s.exe %%* > %USERPROFILE%\bin\a2s.cmd

