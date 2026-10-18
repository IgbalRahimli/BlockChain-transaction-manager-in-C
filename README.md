# BlockChain-transaction-manager-in-C
Simple campus transaction manager made in C based on a custom blockchain. Interactive in terminal and features EATCoin balance transfers, file persistence, and gambling mini-games.

Written in C. Requires `gcc` or any standard C compiler.

* To build use:  
`gcc main.c -o eatcoin`

* To run on Linux/macOS:  
`./eatcoin`

* To run on Windows:  
`eatcoin.exe`


* Note on data persistence: automatically imports transaction history from `blockChain.txt` on startup if present and exports state back to it via menu options.


* if you encounter an error like this during compilation: "fatal error: dsaproject.c: No such file or directory"
* Ensure `main.c`, `dsaproject.h`, and `dsaproject.c` are all in the same directory.
