
echo on 
echo ---------------------------------------------------*****************************
echo postbuild:
echo %~f0  %1  %2
echo ---------------------------------------------------*****************************

echo copy %1mysql4xb.def  %2mysql4xb.def
copy %1mysql4xb.def  %2mysql4xb.def
copy %1__mklib.bat  %2__mklib.bat
del %2mysql4xb.lib


echo ---------------------------------------------------*****************************


%~d2
CD %~dp2         
echo %~d2
echo %~dp2
C:\Alaska\XPPW32\bin\aimplib.exe
C:\Alaska\XPPW32\bin\aimplib.exe
C:\Alaska\XPPW32\bin\aimplib.exe  mysql4xb.def   /omysql4xb.lib 

%~d1
CD %~dp1




echo ---------------------------------------------------*****************************

                                      
@echo ----------------------------------------

@echo ----------------------------------------
IF EXIST C:\pli\mysql4xb  copy %2mysql4xb.dll        C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %2mysql4xb.dll        C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %2mysql4xbcpp.lib     C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %2mysql4xb.lib        C:\pli\mysql4xb\   
IF EXIST C:\pli\mysql4xb  copy %1ch\*.ch          C:\pli\mysql4xb\   



@echo ----------------------------------------

IF EXIST c:\util\mysql4xb-deploy-debug.bat call c:\util\mysql4xb-deploy-debug.bat   %1  %2

@echo ----------------------------------------

IF EXIST  versioninfo.log  type versioninfo.log
IF EXIST  versioninfo.log  del  versioninfo.log

@echo ----------------------------------------
