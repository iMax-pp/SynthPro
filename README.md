# SynthPro

## Introduction

SynthPro is a modular anolgic synthesizer simulator.


## UML Diagrams

[PicasaWeb](http://picasaweb.google.com/simon.maxime/SynthPro?authkey=Gv1sRgCND6ouPy7s6rvAE) **(outdated)**

## Deployment

Here is a quick guide to deploy a standalone version of SynthPro for each platform.

### On OS X

After the compilation of the application (into a `.app` bundle), use the tool provided with Qt, `macdeployqt`, to make it a standalone bundle (it will integrate Qt binaries in your bundle).

    $ macdeployqt bin/SynthPro.app

### On X11 platforms (GNU/Linux, BSDs…)

TODO

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
