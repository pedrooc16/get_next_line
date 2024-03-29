# get_next_line.c

<h1 align="center">
	📖 get_next_line
</h1>

</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

---

## 💡 About the project

> _The aim of this project is to make you code a function that returns a line, read from a file descriptor._


For more detailed information, look at the [**subject of this project**](https://github.com/pedrooc16/get_next_line/blob/main/get_next_line.pdf).


## 🛠️ Usage

### Requirements

The function is written in C language.

### Instructions

**1. Using it in your code**

To use the function in your code, simply include its header:

```C
#include "get_next_line.h"
```

and, when compiling your code, add the source files and the required flag:

```shell
get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>
```

## 📋 Testing

You only have to edit the get_next_line.c file and uncomment the main function and headers inside it.
You can edit test.txt files to put another text if you wish to test othe cases.
Then simply run this command (change "xx" with desired buffer size) :

```shell
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=xx get_next_line.c get_next_line_utils.c && ./a.out
```

Or you can also use this following testers to test the code yourself :)

* [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)
* [xicodomingues/francinette](https://github.com/xicodomingues/francinette)
