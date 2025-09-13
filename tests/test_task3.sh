#!/bin/bash

# --- Setup Sandbox ---
TEST_DIR="tmp3"
mkdir -p "$TEST_DIR"
cd "$TEST_DIR" || exit 1

echo "[INFO] Build ./run_cmds..."
cp -r ../../task3/ task3_copy
make -C task3_copy > /dev/null 2>&1

if [[ ! -x task3_copy/run_cmds ]]; then
	echo "[SETUP FAIL] task3 binary was not built"
	cd ..
	rm -rf "$TEST_DIR"
	exit 1
fi
mv task3_copy/run_cmds .
rm -rf task3_copy

TASK3=./run_cmds
FAIL=0

# --- Test Function ---
run_test() {
	local prog1="$1"
	local prog2="$2"
	local prog3="$3"
	local expected="$4"
	local outfile="outfile.txt"

	echo "[INFO] running $prog1 && $prog2 | $prog3 > $outfile"
	$TASK3 $prog1 $prog2 $prog3 $outfile
	if [[ "$expected" == "__FILE_SHOULD_NOT_EXIST__" ]]; then
		if [[ ! -f "$outfile" ]]; then
			echo "[PASS] File correctly not created"
		else
			echo "[FAIL] File should not have been created"
			FAIL=1
			rm -f "$outfile"
		fi
	elif [[ -f "$outfile" ]]; then
		actual=$(<"$outfile")
		if [[ "$actual" == "$expected" ]]; then
			echo "[PASS] $prog1 && $prog2 | $prog3 > $outfile -> '$expected'"
		else
			echo "[FAIL] output missmatch"
			echo "expected:	'$expected'"
			echo "got:		'$actual'"
			FAIL=1
		fi
	else
		echo "[FAIL] Output file not created"
		FAIL=1
	fi
	rm -f "$outfile"
}

# --- Tests ---
run_test	/bin/true	/bin/echo	/bin/wc		"$(/bin/true && /bin/echo | /bin/wc)"
run_test	/bin/false	/bin/echo	/bin/wc		"__FILE_SHOULD_NOT_EXIST__"
run_test	/bin/true	/bin/pwd	/bin/wc		"$(/bin/true && /bin/pwd | /bin/wc)"
run_test	/bin/true	/bin/pwd	/bin/base64	"$(/bin/true && /bin/pwd | /bin/base64)"

# --- Conclusion ---
if [[ $FAIL -eq 0 ]]; then
    echo "✅ Task 3 passed all tests"
else
    echo "❌ Task 3 failed tests"
fi

# --- Cleanup ---
cd ..
rm -rf $TEST_DIR
