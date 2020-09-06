#!/bin/bash

#magnet-info() {
  hash=$(echo "$1" | grep -oP "(?<=btih:).*?(?=&)")
  echo "Magnet hash: $hash"
  aria2c --bt-metadata-only=true --bt-save-metadata=true -q "$1"
  aria2c "$hash.torrent" -S
#}
