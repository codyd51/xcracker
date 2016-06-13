xcracker
--------------

xcracker is a simple password cracker. 

`locked.c` is a simple locked program that accepts a password as an argument. 

`cracker.c` attempts to crack the password for the locked program. `cracker.c` has two stages: a dictionary attack and a brute force attack. The former tries the top 100,000 most common passwords (located in `common_pwds.txt`), and the latter generates every string and tries each. 

The bottleneck is the `system()` call we must make every time we test a password. To work around this, `cracker` also accepts a password as a command line argument. If a password is not specified as an argument, `cracker` tries to crack `locked`'s password instead.

MIT license.
