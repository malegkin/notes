#!/usr/bin/env bash
#https://stackoverflow.com/questions/59895/getting-the-source-directory-of-a-bash-script-from-within



########## one line folder resolver:

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
echo "DIR(one_line) = '$DIR'"


######### advanced folder resolver:

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"

echo "DIR(advanced) = '$DIR'"



###  get SOURCE without symlink:

SOURCE="${BASH_SOURCE[0]}"

while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  TARGET="$(readlink "$SOURCE")"
  if [[ $TARGET == /* ]]; then
    echo "SOURCE: '$SOURCE' is an absolute symlink to '$TARGET'"
    SOURCE ="$TARGET"
  else
    DIR="$( dirname "$SOURCE_FOLDER" )"
    echo "SOURCE '$SOURCE' is a relative symlink to '$TARGET' (relative to '$DIR')"
    SOURCE="$DIR/$TARGET" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
  fi
done

echo "SOURCE =  '$SOURCE'"

SOURCE="${BASH_SOURCE[0]}"
