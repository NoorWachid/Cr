# cr
A nice wrapper to create files and directories

## Features
- Short!
  If you always doing `mkdir -p src/mylib` and then `touch src/mylib/mylib.{c,h}`.
  Now you can do it in a single command `cr src/mylib/mylib.{c,h}`

## Usage
- Create a file
  `$ cr myfile`
- Create a directory
  `$ cr mydir/`
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
