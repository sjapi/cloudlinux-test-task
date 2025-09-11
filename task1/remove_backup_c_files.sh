#!/bin/bash

while IFS= read -r -d '' file; do
	rm -f "$file"
done < <(find . -name '*.c.orig' -print0)
