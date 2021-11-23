## Haiku Generic Makefile v2.6 ##


NAME = Peggy
TYPE = APP
APP_MIME_SIG = application/x-vnd.BlueSky-Peggy

#%{
# @src->@
SRCS = \
	 src/gamecontroller.cpp  \
	 src/gamerow.cpp  \
	 src/app.cpp  \
	 src/boardview.cpp  \
	 src/buttonview.cpp  \
	 src/mainwindow.cpp  \
	 src/peg.cpp  \
	 src/pegselectview.cpp  \

RDEFS = \
	 Peggy.rdef  \


RSRC = \

# @<-src@
#%}

#%}

#%}

#%}

#%}

#%}

#%}

#%}

#%}

#%}

#%}

#%}

#%}

LIBS = $(STDCPPLIBS) be root localestub tracker
LIBPATHS =
SYSTEM_INCLUDE_PATHS = /boot/system/develop/headers/private/interface
LOCAL_INCLUDE_PATHS =
OPTIMIZE :=
LOCALES = en
DEFINES=
WARNINGS = ALL
SYMBOLS :=
DEBUGGER :=
COMPILER_FLAGS = -std=c++11
LINKER_FLAGS =
APP_VERSION :=

DEVEL_DIRECTORY := \
	$(shell findpaths -r "makefile_engine" B_FIND_PATH_DEVELOP_DIRECTORY)
include $(DEVEL_DIRECTORY)/etc/makefile-engine
