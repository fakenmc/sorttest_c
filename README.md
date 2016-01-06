### Self-contained ANSI C program for testing sorting algorithms

#### Compiling

```
$ gcc sorttest.c -ansi -Wall -pedantic -g -o sorttest
```

#### Usage

```
./sorttest SORTALG NUM SEED [CHECK]
    SORTALG - Sorting algorithm: bubble, selection, merge, quick
        NUM - Number of elements to sort
       SEED - Seed for random number generator
      CHECK - Check if sorting is correct
```

#### Benchmarking with GNU Time

In several Linux OSes the [GNU Time] utility must be explicitly installed and
is invoked as `/usr/bin/time`. In OSX it should be installed using [Homebrew]
or similar, and it is invoked as `gtime`. In the following example we use the
common Linux invokation.

```
$ /usr/bin/time ./sorttest selection 4096 44
0.06user 0.00system 0:00.08elapsed 71%CPU (0avgtext+0avgdata 1304maxresident)k
0inputs+0outputs (0major+69minor)pagefaults 0swaps
```

#### License

[MIT License](http://opensource.org/licenses/MIT)

[GNU Time]: https://www.gnu.org/software/time/
[Homebrew]: http://brew.sh/
