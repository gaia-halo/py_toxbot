from setuptools import setup, Extension, find_packages

e = Extension("tox._tox",
              sources=["tox/toxmodule.c"],
              libraries=['toxcore'])

setup(name="python-tox",
      version="0.1",
      packages=find_packages(),
      ext_modules=[e],
      author='Antonio Serrano Hernandez',
      author_email='toni.serranoh@gmail.com')

