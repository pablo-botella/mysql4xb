echo on 
echo ---------------------------------------------------***************************** 1
echo postbuild:
echo %~f0  %1  %2
echo ---------------------------------------------------***************************** 2

echo copy %1mysql4xb.def  %2mysql4xb.def
copy %1mysql4xb.def  %2mysql4xb.def
copy %1__mklib.bat  %2__mklib.bat


rem del %2mysql4xb.lib


%~d2
CD %~dp2         
echo C:\Alaska\XPPW32\bin\aimplib.exe  mysql4xb.def   /omysql4xb.lib
C:\Alaska\XPPW32\bin\aimplib.exe  mysql4xb.def   /omysql4xb.lib
           

%~d1
CD %~dp1

echo ---------------------------------------------------***************************** 3

                                      
@echo ---------------------------------------- 4

@echo ---------------------------------------- 5
IF EXIST C:\pli\mysql4xb  copy %2mysql4xb.dll        C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %2mysql4xb.dll        C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %2mysql4xbcpp.lib     C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %2mysql4xb.lib        C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %1ch\*.ch          C:\pli\mysql4xb\   


@echo ---------------------------------------- 6

IF EXIST c:\util\mysql4xb-deploy-release.bat echo  c:\util\mysql4xb-deploy-release.bat   %1  %2
IF EXIST c:\util\mysql4xb-deploy-release.bat call c:\util\mysql4xb-deploy-release.bat   %1  %2

@echo ---------------------------------------- 7

IF EXIST __mk_package.bat call __mk_package.bat  %1  %2

@echo ---------------------------------------- 8

IF EXIST  versioninfo.log  type versioninfo.log
IF EXIST  versioninfo.log  del  versioninfo.log

@echo ---------------------------------------- 9
