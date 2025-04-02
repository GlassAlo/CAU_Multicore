set_project("problem1-static-block")
set_project("problem1-static-cyclic")
set_project("problem1-dynamic")
set_project("problem2")

if is_os("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

set_languages("cxx23")
add_rules("mode.debug", "mode.release")

includes("problem1")
includes("problem2")
