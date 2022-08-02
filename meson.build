project(
  'hyfetch',
  'c',
  version : '0.0.1',
  license : 'ARR',

  )

curl = dependency('libcurl')
cjson = dependency('libcjson')
req = library(
    'hyfetch', sources: ['src/Request.c', 'src/Config.c'],
    install: true,
    dependencies: [curl])

executable('hyfetch', 'src/main.c',
  dependencies: [curl, cjson],
  link_with: req,
  install: true)

