project(
    'pymmcore-nano',
'cpp',
    version: '0.0.1',
    meson_version: '>= 1.6.0',
    default_options: ['cpp_std=c++17'],
)
py = import('python').find_installation()
nanobind_dep = dependency('nanobind', static: true)


# ---------- patch c++14 to c++17 ----------

patch_script = files('patch_c14_c17.py')

# List of files to patch
patched_files = [
    'extern/mmCoreAndDevices/MMCore/Configuration.h',
    'extern/mmCoreAndDevices/MMCore/MMCore.h'
]

# Patch the files during the configure step
foreach file : patched_files
    run_command(py.full_path(), patch_script[0], file)
endforeach

py.extension_module(
    '_pymmcore_nano',
    sources: ['src/_pymmcore_nano.cc'],
    dependencies: [nanobind_dep],
    include_directories: ['extern/mmCoreAndDevices/MMCore', '.'],
    install: true,
)

# install the Python package into the site-packages directory
install_subdir('src/pymmcore_nano', install_dir: py.get_install_dir() / 'pymmcore_nano', strip_directory: true)

test('test_script',
    py,
    args: ['-m', 'pytest', '--color=yes', '-v'],
    workdir: meson.current_source_dir()
)