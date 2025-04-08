set_project("pc_static_block")
set_project("pc_static_cyclic")
set_project("pc_dynamic")
set_project("MatmultD")

if is_os("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

set_languages("cxx23")
add_rules("mode.debug", "mode.release")

includes("src")
