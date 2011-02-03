# SynthPro

## Introduction

SynthPro is a modular anolgic synthesizer simulator.

## UML Diagrams

[PicasaWeb](http://picasaweb.google.com/simon.maxime/SynthPro?authkey=Gv1sRgCND6ouPy7s6rvAE)

## Coding Style

### Pre-Commit Hook Installation

To install the pre-commit hook for git, copy the `check-style/pre-commit.hook` file to `.git/hooks/pre-commit`, like this:

    $ cp check-style/pre-commit.hook .git/hooks/pre-commit

If you want to skip the style checking (when it's inevitable…) use `--no-verify` at commit:

    $ git commit --no-verify -m "Commit message"

Use this only when you can't do otherwise! (ie. when commiting `main.cpp`)

### Using Astyle

If you have `astyle` installed, you can "enhance" your code using the following command:

    $ astyle -s4 -u -Y -M70 -f -p -k1 -H -U -O -n -Q -z2 src/**/*.cpp src/**/*.h

It follows our coding guideline, and may ease the style checking…
