

Guide to building coral - standalone on linux, win and mac.

# Dependencies #
This is the list of dependencies you'll need:
  * python (2.6 or 2.7)
  * scons (latest)
  * boost.python (1.46)
  * QT (4.5.3)
  * PyQt (latest)
  * intel TBB (4.0)
  * OpenEXR: ilmbase (1.0)
  * OpenImageIO (0.10)
  * GLEW (1.5.2+)
  * OpenCL (1.0)

# Getting coral's source code #
You can checkout the code following these instructions:
http://code.google.com/p/coral-repo/source/checkout

# Environment setup #
First off you'll need to create a file called buildEnv.py where we'll store some environment variables, this file could be placed anywhere, for convenience you can put it inside ~/coralRepo.

The content of this file is a series of environment variables that point to all the dependencies required by coral for compiling, here is an example of what it should look like on unix, use windows style paths if you are on windows:

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

os.environ["CORAL_OIIO_INCLUDES_PATH"] = "/dev/external/OpenImageIO-0.10/dist/linux64/include"
os.environ["CORAL_OIIO_LIBS_PATH"] = "/dev/external/OpenImageIO-0.10/dist/linux64/lib"
os.environ["CORAL_OIIO_LIB"] = "OpenImageIO"

os.environ["CORAL_TBB_INCLUDES_PATH"] = "/dev/external/tbb40_20110809oss/include"
os.environ["CORAL_TBB_LIBS_PATH"] = "/dev/external/tbb40_20110809oss/lib"
os.environ["CORAL_TBB_LIB"] = "tbb"

os.environ["CORAL_GLEW_INCLUDES_PATH"] = "/dev/external/glew-1.5.2/include/GL"
os.environ["CORAL_GLEW_LIBS_PATH"] = "/dev/external/glew-1.5.2/lib"
os.environ["CORAL_GLEW_LIB"] = "GLEW"

os.environ["CORAL_CL_INCLUDES_PATH"] = "/dev/external/AMD-APP-SDK-v2.5-RC2-lnx64/include"
os.environ["CORAL_CL_LIBS_PATH"] = "/dev/external/AMD-APP-SDK-v2.5-RC2-lnx64/lib/x86_64"
os.environ["CORAL_CL_LIB"] = "OpenCL"

os.environ["CORAL_PARALLEL"] = "CORAL_PARALLEL_TBB"

# sdk setup
os.environ["CORAL_INCLUDES_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coral/includes"
os.environ["CORALUI_INCLUDES_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coralUi/includes"
os.environ["CORAL_LIBS_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coral/libs"
os.environ["CORALUI_LIBS_PATH"] = "~/coralRepo/build/coralStandaloneBuild/sdk/coralUi/libs"

```

# Building #
If you've made it this far you are a hero, now onto the actual building.

Open a terminal or a shell go trough your local repository:
```
cd ~/coralRepo.
```

Tell python where it can find buildEnv.py:
```
export PYTHONPATH=$PYTHONPATH:"~/coralRepo"
```

Finally build coral standalone:
```
scons -f buildStandalone.py build-sdk=1
```

# Setting up the envs #
Before to start coral-standalone you'll have to configure your system environment variables so that it can find the required libraries, or copy those libraries in your system directories where they can be found automatically.
The libraries to be found are boost.python, tbb, Imath, and also _coral.so,_coralUi.so and Imath.so.

## Linux ##
If you have an error message like:
```
ImportError: libOpenCL.so.1: cannot open shared object file: No such file or directory
```
It's because your environment is not well defined and it can not find libraries.

In that case, define library path like this should solve the problem:
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"/dev/external/AMD-APP-SDK-v2.5-RC2-lnx64/lib/x86_64"
```

# Launching coral-standalone #
After the build is done you'll find a new directory ~/coralRepo/build/coralStandaloneBuild, cd in there and type:
python launchApp.py