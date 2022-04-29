// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cassert>
#include <cstddef>
#include <memory>

#include "mpl.h"

// You should define a file ../game/ecs_defs.h with the list of
// your components, groups, and handlers. See ecs_defs_example.h
// for an example
//
// the following includes your ../game/ecs_defs.h, it is valid
// from c++17, it won't compile with older versions. If you are
// using an older version replace the #if #else and #endif
//
#if __has_include("../game/ecs_defs.h")
#include "../game/ecs_defs.h"
#else
#endif

#ifndef  _CMPS_LIST_
struct ___DummyComponent____;
#define _CMPS_LIST_ ___DummyComponent____
#endif

#ifndef  _GRPS_LIST_
struct ___DummyGroup____;
#define _GRPS_LIST_ ___DummyGroup____
#endif

#ifndef  _HDLRS_LIST_
struct ___DummyHandler____;
#define _HDLRS_LIST_ ___DummyHandler____
#endif

#ifndef  _SYS_LIST_
struct ___DummySystem____;
#define _SYS_LIST_ ___DummySystem____
#endif




namespace ecs {

using ComponentsList = mpl::TypeList<_CMPS_LIST_>;
using GroupsList = mpl::TypeList<_GRPS_LIST_>;
using HdlrsList = mpl::TypeList<_HDLRS_LIST_>;
using SysList = mpl::TypeList<_SYS_LIST_>;


template<typename T>
constexpr std::size_t cmpIdx = mpl::IndexOf<T, ComponentsList>();

template<typename T>
constexpr std::size_t grpIdx = mpl::IndexOf<T, GroupsList>();

template<typename T>
constexpr std::size_t hdlrIdx = mpl::IndexOf<T, HdlrsList>();

template<typename T>
constexpr std::size_t sysIdx = mpl::IndexOf<T, SysList>();


constexpr std::size_t maxComponent = ComponentsList::size;
constexpr std::size_t maxGroup = GroupsList::size;
constexpr std::size_t maxHdlr = HdlrsList::size;
constexpr std::size_t maxSystem = SysList::size;

}

