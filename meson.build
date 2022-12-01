project('guiplug', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

compiller = meson.get_compiler('cpp')
source_dir = meson.current_source_dir()


include=include_directories(
      'imgui/',
      'imgui/backends/',
      'imgui/renderers/',
      'GLFW/',
      'include/',
      'include/fonts',
      'resources/',
      'resources/fonts/',
      'dependencies/',
      'dependencies/skia/',
      'dependencies/skia/include/',
      'dependencies/skia/include/core/',
      'dependencies/skia/include/effects/',
      'dependencies/skia/include/gpu/',
      'dependencies/skia/include/private/',
      'dependencies/skia/include/config/',
      'dependencies/skia/src/',
      'dependencies/skia/src/core/',
      'dependencies/skia/src/ports/',
      'dependencies/skia/src/images/',
      'dependencies/skia/src/gpu/',
      'dependencies/skia/modules/',
      'dependencies/skia/third_party/',
      'lib/',
      'lib/nlohmann/',
      'C:/msys64/mingw64/include/GL/',
 
      )

add_project_link_arguments( 
      '-luuid',         
      '-lucrt',        
      '-lopengl32',
	'-lskia',
      '-lparticles',
      '-lpathkit',
      # '-lskottie',
      '-lskparagraph',
      '-lskresources',
      '-lskshaper',
      '-lsktext',
      '-lskunicode',
      '-lsvg',
      '-ljpeg',
      '-lpng',
      '-lwebp',
      '-lwebpdecoder',
      '-lwebpmux',
      '-lwebpdemux',
        language: 'cpp'
      )

libs=[]

src=[
      'src/GuiPlugApp.cpp',
      'imgui/imgui.cpp',
      'imgui/imgui_stdlib.cpp',
      'imgui/imgui_draw.cpp',
      'imgui/imgui_tables.cpp',
      'imgui/imgui_widgets.cpp',
      'imgui/imgui_demo.cpp',
      'imgui/backends/imgui_impl_glfw.cpp',
      'imgui/renderers/imgui_impl_opengl3.cpp',
      'dependencies/skia/src/core/SkImageInfo.cpp'
      ]

# Additional precompiled libs
libs += compiller.find_library('libglfw3dll', dirs : source_dir+'/lib')
libs += compiller.find_library('skia', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skia.dll', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skparagraph', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skparagraph.dll', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skshaper', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skshaper.dll', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('sktext', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('sktext.dll', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skunicode', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skunicode.dll', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skcms', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('skresources', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('compression_utils_portable', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('expat', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('harfbuzz', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('icu', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('libjpeg', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('libpng', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('particles', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('pathkit', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('wuffs', dirs : source_dir+'/dependencies/skia_b')
# libs += compiller.find_library('zlib', dirs : source_dir+'/dependencies/skia_b')
 

executable('a',
           'main.cpp',
           #cpp_args: '-DSK_GL',
           include_directories : include,
           sources : src,
           dependencies : libs,
           install : true,
           install_dir: './release')

 