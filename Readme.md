# Cr
A nice wrapper for creating files and recursive directories

[STILL IN ALPHA STAGE DONOT USE IT TO MODIFY ROOT BASED ACCESS]

## Features
- Short!  
  If you always doing `mkdir -p src/mylib` and then `touch src/mylib/mylib.{c,h}`.
  Now you can do it in a single command `cr src/mylib/mylib.{c,h}`

## Install
`$ git clone https://github.com/wachd/cr.git`

`$ cd cr`

`$ sudo make install`

## Practical usage
```shell
# Create a directory and cd to it
# rcd tmp/Testing/SomethingDangerous
rcd() {
    cd `cr -dr $1`
}

# Create a file and edit it
# rvi Projects/NewProject/MyLib{c,h}
rvi() {
    vi `cr -f $1`
}

```

## Wierd stuff
`$ cr -dr somedir -n somefile somediragain/`

## Flags
- `v` version
- `h` help
- `r` directory mode
- `n` normal mode
- `o` print output
- `d` print output directory only
- `f` print output file only
- `s` silent the output

## Usage
- Create a file  
  `$ cr myfile`
- Create a directory  
  `$ cr mydir/`  
  `$ cr -r mydir`
- Create a file and a directory  
  `$ cr mydir/myfile`
- Create multiple files  
  `$ cr file1 file2`
- Create multiple directories  
  `$ cr dir1/ dir2/`
- Create nested directories  
  `$ cr dir1/dir2/`
- Create nested directories and file  
  `$ cr dir1/dir2/file`
- Create file with glob enable in your shell  
  `$ cr src/{main,stack,string}.{c,h}`
