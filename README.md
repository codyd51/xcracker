xcracker
--------------

xcracker is a simple password cracker. `locked.c` is a simple locked program that accepts a password as an argument. 'cracker.c' generates and attempts every possible string up to 16 characters on the locked program. When a correct password is found, the password and some statistics about the crack are printed out.

Currently, xcracker only generates passwords with characters 'a'-'z' due to performance constraints. The bottleneck right now is `popen`ing the locked program every time we generate a password.

MIT license.