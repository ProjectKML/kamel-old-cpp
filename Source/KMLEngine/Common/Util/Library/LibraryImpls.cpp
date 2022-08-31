//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: LibraryImpls.cpp
//------------------------------------------------------------

//zpl
#define ZPL_IMPL
#include <zpl/zpl.h>

//fmt
#include <fmt/os.cc>
#include <fmt/format.cc>

//spdlog
#define SPDLOG_COMPILED_LIB
#include <spdlog/async.cpp>
#include <spdlog/cfg.cpp>
#include <spdlog/color_sinks.cpp>
#include <spdlog/file_sinks.cpp>
#include <spdlog/spdlog.cpp>
#include <spdlog/stdout_sinks.cpp>

//simdjson
#include <simdjson/simdjson.cpp>

//zip
#include <zip/zip.c>

//volk
#define VOLK_IMPLEMENTATION
#include <volk/volk.h>

//vk_mem_alloc
#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 1
#include <vk_mem_alloc/vk_mem_alloc.h>

//dear imgui
#ifdef VK_NO_PROTOTYPES
#undef VK_NO_PROTOTYPES //Prevent ImGui from exposing own vulkan function pointers
#endif

#include <imgui/imgui.cpp>
#include <imgui/imgui_demo.cpp>
#include <imgui/imgui_draw.cpp>
#include <imgui/imgui_tables.cpp>
#include <imgui/imgui_widgets.cpp>
#include <imgui/backends/imgui_impl_sdl.cpp>
#include <imgui/backends/imgui_impl_vulkan.cpp>
#include <imgui/misc/freetype/imgui_freetype.cpp>

//fast_obj
#include <fast_obj/fast_obj.c>

//meshoptimizer
#include <meshoptimizer/allocator.cpp>
#include <meshoptimizer/clusterizer.cpp>
#include <meshoptimizer/indexcodec.cpp>
#include <meshoptimizer/indexgenerator.cpp>
#include <meshoptimizer/overdrawanalyzer.cpp>
#include <meshoptimizer/overdrawoptimizer.cpp>
#include <meshoptimizer/simplifier.cpp>
#include <meshoptimizer/spatialorder.cpp>
#include <meshoptimizer/stripifier.cpp>
#include <meshoptimizer/vcacheanalyzer.cpp>
#include <meshoptimizer/vcacheoptimizer.cpp>
#include <meshoptimizer/vertexcodec.cpp>
#include <meshoptimizer/vertexfilter.cpp>
#include <meshoptimizer/vfetchanalyzer.cpp>
#include <meshoptimizer/vfetchoptimizer.cpp>

#ifdef KML_PLATFORM_MACOS
#include <memory_resource.cpp> //TODO: remove files from include dir and destroy this s**** when officially supported
#endif