
@echo off

set header_folder=..\third_party

set pluto_src_folder=..\include
set pluto_dst_folder=%header_folder%



set charon_src_folder=..\module\charon\include
set charon_dst_folder=%header_folder%\charon

if not exist %pluto_dst_folder% (
	md %pluto_dst_folder%
)

COPY /Y %pluto_src_folder%\* %pluto_dst_folder%




if not exist %charon_dst_folder% (
	md %charon_dst_folder%
)

COPY /Y %charon_src_folder%\* %charon_dst_folder%

pause