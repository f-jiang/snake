# Snake



## Installing and Compiling on Linux

- `git clone` this repo or download as ZIP
- To compile, `cd` into the root of the local repo and execute the following command:
```
$ make
```

### Dependencies

Snake relies on ncurses for displaying terminal graphics and make for compiling the program. On Debian and Ubuntu-based distros these can be installed using this command:
```
$ sudo apt install -y libncurses5-dev make
```

## Usage

Run the program by issuing the following command from the root of the local repo:
```
$ ./snake
```
You can set the size of the game map using the `-s` option, shown below. A size 5 map will occupy the entire terminal window.
```
$ ./snake -s 3    # size ranges from 1 to 5, inclusive
```

## Built With

- ncurses

## Authors

- Feilan Jiang ([f-jiang](https://github.com/f-jiang))

## License

This project is licensed under the MIT License; see the [LICENSE.txt](https://github.com/f-jiang/snake/blob/master/LICENSE.txt) file for details.
