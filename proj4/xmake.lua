set_project("openmp_ray")
set_project("cuda_ray")

if is_os("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

set_languages("cxx23")
add_rules("mode.debug", "mode.release")

includes("problem1")
includes("problem2")
