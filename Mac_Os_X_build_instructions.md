

These instructions cover how to install the dependencies and compile coral-standalone and coral-maya, the steps are the same for Snow Leopard and Lion.

## Installing the dependencies ##

### python 2.7 64 bit ###
Download from: http://www.python.org/ftp/python/2.6.7/Python-2.6.7.tar.bz2

Uncompress and cd inside the newly created folder from a terminal, then type:
```
./configure --enable-framework=/Library/frameworks --enable-universalsdk=/ --with-universal-archs=intel
make
sudo make install
```

Make sure you have a 64 bit python by opening a terminal and typing this:
```
python

import struct;print( 8 * struct.calcsize("P"))
```

Now that you have your python installed, we need to symlink some files for it to be properly setup:
```
cd /Library/Frameworks/Python.framework/Versions/2.6/
sudo ln -s Python libpython2_6_7.dylib
cd /Library/Frameworks/Python.framework/Versions/2.6/bin
sudo ln -sf python2.6-64 python
sudo ln -sf python2.6-64 python2.6
sudo ln -sf pythonw2.6-64 pythonw
sudo ln -sf python2.6-64 pythonw2.6
```

Note that from now on we'll specify this python version pretty much everywhere, mixing up different python versions is usually the main cause of major disasters during this process.

### boost 1.47 ###
Boost is mostly a headers-only toolkit, but in order to use its python wrapper functionalities we'll need to build the boost.python part.

Download from: http://sourceforge.net/projects/boost/files/boost/1.47.0/boost_1_47_0.tar.gz/download

Uncompress and cd inside the newly created folder from a terminal, then type:
```
./bootstrap.sh --with-libraries=python --with-python=/Library/Frameworks/Python.framework/Versions/2.6/bin/python
./bjam
```

Now you should see libboost\_python.dylib inside yourBoostFolder/stage/lib.
There's no need to install it, just place yourBoostFolder wherever you like, we'll specify the path to this folder later in order to compile coral.

### build ilmbase 1.0.1 ###
We need this library to use Imath, which is the main math library used in coral.

Download from: http://download.savannah.nongnu.org/releases/openexr/ilmbase-1.0.1.tar.gz

Uncompress and cd inside the newly created folder from a terminal, then type:
```
./configure
```

Now because of an incompatibility issue with Os X, we need to perform some changes to the makefiles.

Use grep from your ilmbase folder to find this flag "-Wno-long-double":
```
grep -r Wno *
```

For each Makefile found (ignore the other config files found), open it and delete -Wno-long-double then save.

Once we've done that for all the makefiles just type:
```
make
sudo make install
```

### Qt 4.7.4 ###
Download from: http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.4.tar.gz

Uncompress and cd inside the newly created folder from a terminal, then type:
```
./configure
make
sudo make install
```

### Sip latest ###
We need this library to build PyQt.

Download from: http://www.riverbankcomputing.co.uk/software/sip/download (Linux, UNIX, MacOS/X source)

Uncompress and cd inside the newly created folder from a terminal, then type:
```
/Library/Frameworks/Python.framework/Versions/2.6/bin/python configure.py
make
sudo make install
```

### PyQt latest ###
Download from: http://www.riverbankcomputing.co.uk/software/pyqt/download (MacOS/X source)

Uncompress and cd inside the newly created folder from a terminal, then type:
```
/Library/Frameworks/Python.framework/Versions/2.6/bin/python configure.py -d /Library/Frameworks/Python.framework/Versions/2.6/lib/python2.6/site-packages -q /usr/local/Trolltech/Qt-4.7.4/bin/qmake
make
sudo make install
```

### GLEW ###
Downaload from: http://sourceforge.net/projects/glew/files/glew/1.7.0/glew-1.7.0.tgz/download

Uncompress and cd inside the newly created folder from a terminal, then type:
```
make
```

### TBB ###
Download from: http://threadingbuildingblocks.org/uploads/77/177/4.0%20update%201/tbb40_20111003oss_mac.tgz
Uncompress and enjoy the pre-built binaries for once!

## Building coral-standalone ##
In order to build coral we first need to set some environment variables, we'll do so from a special python file which is automatically imported by coral's build system.
Create a buildEnv.py file and place it wherever you like.

The content of buildEnv.py should be as follows (replace with your own paths where appropriate):
```
import os

os.environ["CORAL_PARALLEL"] = "CORAL_PARALLEL_TBB"

os.environ["CORAL_PYTHON_PATH"] = "/Library/Frameworks/Python.framework/Versions/2.6"
os.environ["CORAL_PYTHON_INCLUDES_PATH"] = "/Library/Frameworks/Python.framework/Versions/2.6/include/python2.6"
os.environ["CORAL_PYTHON_LIB"] = "python2_6_7"
os.environ["CORAL_PYTHON_LIBS_PATH"] = "/Library/Frameworks/Python.framework/Versions/2.6"

os.environ["CORAL_BOOST_INCLUDES_PATH"] = "/yourPathToBoost"
os.environ["CORAL_BOOST_LIBS_PATH"] = "/yourPathToBoost/stage/lib"
os.environ["CORAL_BOOST_PYTHON_LIB"] = "boost_python"

os.environ["CORAL_IMATH_INCLUDES_PATH"] = "/usr/local/include/OpenEXR"
os.environ["CORAL_IMATH_LIBS_PATH"] = "/usr/local/lib"
os.environ["CORAL_IMATH_LIB"] = "Imath"
os.environ["CORAL_IMATH_IEX_LIB"] = "Iex"

os.environ["CORAL_TBB_INCLUDES_PATH"] = "/yourPathToIntelTBB/include"
os.environ["CORAL_TBB_LIBS_PATH"] = "/yourPathToIntelTBB/lib"
os.environ["CORAL_TBB_LIB"] = "tbb"
os.environ["CORAL_CL_INCLUDES_PATH"] = "/yourPathToCLHPP"

os.environ["CORAL_GLEW_INCLUDES_PATH"] = "/yourPathToGLEW/include"
os.environ["CORAL_GLEW_LIBS_PATH"] = "/yourPathToGLEW/lib"
os.environ["CORAL_GLEW_LIB"] = "GLEW"
```

