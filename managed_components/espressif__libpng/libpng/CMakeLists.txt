# CMakeLists.txt - CMake lists for libpng
#
# Copyright (c) 2018-2025 Cosmin Truta
# Copyright (c) 2007-2018 Glenn Randers-Pehrson
# Originally written by Christian Ehrlicher, 2007
#
# Use, modification and distribution are subject to
# the same licensing terms and conditions as libpng.
# Please see the copyright notice in png.h or visit
# http://libpng.org/pub/png/src/libpng-LICENSE.txt
#
# For copyright and licensing purposes, please see
# the accompanying file scripts/cmake/AUTHORS.md
#
# SPDX-License-Identifier: libpng-2.0

cmake_minimum_required(VERSION 3.14...4.0)

set(PNGLIB_MAJOR 1)
set(PNGLIB_MINOR 8)
set(PNGLIB_REVISION 0)
#set(PNGLIB_SUBREVISION 0)
set(PNGLIB_SUBREVISION "git")
set(PNGLIB_VERSION ${PNGLIB_MAJOR}.${PNGLIB_MINOR}.${PNGLIB_REVISION})
set(PNGLIB_ABI_VERSION ${PNGLIB_MAJOR}${PNGLIB_MINOR})
set(PNGLIB_SHARED_VERSION ${PNGLIB_ABI_VERSION}.${PNGLIB_REVISION}.${PNGLIB_SUBREVISION})


set(libpng_srcs
    png.c
    pngget.c
    pngrio.c
    pngwio.c
    pngwrite.c
    pngrtran.c
    pngrutil.c
    pngwtran.c
    pngwutil.c
    pngread.c
    pngset.c
    pngtrans.c
    pngerror.c
    pngmem.c
    pngpread.c
)

idf_component_register(
    SRCS "${libpng_srcs}"
    INCLUDE_DIRS "."
    REQUIRES 
        zlib
        mbedtls
    PRIV_REQUIRES 
        esp_timer
)
