const { cge_config, game_config } = require('./shared.config.js')

module.exports = cuff => {

  cuff.commands.watch(cge_config, option => {
    const cge_option = cuff.buildConfig(cge_config)
    const output = cuff.compilers.clLib.generate(cge_option)

    cuff.commands.build(output)
    .then(() => {
      const game_option = cuff.buildConfig(game_config)
      const game_output = cuff.compilers.clDefault.generate(game_option)

      return cuff.commands.build(game_output)
    })
    .catch(() => {})
  })

  cuff.commands.watch(game_config, option => {
    const game_output = cuff.compilers.clDefault.generate(option)

    return cuff.commands.build(game_output)
  })

}