#!/bin/bash

# --- Setup Sandbox ---
TEST_DIR="tmp1"
mkdir -p "$TEST_DIR"
cd "$TEST_DIR" || exit 1

mkdir -p src include
echo "int main() { return 0; }" > src/main.c
echo "int util() { return 0; }" > src/util.c
echo "// header" > include/util.h

# --- Run the backup script ---
echo "[INFO] Running backup_c_files.sh..."
bash ../../task1/backup_c_files.sh

# --- Validate Results ---
FAIL=0

for file in src/main.c src/util.c; do
	if [[ -f "$file.orig" ]]; then
		echo "[PASS] Found backup: $file.orig"
	else
		echo "[FAIL] Missing backup for: $file"
		FAIL=1
	fi
done

if [[ ! -f include/util.h.orig ]]; then
	echo "[PASS] Not-C file not backed up"
else
	echo "[FAIL] Unexpected backup of util.h"
fi

# --- Run the cleanup script ---
echo "[INFO] Running remove_backup_c_files.sh..."
bash ../../task1/remove_backup_c_files.sh
for file in src/main.c src/util.c; do
	if [[ ! -f "$file.orig" ]]; then
		echo "[PASS] Backup deleted: $file.orig"
	else
		echo "[FAIL] Backup not delted: $file.orig"
		FAIL=1
	fi
done

# --- Conclusion ---
if [[ $FAIL -eq 0 ]]; then
	echo "✅ Taks 1 passed all tests"
else
	echo "❌ Taks 1 failed tests"
fi

# --- Clean Up ---
cd ..
rm -rf $TEST_DIR
