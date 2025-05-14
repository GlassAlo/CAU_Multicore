set_project("prob1")
set_project("prob2")

if is_os("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

set_languages("cxx23")
add_rules("mode.debug", "mode.release")

includes("prob1")
includes("prob2")
