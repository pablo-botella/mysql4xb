rd mysql4xb_bin /s /q
md mysql4xb_bin
rd mysql4xb_source  /s /q
md mysql4xb_source

7z x _mysql4xb_001_000_008_000.zip  -o.\mysql4xb_bin
7z x _mysql4xb_001_000_008_000_source.zip  -o.\mysql4xb_source

if exist "c:\util\mysql4xb_autodeploy.bat" ( 
call "c:\util\mysql4xb_autodeploy.bat"  %~dp0mysql4xb_bin\  
) else (
cls                        
@echo '
@echo '
@echo '
@echo '
@echo '  - --------------------------------------------------------------------
@echo '  -   CREATE THE BATCH FILE "c:\util\mysql4xb_autodeploy.bat"             -
@echo '  -   THAT WILL BE CALLED WITH THE FULL PATH OF mysql4xb_BIN AS PARAMETER -
@echo '  -   SO YOU CAN CUSTOMIZE THE DEPLOYMENT ACORDING YOUR ENVIRONMENT    -
@echo '  - --------------------------------------------------------------------
@echo '
@echo '
@echo '
pause
)    



