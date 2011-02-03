# SynthPro

## Introduction

SynthPro is a modular anolgic synthesizer simulator.

## UML Diagrams

[PicasaWeb](http://picasaweb.google.com/simon.maxime/SynthPro?authkey=Gv1sRgCND6ouPy7s6rvAE)

## Pre-Commit Hook Installation

To install the pre-commit hook for git, copy the `check-style/pre-commit.hook` file to `.git/hooks/pre-commit`, like this:

    $ cp check-style/pre-commit.hook .git/hooks/pre-commit

If you want to skip style checking (when it's inevitable…) use `--no-verify` at commit:

    $ git commit --no-verify -m "Commit message"

Use this only when you can't do otherwise (ie. when commiting `main.cpp`).