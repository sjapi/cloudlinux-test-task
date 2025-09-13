#!/bin/bash

# --- Setup Sandbox ---
TEST_DIR="tmp2"
mkdir -p "$TEST_DIR"
cd "$TEST_DIR" || exit 1

mkdir -p proj/src proj/include
echo "int main() { return 0; }" > proj/src/main.c
echo "int util() { return 0; }" > proj/src/util.c
echo "// header" > proj/include/util.h

# --- Run Build ---
echo "[INFO] Building task2/list_dir..."
make -C ../../task2 > /dev/null 2>&1
if [[ ! -x ../../task2/list_dir ]]; then
	echo "[FAIL] list_dir was not built"
	cd ..
	rm -rf $TEST_DIR
	exit 1
fi

echo "[INFO] Copy executable to test folder"
cp ../../task2/list_dir .
echo "[INFO] Cleanup task2 folder"
make -C ../../task2 fclean > /dev/null 2>&1

# --- Run Program --- 
echo "[INFO] Running list_dir on test project"
OUTPUT=$(./list_dir)

EXPECTED=$(
cat <<EOF
$PWD
	proj
		include
			util.h
		src
			util.c
			main.c
	list_dir
EOF
)

# --- Compare Results ---
FAIL=0
if [[ "$OUTPUT" == "$EXPECTED" ]]; then
	echo "[PASS] Output matches expected"
else
	echo "[FAIL] Output mismatch"
	echo "Expected:"
	echo "$EXPECTED"
	echo "Got:"
	echo "$OUTPUT"
	FAIL=1	
fi

# --- Conclusion ---
if [[ $FAIL -eq 0 ]]; then
	echo "✅ Task 2 passed all tests"
else
	echo "❌ Task 2 failed tests"
fi

# --- Cleanup ---
cd ..
rm -rf "$TEST_DIR"
