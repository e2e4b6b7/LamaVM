# LamaVM

VM for Lama language

Implemented by Roman Venediktov

## Build instructions

```bash
cmake .
make # Or any other generator
```

## Tests instructions

Test was copied from original repo. It's bubble sort of 2000 elements. Requires `lamac` to be installed.

Run compiled version:
```bash
lamac tests/Sort.lama
time ./Sort
```

Run interpreter (requires build):
```bash
lamac -b Sort.lama
time ./LamaVM Sort.bc
```

Performance comparison:

* 0.56s - Compiled
* 1.3s - Interpreter + (`profile-generate`/`profile-use`)
* 2s - Interpreter
