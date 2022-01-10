from setuptools import setup

setup(
    name='Serializer',
    packages=[
        'Serializer',
        'Serializer/factory',
        'Serializer/packager',
        'Serializer/parsers',
        'Serializer/parsers/custom_json'
    ],
    version='3.1.3',
    description='Serializer library',
    author='Stanislav Korenevsky',
    install_requires=['pyyaml'],
    python_requires='>=3.8',
)