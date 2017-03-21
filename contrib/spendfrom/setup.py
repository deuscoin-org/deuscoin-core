from distutils.core import setup
setup(name='DEUSspendfrom',
      version='1.0',
      description='Command-line utility for deuscoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@deuscoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
