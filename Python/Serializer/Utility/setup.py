from setuptools import setup
from setuptools import find_packages

setup(
    name='convert',
    packages=[
        'packager',
        'factory',
        'parsers',
    ],
    version='0.3.0',
    description='Custom serializer',
    author='Stanislav Korenevsky',
    install_requires=[],
    scripts=['bin/convert']
)