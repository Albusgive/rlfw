from setuptools import find_packages
from setuptools import setup

setup(
    name='rlfw_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('rlfw_msgs', 'rlfw_msgs.*')),
)
