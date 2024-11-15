# C Library for emulating Terminal Commands 📚

C library developed for a university project that emulates the behavior of some terminal commands. The commands that are "emulated" are:
- `head`: Prints the first 10 lines read from standard input or the number of lines specified by the user.
- `tail`: Prints the last 10 lines read from standard input or the number of lines specified by the user.
- `longlines`: Prints the number of lines specified by the user that are the longest in the input.

## 🚀 Usage
To test the library, you can compile the `test.c` file with the following command:
```bash
./compila.sh
```

Then, you can run the compiled file with the following command:
```bash
./test -<function> <number> 
```

Where `<function>` is the function you want to test and `<number>` is the number of lines you want to read. For example:
```bash
./test -head 5
```

## 📜 Credits

| Name          | GitHub                                       | LinkedIn                                                    |
| ------------- | -------------------------------------------- | ----------------------------------------------------------- |
| Diego Sánchez | [@CuB1z](https://github.com/CuB1z)           | [Diego Sánchez](https://www.linkedin.com/in/cub1z/)         |
| Daniel Santos | [@danisntoss](https://github.com/danisntoss) | [Daniel Santos ](https://www.linkedin.com/in/danisntoss/) |

## 📚 License

By Diego Sánchez and Daniel Santos.

This projects is licensed under a Creative Commons CC0 1.0 Universal License. 

You should have received a copy of the license along with this work. If not, see [http://creativecommons.org/publicdomain/zero/1.0/](http://creativecommons.org/publicdomain/zero/1.0/).
