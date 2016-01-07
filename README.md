### Self-contained ANSI C program for benchmarking sorting algorithms

#### Compiling

Using [GCC]:

```
gcc sorttest.c -ansi -Wall -pedantic -o sorttest
```

Using [clang]:

```
clang sorttest.c -ansi -Wall -pedantic -o sorttest
```

Using [Microsoft Visual Studio C compiler][vscc]:

```
cl sorttest.c
```

#### Usage

```
./sorttest SORTALG NUM SEED [CHECK]
    SORTALG - Sorting algorithm: bubble, selection, merge, quick
        NUM - Number of elements to sort
       SEED - Seed for random number generator
      CHECK - Check if sorting is correct
```

For example, invoking `sorttest` to sort an integer array of 100,000 elements
using Bubble sort and a random number generator seed of 99823:

```
$ ./sorttest bubble 100000 99823
```

If a 4th argument is given, the program checks the correctness of the sorting
procedure:

```
$ ./sorttest bubble 100000 34545 yes
Sorting Ok!
```

#### Benchmarking with GNU Time

In several Linux OSes the [GNU Time] utility must be explicitly installed using
the package manager and invoked as `/usr/bin/time`. On OSX it should be
installed using [Homebrew] or similar, and it is invoked as `gtime`.

It is also possible to use the shell built-in *time* command, which is available
by default on Linux and OSX. For Windows, [Cygwin] and [MinGW] provide a [Bash]
shell with this command, but there are [native alternatives].

##### Default output format

The [PerfAndPubTools] benchmark analysis functions accept the default output
format of the [GNU Time] command, as shown in the following example:

```
$ /usr/bin/time ./sorttest merge 500000 99823
0.18user 0.00system 0:00.18elapsed 99%CPU (0avgtext+0avgdata 7076maxresident)k
0inputs+0outputs (0major+2655minor)pagefaults 0swaps
```

Of course, the output should be redirected to a file in order to be used by
[PerfAndPubTools]:

```
$ /usr/bin/time ./sorttest quick 1000000 2362 2> time.txt 
```

##### Alternative output formats

The `-f` option allows to format the output of the [GNU Time] command. For
example, the `%e` format specifier shows the elapsed wall clock time used by the
process (in seconds), while the `%M` specifier displays the maximum resident set
size of the process during its lifetime, in Kilobytes. These are useful for
testing the time and space complexity of each algorithm:

```
$ /usr/bin/time -f "%e sec.\n%M Kb\n" ./sorttest bubble 100000 128
59.62 sec.
1348 Kb

$ /usr/bin/time -f "%e sec.\n%M Kb\n" ./sorttest selection 100000 128
16.87 sec.
1352 Kb

$ /usr/bin/time -f "%e sec.\n%M Kb\n" ./sorttest merge 100000 128
0.03 sec.
2320 Kb

$ /usr/bin/time -f "%e sec.\n%M Kb\n" ./sorttest quick 100000 128
0.02 sec.
1348 Kb
```

#### License

[MIT License](http://opensource.org/licenses/MIT)

[GNU Time]: https://www.gnu.org/software/time/
[Homebrew]: http://brew.sh/
[PerfAndPubTools]: https://github.com/fakenmc/perfandpubtools
[Cygwin]: https://www.cygwin.com/
[MinGW]: http://www.mingw.org/
[Bash]: http://tiswww.case.edu/php/chet/bash/bashtop.html
[tricky]: http://stackoverflow.com/questions/13356628/is-there-a-way-to-redirect-time-output-to-file-in-linux
[native alternatives]: http://stackoverflow.com/questions/673523/how-to-measure-execution-time-of-command-in-windows-command-line
[GCC]: https://gcc.gnu.org/
[clang]: http://clang.llvm.org/
[vscc]: https://msdn.microsoft.com/en-us/library/bb384838.aspx
