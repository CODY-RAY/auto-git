main() {
  set -e
  umask g-w,o-w
  file=/usr/local/bin/auto-git
  env curl -L -o "$file" https://github.com/CODY-RAY/auto-git/releases/download/v0.0.2/auto-git  || {
    printf "Error: download failed\n"
    exit 1
  }

  env brew install boost || {
    printf "Error: boost install failed\n"
    exit 1
  }
  if [ -e "$file" ]; then
     env chmod +x "$file"|| {
    printf "Error: linking failed\n"
    exit 1
  }
  else 
    echo "File does not exist"
  fi 
}

main
