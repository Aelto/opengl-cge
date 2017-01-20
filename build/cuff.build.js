const path = require('path')
const {exec} = require('child_process')
const {cuff, clCompilerDefault, clCompilerLib} = require('./cuff.js')

cuff({
    entry: path.resolve(__dirname, '../src/main.cpp'),
    includeDirectories: [
        path.resolve(__dirname, `includes`)
    ],
    
    libraries: [
        path.resolve(__dirname, `libs/opengl32.lib`),
        path.resolve(__dirname, `libs/glfw3dll.lib`),
    ],

    staticLibraries: [
        path.resolve(__dirname, `libs/glew32s.lib`),
        path.resolve(__dirname, `libs/SOIL.lib`),
    ],

    macros: [
        'GLEW_STATIC'
    ],

    output: {
        path: path.resolve(__dirname, 'cpp/output'),
        filename: 'main.exe'
    },
    compiler: clCompilerDefault,
    watch: true
})