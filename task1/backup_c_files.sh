#!/bin/bash

while IFS= read -r -d '' file; do
	cp "$file" "$file.orig"
done < <(find . -name '*.c' -print0)
