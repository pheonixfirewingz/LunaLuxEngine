//
// Created by luket on 18/01/2020.
//

#ifndef LUNALUXENGINE_COMMON_HEADER_H
#define LUNALUXENGINE_COMMON_HEADER_H
#include <GLM/glm.hpp>
#include "types.h"
#ifdef WIN32
/*
 * The following #defines disable a bunch of unused windows stuff
 * removing some or all of these defines it will increase build time.
 */
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define STRICT
#endif
#endif //LUNALUXENGINE_COMMON_HEADER_H
