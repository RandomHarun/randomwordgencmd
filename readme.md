# About

This is a random word generator command line tool. If you provide it with a wordlist (see Download/Usage) it will use [libsodium](https://github.com/jedisct1/libsodium) to generate a random uniform number based on the size of the wordlist given and output one of the words in that list. This *should* mean that every word in that list is equally likely to occur. I sourced mine from [here](https://www.mit.edu/~ecprice/wordlist.10000), however I stripped all words with less than 4 characters, so it winds up being 8900 words. The intent is to use this to generate random passwords, inspired by this [XKCD](https://xkcd.com/936/).

# Disclaimer

**This is a learning project.** I am not an experienced programmer. Do not expect a robust piece of software. This will surely break if the wordlist is not formatted correctly or if the command line arguments given are misspelled. What happens then is really up to anyone's guess. Feel free to give advice and if you see something that you consider very bad practice in coding, feel free to correct me. However, I might take a long time to respond. Furthermore if you see something terrible, please consider that I didn't know any better.

# Download 

[1.0 Release](https://github.com/RandomHarun/randomwordgencmd/releases/tag/v1.0)

Please download the executable as well as the wordlist file. Both are needed. Alternatively you may create your own wordlist. It should contain one word per line, which is to say one line will be considered one word by the program. The wordlist should not contain duplicates. I have not tested unicode characters which probably means they won't work.

# Usage / Features

This being a command line tool, put the executable where you want, open a command line shell and run it from there to see console output. If you put the provided wordlist.txt in the same directory as the executable it should work "out of the box". It is designed to run smoothely in a script. Given the above disclaimer, I would however not recommend using it in any important automated process.

## Possible Arguments

-  [-h] or no argument to display this help info.
-  [-i wordlist] path to wordlist text file. 1 word per line. Will try to open a "wordlist.txt" in the same folder as the executable by default.
-  [-o output-file] path to output file. if none given, output will be to the console.
-  [-n count] number of random words to generate, default is 1.
-  [-d delimiter] delimiting string between output words(can be single character), newline by default.
-  [-v] Enable verbose display. (more information about chosen settings and odds of the calculated sequence being guessed.)

# ToDo
-  Test the actual randomness of the output by outputting a lot of words and counting the duplicates.
-  Make it run faster. I realise it's terribly slow.
-  Make the code more robust. I.E. have the flag "parsing" be mindful of misspellings, falsely left out info etc
-  Port it to other operating systems
-  ???

# License

[ISC license](https://en.wikipedia.org/wiki/ISC_license)

```
Copyright 2022 Phillip Haarhaus

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
```
