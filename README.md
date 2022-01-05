# Peggy

A board game for Haiku inspired by Mastermind™.


![Screenshot](./screenshot.png)

## Prerequisites
Peggy should compile and run under any version of Haiku that is not too ancient.
A C++11 capable compiler is required, so remember to do a *setarch x86* on 32bit Haiku.

## Compiling
Compiling is done using the makefile engine supplied with Haiku. A simple *make* compiles the code,
and *make bindcatalogs* adds the translations.

After that, you can run *Peggy* from the generated *objects.xxxxx* directory.

## Contributing
Pull requests for bugfixes and design improvement are very welcome. For language translations please
use Haiku´s Polyglot tool at https://i18n.kacperkasper.pl

