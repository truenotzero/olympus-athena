#!/bin/bash
source compiler_options.sh

TEST_BIN="$TEST/bin"
TARGETS=$(find "$TEST" -name "*.c")

echo "Clearing old tests"
rm -f $(find "$TEST_BIN" -name "*.*" ! -name "*.h")

echo "Compiling tests"

i=1
for f in $TARGETS; do
    echo -n "$i. Compiling \"$f\"... "
    ff=$f
    f=${f%.c}
    f="${f##*/}"
    "$CC" -o "$TEST_BIN/$f.exe" -include "$TEST_BIN/framework.h" $CFLAGS $ff
    echo "Done!"
    i=$((i + 1))
done

echo -e "\nExecuting test harness"
i=$((i-1))
j=1
TARGETS=$(find "$TEST_BIN" -name "*.exe")
for f in $TARGETS; do
    echo "$j/$i. Running \"$f\":"
    $f
    if [[ $? -eq 0 ]]; then
        echo -e "Ok!\n"
        j=$((j + 1))
    else
        echo "Fail!"
        break
    fi
done