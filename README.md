# SynthPro

## Introduction

SynthPro is a modular anolgic synthesizer simulator.

## Downloads

GNU/Linux executable: [SynthPro.tar.gz](https://github.com/downloads/iMax-pp/SynthPro/SynthPro.tar.gz)

Mac OS X executable: [SynthPro.dmg](https://github.com/downloads/iMax-pp/SynthPro/SynthPro.dmg)

## UML Diagrams

[PicasaWeb](http://picasaweb.google.com/simon.maxime/SynthPro?authkey=Gv1sRgCND6ouPy7s6rvAE) **(outdated)**

## Deployment

Here is a quick guide to deploy a standalone version of SynthPro for each platform.

### On OS X

After the compilation of the application (into a `.app` bundle), use the tool provided with Qt, `macdeployqt`, to make it a standalone bundle (it will integrate Qt binaries in your bundle).

    $ macdeployqt bin/SynthPro.app

You can use the `-dmg` flag to create a `.dmg` archive containing the bundle.

### On X11 platforms (GNU/Linux, BSDs…)

After the compilation (32-bit, as the libraries in `lib/` are 32-bit), create an archive (`.tar.gz` for instance) containing `bin/`, `lib/` and `SynthPro.sh`.

It is recommended to add a README file to explain to users that the launching file is `SynthPro.sh` (and not directly `bin/SynthPro`).

### On Windows

TODO *(maybe)*

## Tests

### How to add Tests

After designing a new class, unit and functional tests **MUST** be written. To do so,

- Open the `SynthProTest` project;
- Add your class (and its dependencies) to the `.pro` file;
- Write a test class accordingly (see `TestInPort` for an example);
- Include the execution of this class in `test.cpp` (see `test.cpp` for examples).

### How to execute Tests

To execute the test cases, just run the `SynthProTest` project…


## Coding Style

### Pre-Commit Hook Installation

To install the pre-commit hook for git, copy the `check-style/pre-commit.hook` file to `.git/hooks/pre-commit`, like this:

    $ cp check-style/pre-commit.hook .git/hooks/pre-commit

If you want to skip the style checking (when it's inevitable…) use `--no-verify` at commit:

    $ git commit --no-verify -m "Commit message"

Use this only when you can't do otherwise!

### Using Astyle

If you have `astyle` installed, you can "enhance" your code using the following command:

    $ astyle -s4 -u -Y -M70 -f -p -k1 -H -U -O -n -Q -z2 src/**/*.cpp src/**/*.h

It follows our coding guideline, and may ease the style checking…
