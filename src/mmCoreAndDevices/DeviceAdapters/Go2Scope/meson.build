# This Meson script is experimental and potentially incomplete. It is not part
# of the supported build system for Micro-Manager or mmCoreAndDevices.

project(
    'Go2Scope',
    'cpp',
    meson_version: '>=1.2.0',
    default_options: [
        'cpp_std=c++14',
        'warning_level=3',
    ],
)

boost_dep = dependency('boost')

acquire_zarr_proj = subproject('acquire-zarr')
zarr_include_dir = include_directories('include')
zarr_lib_dir = meson.current_source_dir() / 'lib'
# Declare dependencies for acquire-zarr
zarr_logger_dep = declare_dependency(
    include_directories: zarr_include_dir,
    link_with: static_library('acquire-logger', zarr_lib_dir / 'libacquire-logger.a'),
)
zarr_dep = declare_dependency(
    include_directories: zarr_include_dir,
    link_with: static_library('acquire-zarr', zarr_lib_dir / 'libacquire-zarr.a'),
)
# Expose these dependencies for the parent project
zarr_dependencies = [zarr_logger_dep, zarr_dep]


# MMDevice must be copied into subprojects/ for this experimental build to work
# (unless MMCore is itself being used as a subproject).
mmdevice_proj = subproject('MMDevice')
mmdevice_dep = mmdevice_proj.get_variable('mmdevice')

g2s_sources = files(
    'G2SStorage.cpp',
    'AcqZarrStorage.cpp',
    'G2SBigTiffStorage.cpp',
)

# Define the target (shared library)
library(
    'mmgr_dal_Go2Scope',
    sources: g2s_sources,
    dependencies: [mmdevice_dep, boost_dep, zarr_dependencies],
)