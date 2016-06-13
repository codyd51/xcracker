xcracker
--------------

xcracker is a simple password cracker. 

`locked.c` is a simple locked program that accepts a password as an argument. 

`cracker.c` has two stages: a dictionary attack and a brute force attack. The former tries the top 100,000 most common passwords (located in `common_pwds.txt`), and the latter generates every string and tries each.

Currently, the brute-force attack only generates passwords with characters 'a'-'z' due to performance constraints. The bottleneck is the `system()` call we must make every time we test a password.

MIT license.
