
echo ---------    %0
echo %1
echo %2
echo ----------------------  
set "path=c:\util;%path%"
md %2builds
md %2builds\_mysql4xb_001_000_006_000

md %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
md %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000\include
md %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source
md %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
md %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source\ch

copy %2mysql4xb.dll  %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
copy %2mysql4xb.lib  %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
copy %2mysql4xb_cpp.lib  %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
copy %1*.txt %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
copy %1ch\*.ch  %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000\include

copy %1mysql4xb_extract_all.bat  %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_deploy.bat

%~d2
cd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
7za.exe a -y  ..\_mysql4xb_001_000_006_000.zip  *
%~d1
cd %~dp1

copy %1..\mysql4xb.sln %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source
copy %1ch\*.ch  %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source\ch
copy %1*.rc %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.txt %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.h %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.hpp %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.c %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.cpp %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.def %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.xbmac %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.versioninfo %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1*.bat %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
del %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source\BAT??????????????.bat
copy %1mysql4xb.vcproj %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
copy %1mysql4xb.vcxproj %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
%~d2
cd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source
7za.exe a -y  ..\_mysql4xb_001_000_006_000_source.zip   *

%~d1
cd %~dp1


if exist %2builds\SKIP_REMOVE_FILES.TXT goto SKIP_REMOVE_FILES
del %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000\*.* /q
del %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000\include\*.* /q
del %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\*.* /q
del %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source\*.* /q
del %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source\ch\*.* /q

rd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000\include
rd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source\ch
rd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source\source
rd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000_source
rd %2builds\_mysql4xb_001_000_006_000\_mysql4xb_001_000_006_000
rd %2builds\_mysql4xb_001_000_006_000
:SKIP_REMOVE_FILES

