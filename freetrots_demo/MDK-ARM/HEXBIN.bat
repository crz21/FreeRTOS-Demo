
@echo off


if not exist HEXBIN_output (
	mkdir HEXBIN_output
)
set exe_location=%1ARM\ARMCC\bin\fromelf.exe
set obj_location=%2
set project_name=%3
set obj_path=%4
set output_name=%project_name%
%exe_location% --bin -o .\HEXBIN_output\%output_name%.bin %obj_location% >nul
ren %obj_path%%project_name%.hex %output_name%.hex >nul
move %obj_path%%output_name%.hex .\HEXBIN_output >nul

