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

    `opengl32.lib`
  ],

  staticLibraries: [
    path.resolve(libDirectory, `glew32s.lib`),
    path.resolve(libDirectory, `SOIL.lib`)
  ],

  macros: [ 'GLEW_STATIC' ],
  args: ['/MD', '/EHcs'],
}

const game_config = {
  entry: path.resolve(__dirname, `../game/main.cpp`),

  includeDirectories: [
    path.resolve(__dirname, '../deps/includes/'),
    path.resolve(__dirname, `../src`)
  ]
}

module.exports = cuff => {
  const option = cuff.buildConfig(config)
  const output = cuff.compilers.clDefault.generate(option)

  cuff.commands.build(output)
  .catch(err => {})
}