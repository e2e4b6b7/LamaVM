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
./LamaVM analyze Sort.bc
```

Output:
```
Simple count
DROP: 40
DUP: 35
CONST: 35
ELEM: 25
LD: 23
JMP: 19
LINE: 17
CALL: 11
CJMP: 11
ST: 10
BEGIN: 7
END: 7
BINOP: 6
SEXP: 4
...

Parametrized count
DROP: 40
DUP: 35
ELEM: 25
CONST 1: 18
CONST 0: 16
LD 2 0: 9
END: 7
ST 1 0: 4
LD 1 0: 4
SEXP 0 2: 4
...

Simple groups of length 3 count
DUP; CONST; ELEM; : 22
DROP; DUP; CONST; : 20
ELEM; ST; DROP; : 10
CONST; ELEM; ST; : 10
CONST; ELEM; DROP; : 9
END; BEGIN; LD; : 6
ST; DROP; DUP; : 5
ST; DROP; DROP; : 5
ELEM; DROP; DROP; : 5
DROP; DROP; LD; : 5
DROP; DROP; DUP; : 5
LD; CALL; DUP; : 4
ELEM; DROP; DUP; : 4
CONST; ELEM; CONST; : 4
...
```