You can now build coral-standalone, cd in coral's folder (where you see buildStandalone.py) and type:
```
export PYTHONPATH=$PYTHONPATH:"/yourPathToBuildEnv"
/usr/local/bin/scons -f "buildStandalone.py"
```

If you want to build the sdk then type the following:
```
/usr/local/bin/scons -f "buildStandalone.py" build-sdk=1
```

### start coral-standalone ###
To start coral-standalone cd onto the coral's build dir coral/build/coralStandaloneBuild, then type the following commands,
or create a bash script:
```
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/yourPathToIntelTBB/lib"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/yourPathToBoost/stage/lib"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"yourPathToCoral/coral/build/coralStandaloneBuild/coral"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"yourPathToCoral/coral/build/coralStandaloneBuild/coral"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"yourPathToCoral/coral/build/coralStandaloneBuild/coral/coralUi"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/Library/Frameworks/Python.framework/Versions/2.6"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/System/Library/Frameworks/OpenGL.framework/Versions/A"

/Library/Frameworks/Python.framework/Versions/2.6/bin/python2.6 launchApp.py
```

### using coral's SDK ###
In order to use coral's sdk to compile your own nodes you'll need to specify the following envs in buildEnv.py (and build coral with the build-sdk=1 flag):
```
os.environ["CORAL_INCLUDES_PATH"] = "/yourPathToCoral/coral/build/coralStandaloneBuild/sdk/coral/includes"
os.environ["CORALUI_INCLUDES_PATH"] = "/yourPathToCoral/coral/build/coralStandaloneBuild/sdk/coralUi/includes"
os.environ["CORAL_LIBS_PATH"] = "/yourPathToCoral/coral/build/coralStandaloneBuild/sdk/coral/libs"
os.environ["CORALUI_LIBS_PATH"] = "/yourPathToCoral/coral/build/coralStandaloneBuild/sdk/coralUi/libs"
```

Have a look in the examples folder to check some example nodes.

## build coral-maya ##

First off it's better if we create an alias of maya's python lib, gcc on Os X can be annoying and pickup the first lib it finds.
So just type the following commands from a terminal:
```
cd /Applications/Autodesk/maya2012/Maya.app/Contents/Frameworks/Python.framework/Versions/2.6
sudo ln -s Python libpython_maya.dylib
```

To build coral-maya add the following envs to your buildEnv.py:
```
if os.environ.has_key("CORAL_BUILD_FLAVOUR"):
    if os.environ["CORAL_BUILD_FLAVOUR"] == "coralMaya":
        os.environ["CORAL_MAYA_INCLUDES_PATH"] = "/Applications/Autodesk/maya2012/devkit/include"
        os.environ["CORAL_MAYA_LIBS_PATH"] = "/Applications/Autodesk/maya2012/Maya.app/Contents/MacOS/"
    
        os.environ["CORAL_PYTHON_LIB"] = "python_maya"
        os.environ["CORAL_PYTHON_INCLUDES_PATH"] = "/Applications/Autodesk/maya2012/Maya.app/Contents/Frameworks/Python.framework/Versions/2.6/include/python2.6"
        os.environ["CORAL_PYTHON_LIBS_PATH"] = "/Applications/Autodesk/maya2012/Maya.app/Contents/Frameworks/Python.framework/Versions/2.6"

        os.environ["CORAL_PARALLEL"] = ""
```

Then use the builder:
```
export PYTHONPATH=$PYTHONPATH:"/yourPathToBuildEnv"
/usr/local/bin/scons -f "buildMayaPlugin.py"
```

Note that in order to use coral's UI from maya you'll need to install PyQt for maya:
http://images.autodesk.com/adsk/files/pyqtmaya2011.pdf
or use one these amazing auto-installers: http://www.justinfx.com/2011/11/09/installing-pyqt4-for-maya-2012-osx/

## launch coral-maya ##
We need to start maya from a terminal after we've setup the right evironment variables, you can also create a bash script to do this:
```
export PYTHONPATH=$PYTHONPATH:"/yourPathToCoral/coral/build/coralMayaBuild"
export DYLD_LIBRARY_PATH="/yourPathToBoost/stage/lib"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/yourPathToIntelTBB/lib"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/yourPathToCoral/coral/build/coralMayaBuild/coralMaya"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/yourPathToCoral/coral/build/coralMayaBuild/coral"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/yourPathToCoral/coral/build/coralMayaBuild/coral/coralUi"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/Applications/Autodesk/maya2012/Maya.app/Contents/Frameworks/Python.framework/Versions/2.6"
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:"/Applications/Autodesk/maya2012/Maya.app/Contents/MacOS"

/Applications/Autodesk/maya2012/Maya.app/Contents/bin/maya
```