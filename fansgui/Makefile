#
# Copyright 2019 Saso Kiselkov
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

include ../Makefile.vars
include ../Makefile.com

CFLAGS += -W -Wall -Wextra -Werror -Wno-unused-result -O2 -g -DDEBUG \
	$(PLATFORM_DEFS) -D_GNU_SOURCE -I$(SRCPREFIX) -I$(ACFUTILS)/src \
	$(shell $(ACFUTILS)/pkg-config-deps $(PLATFORM_NAME) --glfw --cflags) \
	$(shell pkg-config gnutls --cflags)
LIBS += -L$(ACFUTILS)/qmake/$(PLATFORM_LIBNAME) -lacfutils \
	$(shell $(ACFUTILS)/pkg-config-deps $(PLATFORM_NAME) --glfw --libs) \
	$(shell pkg-config gnutls --libs) \
	-lGL -lX11 -ldl -lpthread -lm

OBJS = \
	mtcr_mini.o \
	fansgui.o \
	$(CORE_SRC_OBJS) \
	$(FANS_OBJS)

all : fansgui

fansgui : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean :
	rm -f fansgui $(OBJS)