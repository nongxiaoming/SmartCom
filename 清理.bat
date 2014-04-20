attrib -h -s -r *.*
del /Q CometBrowser\Release\*.*
del /Q CometBrowser\Debug\*.*
del /Q Debug\*.*
del /Q release\*.pdb
del /Q CometBrowser\*.user
del /Q *.suo
del /Q *.ncb
RD  debug
RD  CometBrowser\Release
RD  CometBrowser\debug