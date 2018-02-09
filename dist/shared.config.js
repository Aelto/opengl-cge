const path = require('path')
const libDirectory = path.join(__dirname, '../deps/libs')

const cge_config = {
  entry: path.resolve(__dirname, '../src/cge.cpp'),
  
  includeDirectories: [
    path.resolve(__dirname, '../deps/includes/'),
  ],

  libraries: [
    path.resolve(libDirectory, `glfw3.lib`),
    path.resolve(libDirectory, `freetype28.lib`),
    path.resolve(libDirectory, `glew32s.lib`),
    path.resolve(libDirectory, `SOIL.lib`),

    'gdi32.lib', 'opengl32.lib', 'kernel32.lib', 'user32.lib', 'shell32.lib'
  ],

  macros: [ 'GLEW_STATIC' ],
  args: ['/MD', '/EHcs', '/std:c++17'],
}

const game_config = {
  entry: path.resolve(__dirname, `../game/main.cpp`),

  includeDirectories: [
    path.resolve(__dirname, '../deps/includes/'),
    path.resolve(__dirname, `../src`)
  ],

  ignored: [ 'cge.h' ],

  libraries: ['cge.lib'].concat(cge_config.libraries),
  args: [].concat(cge_config.args)
}


module.exports = { cge_config, game_config }