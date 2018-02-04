const path = require('path')
const libDirectory = path.join(__dirname, '../deps/libs')

const config = {
  entry: path.resolve(__dirname, '../game/main.cpp'),

  includeDirectories: [
    path.resolve(__dirname, '../deps/includes/')
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

  modules: {
    directory: path.join(__dirname, '../src'),
    // extension: '.ixx'
  },

  macros: ['GLEW_STATIC'],
  args: ['/MD', '/EHcs'],
}

module.exports = cuff => {

  cuff.commands.watch(config, option => {
    const output = cuff.compilers.clDefault.generate(option)

    cuff.commands.build(output)
      .catch(err => { })
  })

}