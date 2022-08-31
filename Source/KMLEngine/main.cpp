//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: main.cpp
//------------------------------------------------------------

#include "Common/Util/STL/pmr_new.hpp"
#include "Client/Game.hpp"

using namespace KMLEngine;

template<typename T, typename... Arguments>
KML_FORCEINLINE void Run(Arguments&&... arguments) noexcept {
    auto* instance = kml_stl::pmr_new<T>(std::pmr::new_delete_resource(), std::forward<Arguments>(arguments)...);
    kml_stl::pmr_delete(std::pmr::new_delete_resource(), instance);
}

KML_FORCEINLINE int ReturnArguments(zpl_opts& options, const char* name, int result) noexcept {
    zpl_printf("[KMLEngine] %s:\n", name);

    if (result) zpl_opts_print_errors(&options);
    zpl_opts_print_help(&options);

    return result;
}

KML_FORCEINLINE void AddOptions(zpl_opts& options) noexcept {
    //Common
    zpl_opts_add(&options, nullptr, "help", "Lists all available options", ZPL_OPTS_FLAG);
    zpl_opts_add(&options, "c", "client", "Runs the client", ZPL_OPTS_FLAG);
    zpl_opts_add(&options, "s", "server", "Runs the server", ZPL_OPTS_FLAG);
    zpl_opts_add(&options, "lf", "log-to-file", "Option to enable logging to file", ZPL_OPTS_FLAG);

    //Client
    zpl_opts_add(&options, "w", "width", "The window width", ZPL_OPTS_INT);
    zpl_opts_add(&options, "h", "height", "The window height", ZPL_OPTS_INT);
    zpl_opts_add(&options, "f", "fullscreen", "The window fullscreen mode", ZPL_OPTS_FLAG);
    zpl_opts_add(&options, "fl", "frame-limit", "The frame limit", ZPL_OPTS_INT);

    //Server
    //TODO:
}

i32 main(i32 numArguments, char** arguments) {
    zpl_opts options = {};
    zpl_opts_init(&options, zpl_heap(), "KMLEngine");

    AddOptions(options);

    if(const auto result = zpl_opts_compile(&options, numArguments, arguments); !result || !zpl_opts_positionals_filled(&options)) return ReturnArguments(options, "Invalid options", 1);
    if(zpl_opts_has_arg(&options, "help")) return ReturnArguments(options, "Available options", 0);

    const auto isServer = zpl_opts_has_arg(&options, "server");
    if(isServer && zpl_opts_has_arg(&options, "client")) return ReturnArguments(options, "Only either the client or the server can be started", 1);

    
    if(isServer) {
        //TODO: start server
    }
    else Run<Game>(options);
    
    zpl_opts_free(&options);
    
    return 0;
}