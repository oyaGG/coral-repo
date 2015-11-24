# Introduction #

In order to build the maya plugin you should first follow the coral-standalone build instructions:
[build\_coralStandalone](https://code.google.com/p/coral-repo/wiki/build_coralStandalone)


# Environment setup #

Setting up the environment for building the maya plugin involves adding the following variables to your buildEnv.py:

```
# buildEnv.py
import os

os.environ["CORAL_PYTHON_INCLUDES_PATH"] = "/Library/Frameworks/Python.framework/Versions/2.6/include/python2.6"
os.environ["CORAL_PYTHON_LIB"] = "python"
os.environ["CORAL_PYTHON_LIBS_PATH"] = "/Library/Frameworks/Python.framework/Versions/2.6"

os.environ["CORAL_BOOST_INCLUDES_PATH"] = "/dev/external/boost_1_46_1/boost"
os.environ["CORAL_BOOST_LIBS_PATH"] = "/dev/external/boost_1_46_1/stage/lib"
os.environ["CORAL_BOOST_PYTHON_LIB"] = "boost_python"

os.environ["CORAL_IMATH_INCLUDES_PATH"] = "/dev/external/ilmbase-1.0.1/include"
os.environ["CORAL_IMATH_LIBS_PATH"] = "/dev/external/ilmbase-1.0.1/libs"
os.environ["CORAL_IMATH_LIB"] = "Imath.6"
os.environ["CORAL_IMATH_IEX_LIB"] = "Iex.6"

os.environ["CORAL_TBB_INCLUDES_PATH"] = "/dev/external/tbb40_20110809oss/include"
os.environ["CORAL_TBB_LIBS_PATH"] = "/dev/external/tbb40_20110809oss/lib"
os.environ["CORAL_TBB_LIB"] = "tbb"

os.environ["CORAL_PARALLEL"] = "CORAL_PARALLEL_TBB"

# sdk setup
os.environ["CORAL_INCLUDES_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coral/includes"
os.environ["CORALUI_INCLUDES_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coralUi/includes"
os.environ["CORAL_LIBS_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coral/libs"
os.environ["CORALUI_LIBS_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coralUi/libs"

# maya config
if os.environ["CORAL_BUILD_FLAVOUR"] == "coralMaya":
    os.environ["CORAL_MAYA_INCLUDES_PATH"] = "pathToMayaDevkit/include"
    os.environ["CORAL_MAYA_LIBS_PATH"] = "pathToMayaDevkit/libs"
    
    os.environ["CORAL_PYTHON_LIB"] = "Python"
    os.environ["CORAL_PYTHON_INCLUDES_PATH"] = "pathToMayaPython/include/python2.6"
    os.environ["CORAL_PYTHON_LIBS_PATH"] = "pathToMayaPython/"
    
    os.environ["CORAL_PARALLEL"] = ""
```

# Building #
Open a terminal or a shell and cd ~/coralRepo.
Tell python where it can find buildEnv.py: export PYTHONPATH=$PYTHONPATH:"~/coralRepo"
Then finally build coralMaya: scons -f buildMayaPlugin.py

# Setting up the envs #
Before to start maya you'll have to configure your system environment variables so that it can find the required libraries, or copy those libraries in your system directories where they can be found automatically.
The libraries to be found are boost.python, tbb, Imath, and also _coral.so,_coralUi.so and Imath.so.

# Start coral in maya #
Once in maya open a script editor and run the following script:
```
from coralMaya import coralMayaApp
coralMayaApp.start()
coralMayaApp.showWindow()
```

