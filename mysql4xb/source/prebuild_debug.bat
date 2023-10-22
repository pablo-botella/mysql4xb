del mysql4xb.obj
del mysql4xb.def
del mysql4xbCpp.def
del mysql4xb_xbexports.hpp
del mysql4xb_xbfunclist.hpp
c:\util\VersionAutoIncrement.exe /noinc mysql4xb.VersionInfo > versioninfo.log
c:\util\xbmac2h.exe mysql4xb.xbmac
set errorlevel = 0
