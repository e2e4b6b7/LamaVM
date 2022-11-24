# LamaVM

VM and analyser for Lama language

Implemented by Roman Venediktov

## Build instructions

```bash
cd runtime 
make
cd ..
cmake .
make # Or any other generator
```

## VM tests instructions

Test was copied from original repo. It's bubble sort of 2000 elements. Requires `lamac` to be installed.

Run compiled version:
```bash
lamac tests/Sort.lama
time ./Sort
```

Run interpreter (requires build):
```bash
lamac -b Sort.lama
time ./LamaVM execute Sort.bc
```

## Performance comparison

* 0.56s - Compiled
* 1.3s - Interpreter + (`profile-generate`/`profile-use`)
* 1.9s - Interpreter

## Analyser tests instructions

```bash
lamac -b Sort.lama
time ./LamaVM analyze Sort.bc
```
