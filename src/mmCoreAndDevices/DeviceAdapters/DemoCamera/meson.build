mmdevice_dep = dependency('mmdevice_dep')

library(
    'mmgr_dal_DemoCamera',
    ['DemoCamera.cpp'],
    dependencies: [mmdevice_dep],
    cpp_args: [
        '-Wno-unused-but-set-variable',
        '-Wno-reorder',
        '-Wno-unused-private-field',
    ],
)