# Project dependencies

I have designed this to work on GNU/Linux, and here's the list of tools
and libraries the scripts and programs in this repo depends on, in case
you want to run them.

## Tools
Among the tools you'll need to run the benchmarks are:

- bash: The shell to run the scripts, the benchmarks (hyperfine setup uses bash).
- pyperf: A python tool to run benchmarks.
- hyperfine: A pretty cool and easy to use script to benchmark command line programs.
- cmake: A meta build tool, with lots of handy stuff to manage projects.
- make: The classic build tool (I believe cmake depends on make)
- g++: The GNU C++ compiler.
- python3: The python interpreter.
- openssl: The open-source implementation of the SSL and TLS protocols.
- coreutils: sha256sum is part of this package. This is very likely part of your setup already.
- perl: Apparently shasum comes with the perl package, at least in Ubuntu, so probably you have it already.
- pkg-config: A helper tool to manage libraries and include paths.

## Libraries

The following is the list of libraries you'll need to compile the programs

| Library           | Package in Ubuntu 20.04  | URL                                          |
|-------------------|--------------------------|----------------------------------------------|
| boost             | libboost1.74-all-dev     | https://www.boost.org/                       |
| fmt               | libfmt-dev               | https://fmt.dev/                             |
| gflags            | libgflags-dev            | https://gflags.github.io/gflags/             |
| fast-float        | libfast-float-dev        | https://github.com/fastfloat/fast_float      |
| double-conversion | libdouble-conversion-dev | https://github.com/google/double-conversion  |
| google-glog       | libgoogle-glog-dev       | https://google.github.io/glog                |
| wolfssl           | libwolfssl-dev           | https://www.wolfssl.com/                     |
| libopenssl-dev    | libopenssl-dev           | https://www.openssl.org/                     |