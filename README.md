[![Build Status](https://travis-ci.org/dreal/dreal-cmake-example-project.svg?branch=master)](https://travis-ci.org/dreal/dreal-cmake-example-project)

An example cmake project to show you how to use the system-installed
dReal as a library in a Cmake project.

Setup
=====

You need to install [dReal4](https://github.com/dreal/dreal4) in your
system. We also rely on
[pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config).

macOS 10.13/10.12/10.11
-----------------------

We use [homebrew](https://brew.sh).

```bash
brew install dreal/dreal/dreal
```


Ubuntu 16.04
------------

```bash
curl -s https://raw.githubusercontent.com/dreal/dreal4/master/setup/ubuntu/16.04/install_prereqs.sh | sudo bash
```

Ubuntu 14.04
------------

```bash
curl -s https://raw.githubusercontent.com/dreal/dreal4/master/setup/ubuntu/14.04/install_prereqs.sh | sudo bash
```


CMake Build
===========

Run the following to build and run the example project.

```bash
git clone https://github.com/dreal/dreal-cmake-example-project.git
cd dreal-cmake-example-project
mkdir build
cd build
cmake ../
make           # Build
./check_sat    # Execute
```
