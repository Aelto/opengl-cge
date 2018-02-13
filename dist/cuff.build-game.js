const { game_config } = require('./shared.config.js')

module.exports = cuff => {
  console.log(cuff.args)
  const game_option = cuff.buildConfig(game_config)
  const game_output = cuff.compilers.clDefault.generate(game_option)

  return cuff.commands.build(game_output)
  .catch(() => {})
}