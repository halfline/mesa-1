# Copyright © 2013 Intel Corporation
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

SUBDIRS = gtest util mapi/glapi/gen mapi

if NEED_OPENGL_COMMON
SUBDIRS += glsl mesa
endif

SUBDIRS += loader

if HAVE_DRI_GLX
SUBDIRS += glx
endif

if HAVE_EGL_PLATFORM_WAYLAND
SUBDIRS += egl/wayland/wayland-egl egl/wayland/wayland-drm
endif

if HAVE_EGL_DRIVER_DRI2
SUBDIRS += egl/drivers/dri2
endif

if HAVE_GBM
SUBDIRS += gbm
endif

if HAVE_EGL
SUBDIRS += egl/main
endif

if HAVE_GALLIUM
SUBDIRS += gallium
endif

EXTRA_DIST = egl/docs getopt hgl SConscript
