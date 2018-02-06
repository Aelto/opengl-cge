const path = require('path')
const libDirectory = path.join(__dirname, '../deps/libs')

const game_config = {
  entry: path.resolve(__dirname, `../game/main.cpp`),

  includeDirectories: [
    path.resolve(__dirname, '../deps/includes/'),
    path.resolve(__dirname, `../src`)
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

module.exports = cuff => {

  cuff.commands.watch(game_config, option => {
    const game_option = cuff.buildConfig(option)
    const game_output = cuff.compilers.clDefault.generate(game_option)

    return cuff.commands.build(game_output)
  })

}