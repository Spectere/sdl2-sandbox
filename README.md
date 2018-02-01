# SDL2 Sandbox

## Introduction

I've made quite a few little experimental projects in SDL. As such, I've
written very similar initialization code multiple times. I decided that it
would be much easier to put some quick boilerplate code together to give me a
base to quickly experiment with new ideas without having to keep reinventing
the wheel.

## Requirements

This project is aimed at people who are programming using a Linux system. A
compiler toolchain, such as gcc with binutils, and an implementation of Make
are required to build the project. Please note that the Make implementation
must support the $(shell) syntax.

If you're running a Linux system with the development tools installed, odds are
this will work without a hitch. If you're using *BSD, you may have to use GNU
make (gmake) for this to build properly.

macOS and Windows users will have to do a bit more work to get this running,
whether it be creating an Xcode/MSVC project, manually compiling SDL, or using
a third-party package manager and/or toolchain (such as mingw64 on Windows or
homebrew on macOS).

SDL 2.0 is required. Later versions may work, but earlier versions will not.

## What's Included?

This project includes a Makefile, a working sample project, and ignore files
for git and Mercurial. It's designed so that you can compile it, watch it work,
then immediately start making changes.

## How to Use This Project

The first step to using this project is to determine which branch suits your
skill level. The `master` branch--the default--is very heavily commented,
intended to help ease beginners into C and SDL2. All major calls and actions
are commented, and the rationale behind each step is explained in as much
detail as is feasible.

The `terse` branch is much cleaner, intended for people who just want to be
able to use this as a base to build other projects.

Since this is intended to be used as a base, it is highly recommended that you
create your own repository (if you choose to use one) rather than keeping the
existing one. For example, if you wanted to create a project called "my_game",
run the following from your terminal emulator of choice:

```
git clone https://github.com/Spectere/sdl2_sandbox.git my_game
cd my_game
rm -rf .git
git init
```

The above command clones the git repository, changes into the project
directory, removes the existing git repository, then creates a new one in its
place. If you prefer to use Mercurial, use `hg init` in place of
`git init`.

If you are using a repository, be sure to delete the ignore file that does
not apply to your VCS of choice. For example, if you're using git, you should
run `rm .hgignore`, while if you're using Mercurial you should run
`rm .gitignore`. If you don't want to use either, both files can be removed.

After your project directory is prepared, type `make` to build the project.
If there are no errors, type `make test` to launch it. You should see a window
pop up with some color shifting. Either press ESC or close the window to exit.

Now, modify `defs.h` to customize the window title text and resolution. The
application loop is contained in `game.c`, and input handling is done in
`event.c`. Happy coding!

## Caveats

While this project does provide a quick and easy way to create an SDL2 project,
it was not intended for large-scale or release-ready projects. Here are a few
potential issues that you can run into.

* The logger is simple, both in ease-of-use and functionality. It will not
support all platforms flawlessly.

* The video settings are hardcoded in `defs.h`.

* No provisions have been made for audio input and output, network support,
or other features. The only things that have been accounted for are video
and basic input.

* Game logic is tied to the framerate, and vsync is leveraged to limit the
framerate. This project does not contain any timing routines.

* The Makefile was written to include all C files in the src/ directory,
and also names the executable after the directory that contains the
project. Additionally, no automatic configuration is supported, and
cross-platform support is not guaranteed.

* This has not been tested with C++ projects.

## Contributing

If you can think of any ways to improve this project, feel free to submit a
pull request. Please note that PRs that push the project too far past its main
goals will most likely be rejected. The goals are as follows:

1. To provide a base for experimentation and prototyping.
2. To provide beginners with a means of easing into SDL2 programming.

It's recommended that contributions provide thorough documentation, as seen in
the master branch, but this is not required.

Also, please take note of the following style guidelines in this section:

### Comments

All source code comments should be C89-style (using `/*` and `*/`), not
C++-style (using `//`). Comments should be made above the applicable line,
though inline comments may be used where appropriate.

A brief description of the file should be included on every source and header
file.

Comments should not exceed 80 columns of width, including whitespace.

### Braces

Open braces should appear at the end of all block statements, including
function definitions.

### Whitespace and Code Width

Code should be indented using tabs. Total width should be counted counted as if
each tab were 4 spaces in width, as that is the default with most modern
graphical IDEs.

Parenthesis should be placed against control statements, function calls, and
function declarations, with no extra spaces. When pointers are declared, be it
in function or variable definitions, the asterisk should be placed against the
name of the pointer.

80 columns of width should be considered a soft cap, as that will allow easy
code examination when using multiple editor panes and a terminal. 120 columns
should be considered a hard cap. Where feasible, a single parameter or equation
should not be broken across multiple lines.

If a function call must span multiple lines, the subsequent lines should be
indented with a single tab.

If a function definition must span multiple lines, the subsequent lines should
be aligned with spaces to one character after the open parenthesis.

If a control statement must span multiple lines, the subsequent lines should be
indented with two tabs. That said, this probably should never occur on a
project with this scope.

### Include Guards

`#ifndef/#define/#endif` should be used for all include guards. At this time,
`#pragma once` should be avoided. The definition format that should be used is
the include filename, in all caps, with underscores surrounding it and
replacing dots. The `#endif` must have the definition stated in an inline
comment.

For example, if you're working on a header file called `foo.h`, it should look
like the following:

```c
/* foo.h
 *
 * Exposes public functions related to the foo subsystem.
 */

#ifndef _FOO_H_
#define _FOO_H_

void foo_bar();

#endif /* _FOO_H_ */
```

## Licensing

This project is released under the Unlicense, effectively putting it into the
public domain. Feel free to use, modify, and even relicense it to best suit
your needs. No attribution is required.
