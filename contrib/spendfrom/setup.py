from distutils.core import setup
setup(name='mubspendfrom',
      version='1.0',
      description='Command-line utility for mubdi "coin control"',
      author='Hatta Yuthafiga',
      author_email='founder@nur1labs.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
